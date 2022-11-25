#include "llvm/Transforms/Instrumentation/BranchPredictPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Transforms/Instrumentation/BranchPredictFeatures.h"
#include <fstream>
#include <string>
#include <iostream>
// #include <torch/script.h>

namespace llvm {
    
static cl::opt<bool> EnableCollectDataset("collect-dataset", cl::init(false), cl::Hidden, cl::desc("collect dataset"));
static cl::opt<bool> EnableEqualBranchProb("equal-branch-prob", cl::init(false), cl::Hidden, cl::desc("make branch probabilities 50% 50%"));

std::string getEnv( const std::string & Var ) {
     const char * Val = std::getenv( Var.c_str() );
     if ( Val == nullptr ) { // invalid to assign nullptr to std::string
         return "";
     }
    return Val;
    
}

void BranchPredictPass::assignEqualBranchProb(Function &F) {
    for (BasicBlock & BB: F) {
        BranchInst *BI = dyn_cast<BranchInst>(BB.getTerminator());
        if (BI && !BI->isUnconditional()) {
            assignBranchProb(BI, 50);
        }
    }
}

Optional<uint64_t> getBranchProb(BranchInst *BR) {
    MDNode *WeightsNode = BR->getMetadata(LLVMContext::MD_prof);
    if (!WeightsNode)
    return None;

    if (WeightsNode->getNumOperands() != BR->getNumSuccessors() + 1)
    return None;

    auto &V1 = WeightsNode->getOperand(1);
    auto &V2 = WeightsNode->getOperand(2);
    ConstantInt *W1 = mdconst::dyn_extract<ConstantInt>(V1);
    ConstantInt *W2 = mdconst::dyn_extract<ConstantInt>(V2);
    if (!W1 || !W2)
    return None;

    uint64_t Left = W1->getZExtValue();
    uint64_t Right = W2->getZExtValue();
    uint64_t Total = Left + Right;
    

    if (Total < 100)
        return None;

    uint64_t Ratio = (100 * Left) / (Total);
    return Ratio;
}

void BranchPredictPass::assignBranchProb(BranchInst* Branch, unsigned Prob) {
    assert(prob <= 100 && "Invalid prob");
    unsigned TrueProb = Prob;
    unsigned FalseProb = 100 - Prob;

    auto* BranchProb = MDBuilder(Branch->getContext()).createBranchWeights(TrueProb, FalseProb);
    Branch->setMetadata(LLVMContext::MD_prof, BranchProb);
}

void BranchPredictPass::gatherBranchFeatures(BranchFeatures& BF, BranchInst* BR, LoopInfo* LI, DominatorTree* DT, std::set<BasicBlock *> &Visited) {
    BasicBlock* Parent = BR->getParent();
    BasicBlock* Left = BR->getSuccessor(0);
    BasicBlock* Right = BR->getSuccessor(1);
    BasicBlock* Entry = &Parent->getParent()->getEntryBlock();


    BF.setFeature(BranchFeatures::Features::is_entry_block, int(Parent == Entry));
    BF.setFeature(BranchFeatures::Features::num_blocks_in_fn, BR->getParent()->getParent()->size());

    if (CmpInst *CI = dyn_cast<CmpInst>(BR->getCondition())) {
        BF.setFeature(BranchFeatures::Features::condition_cmp, 1);
        BF.setFeature(BranchFeatures::Features::condition_predicate, CI->getPredicate());
        BF.setFeature(BranchFeatures::Features::condition_in_block, CI->getParent() == Parent);
        BF.setFeature(BranchFeatures::Features::predicate_is_eq, CI->isEquality());
        BF.setFeature(BranchFeatures::Features::predicate_is_const, isa<Constant>(CI->getOperand(1)));
    }

    BF.setFeature(BranchFeatures::Features::loop_depth, LI->getLoopDepth(Parent));
    BF.setFeature(BranchFeatures::Features::is_loop_header, LI->isLoopHeader(Parent));
    BF.setFeature(BranchFeatures::Features::is_left_exiting, LI->getLoopFor(Parent) == LI->getLoopFor(Left));
    BF.setFeature(BranchFeatures::Features::is_right_exiting, LI->getLoopFor(Parent) == LI->getLoopFor(Right));
    
    BF.setFeature(BranchFeatures::Features::dominates_left, DT->dominates(Parent, Left));
    BF.setFeature(BranchFeatures::Features::dominates_right, DT->dominates(Parent, Right));
    BF.setFeature(BranchFeatures::Features::dominated_by_left, DT->dominates(Left, Parent));
    BF.setFeature(BranchFeatures::Features::dominated_by_right, DT->dominates(Right, Parent));

    BF.setFeature(BranchFeatures::Features::left_self_edge, Parent == Left);
    BF.setFeature(BranchFeatures::Features::right_self_edge, Parent == Right);

    unsigned Dominates = 0;
    for (BasicBlock &BB : *Parent->getParent()) {
        if (DT->dominates(Parent, &BB)) {
            Dominates += 1;
        }
    }

    BF.setFeature(BranchFeatures::Features::num_blocks_this_dominates, Dominates); 
    BF.setFeature(BranchFeatures::Features::left_is_backedge, Visited.count(Left)); 
    BF.setFeature(BranchFeatures::Features::right_is_backedge, Visited.count(Right)); 

    auto LSB = succ_begin(Left);
    auto LSE = succ_end(Left);
    auto RSB = succ_begin(Right);
    auto RSE = succ_end(Right);

    BF.setFeature(BranchFeatures::Features::right_points_to_left, (std::find(LSB, LSE, Right) != LSE)); 
    BF.setFeature(BranchFeatures::Features::left_points_to_right, (std::find(RSB, RSE, Left) != RSE)); 

    Visited.insert(Parent);
}


void BranchPredictPass::gatherDataset(Function& F, LoopInfo *LI, DominatorTree *DT) {
    std::set<BasicBlock *> Visited;
    for (BasicBlock& BB :F) {
        BranchInst *BR = dyn_cast<BranchInst>(BB.getTerminator());
        if (!BR)
            continue;
        if (BR->isUnconditional())
            continue;

        auto BP = getBranchProb(BR);
        if (!BP.has_value()) {
            continue;
        }

        BranchFeatures BF;
        gatherBranchFeatures(BF, BR, LI, DT, Visited);
        
        auto Ratio = BP.value();
        // std::cout << "========== " << Ratio << "===========" << std::endl;
        std::string FilePath = getEnv("PROJECT_ROOT") + "/dataset/dataset.csv";
        std::ofstream DatasetFile;
        DatasetFile.open(FilePath, std::ios_base::app);
        DatasetFile << BF.toCSVLine() << std::to_string(Ratio) << std::endl;
    }
}

PreservedAnalyses BranchPredictPass::run(Function &F, FunctionAnalysisManager &AM) {
    auto &LI = AM.getResult<LoopAnalysis>(F);
    auto &DT = AM.getResult<DominatorTreeAnalysis>(F);
    if (EnableEqualBranchProb) {
        assignEqualBranchProb(F);
    }

    if (EnableCollectDataset)
        gatherDataset(F,&LI,&DT);
        
    return PreservedAnalyses::all();
}

} // namespace llvm
