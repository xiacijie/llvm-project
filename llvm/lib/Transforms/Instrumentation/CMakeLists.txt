# find_package(Torch REQUIRED)

add_llvm_component_library(LLVMInstrumentation
  AddressSanitizer.cpp
  BoundsChecking.cpp
  CGProfile.cpp
  ControlHeightReduction.cpp
  DataFlowSanitizer.cpp
  GCOVProfiling.cpp
  MemProfiler.cpp
  MemorySanitizer.cpp
  IndirectCallPromotion.cpp
  Instrumentation.cpp
  InstrOrderFile.cpp
  InstrProfiling.cpp
  PGOInstrumentation.cpp
  PGOMemOPSizeOpt.cpp
  PoisonChecking.cpp
  SanitizerCoverage.cpp
  SanitizerBinaryMetadata.cpp
  ValueProfileCollector.cpp
  ThreadSanitizer.cpp
  HWAddressSanitizer.cpp
  BranchPredictPass.cpp
  
  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Analysis
  Core
  Demangle
  MC
  Support
  TransformUtils
  ProfileData
  )
  find_package(PythonLibs REQUIRED)
  include_directories(${PYTHON_INCLUDE_DIRS})
  target_link_libraries(LLVMInstrumentation PRIVATE python3.8)

  # add_subdirectory($ENV{PYBIND_PATH} $ENV{PROJECT_ROOT}/llvm-project/build/pybind11)
  # target_link_libraries(LLVMInstrumentation PRIVATE pybind11::embed)

# target_link_libraries(LLVMInstrumentation PRIVATE ${TORCH_LIBRARIES})