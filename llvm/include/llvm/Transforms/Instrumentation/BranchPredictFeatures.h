#ifndef LLVM_TRANSFORMS_INSTRUMENTATION_BRANCH_PREDICT_FEATURES_PASS
#define LLVM_TRANSFORMS_INSTRUMENTATION_BRANCH_PREDICT_FEATURES_PASS

#include <cassert>
#include <cstdint>
#include <string>

namespace llvm {
    class Features {
        public:
            void setFeature(uint16_t Feature, int32_t Value) {
                FeatureValue[Feature] = Value;
            }

            bool isFeatureSet(uint16_t Feature) {
                return FeatureValue[Feature] != -1;
            }

            int32_t getFeatureValue(uint16_t Feature) {
                assert(isFeatureSet(Feature) && "Feature " + std::to_string(Feature) + "is not set yet!");
                return FeatureValue[Feature];
            }

        private:
            int FeatureValue[64] = {-1};
    };


    class BranchFeatures : public Features {
        enum Features {
            is_entry_block, // 0
            num_blocks_in_fn, // 1
            condition_cmp,  // 2
            condition_predicate, // 3
            condition_in_block, //4
            predicate_is_eq, // 5
            predicate_is_fp, // 6
            predicate_is_const, //7
            left_self_edge, //8
            right_self_edge,//9
            left_is_backedge,//10
            right_is_backedge,//11
            right_points_to_left,//12
            left_points_to_right,//13
            loop_depth,//14
            is_loop_header,//15
            is_left_exiting,//16
            is_right_exiting,//17

            dominates_left, //18
            dominates_right,//19
            dominated_by_left,//20
            dominated_by_right,//21
            num_blocks_this_dominates, //22
            last //23
        };
    };
} // namespace llvm

#endif