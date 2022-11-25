#ifndef LLVM_TRANSFORMS_INSTRUMENTATION_BRANCH_PREDICT_FEATURES_PASS
#define LLVM_TRANSFORMS_INSTRUMENTATION_BRANCH_PREDICT_FEATURES_PASS

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

namespace llvm {
    class Features {
        public:
            void setFeature(uint16_t Feature, int32_t Value) {
                FeatureValue[Feature] = Value;
            }
        protected:
            std::vector<int32_t> FeatureValue;
    };


    class BranchFeatures : public Features {
        public:
            BranchFeatures() {
                FeatureValue.reserve(Features::last);
                for (int I = 0; I < Features::last; I ++) {
                    FeatureValue[I] = 0;
                }
            }

            enum Features {
                is_entry_block, // 0
                num_blocks_in_fn, // 1
                condition_cmp,  // 2
                condition_predicate, // 3
                condition_in_block, //4
                predicate_is_eq, // 5
                predicate_is_const, //6
                left_self_edge, //7
                right_self_edge,//8
                left_is_backedge,//9
                right_is_backedge,//10
                right_points_to_left,//11
                left_points_to_right,//12
                loop_depth,//13
                is_loop_header,//14
                is_left_exiting,//15
                is_right_exiting,//16
                dominates_left, //17
                dominates_right,//18
                dominated_by_left,//19
                dominated_by_right,//20
                num_blocks_this_dominates, //21
                last //22
            };

            std::string toCSVLine() {
                std::string Output;
                for (int I =0 ; I < Features::last; I++) {
                    Output += std::to_string(FeatureValue[I]);
                    Output += ",";
                }

                return Output;
            }

    };
} // namespace llvm

#endif