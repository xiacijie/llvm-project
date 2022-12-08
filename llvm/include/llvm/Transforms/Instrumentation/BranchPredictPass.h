#ifndef LLVM_TRANSFORMS_INSTRUMENTATION_BRANCH_PREDICT_PASS
#define LLVM_TRANSFORMS_INSTRUMENTATION_BRANCH_PREDICT_PASS

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/Instrumentation/BranchPredictFeatures.h"
#include <set>


namespace llvm {

class BranchPredictPass : public PassInfoMixin<BranchPredictPass> {
private:
    void gatherDataset(Function& F, LoopInfo *LI, DominatorTree *DT);
    void gatherDatasetCFG(Function& F, LoopInfo *LI, DominatorTree *DT);
    void gatherBranchFeatures(BranchFeatures& BF, BranchInst* BR, LoopInfo *LI, DominatorTree* DT, std::set<BasicBlock *> &Visited);
    void assignEqualBranchProb(Function &F);
    void predictBranchProb(Function& F, LoopInfo *LI, DominatorTree *DT, const std::string & ModelName);
    void assignBranchProb(BranchInst* Branch, unsigned Prob);

public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif 