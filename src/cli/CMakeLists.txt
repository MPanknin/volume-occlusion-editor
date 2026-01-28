if(NOT BUILD_CLI)
    message(FATAL_ERROR "CLI build is disabled but this target was requested")
endif()

if(BUILD_CUDA)
    # CUDA-based occlusion generation CLI tool
    add_executable(occgen-cli
        occgen_main.cpp)

    target_link_libraries(occgen-cli PRIVATE
        occgen_cuda
        common)

    install(TARGETS occgen-cli
        RUNTIME DESTINATION bin)
else()
    message(WARNING "CLI tools require CUDA. Skipping CLI build.")
endif()
