if(NOT BUILD_CUDA)
    message(FATAL_ERROR "CUDA support is required for this target but BUILD_CUDA is OFF")
endif()

# CUDA occlusion generation library
add_library(occgen_cuda STATIC
    kernel.cu
    LocalHistKernel.cu
    LocalHistKernel.cpp)

target_include_directories(occgen_cuda PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(occgen_cuda PUBLIC
    common
    CUDA::cudart
    CUDA::cuda_driver)

# CUDA compilation flags
set_target_properties(occgen_cuda PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_RESOLVE_DEVICE_SYMBOLS ON
    POSITION_INDEPENDENT_CODE ON)

# Modern CUDA features
target_compile_features(occgen_cuda PUBLIC cxx_std_17)

# Warning suppression for legacy CUDA code
target_compile_options(occgen_cuda PRIVATE
    $<$<COMPILE_LANGUAGE:CUDA>:
        --expt-relaxed-constexpr
        -Wno-deprecated-declarations
    >)

# Installation
install(TARGETS occgen_cuda
    EXPORT SeismicOcclusionEditorTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
