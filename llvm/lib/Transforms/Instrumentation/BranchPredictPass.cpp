#include "llvm/Transforms/Instrumentation/BranchPredictPass.h"
#include "llvm/IR/BasicBlock.h"

namespace llvm {

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
    
    printf("%lu %lu", Left, Right);
    printf("====================\n");

    if (Total < 100)
    return None;

    return (100 * Left) / (Total);
}

void BranchPredictPass::assignBranchProb(BranchInst* Branch, unsigned Prob) {
    assert(prob <= 100 && "Invalid prob");
    unsigned TrueProb = Prob;
    unsigned FalseProb = 100 - Prob;

    auto* BranchProb = MDBuilder(Branch->getContext()).createBranchWeights(TrueProb, FalseProb);
    Branch->setMetadata(LLVMContext::MD_prof, BranchProb);
}

PreservedAnalyses BranchPredictPass::run(Function &F, FunctionAnalysisManager &AM) {
    
    return PreservedAnalyses::all();
}

} // namespace llvm
