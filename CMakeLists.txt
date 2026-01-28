cmake_minimum_required(VERSION 3.20)

project(SeismicOcclusionEditor
    VERSION 1.0.0
    DESCRIPTION "GPU-Accelerated Volumetric Occlusion Classification for Seismic Data"
    LANGUAGES CXX)

# Project options
option(BUILD_VIEWER "Build the interactive viewer application" ON)
option(BUILD_CUDA "Build CUDA-accelerated occlusion generation (requires NVIDIA GPU)" ON)
option(BUILD_CLI "Build command-line tools" ON)
option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_DOCS "Build documentation" OFF)

# Modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Platform-specific settings
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
elseif(UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

# Dependencies
find_package(OpenGL REQUIRED)

if(BUILD_VIEWER)
    find_package(wxWidgets COMPONENTS core base gl QUIET)
    find_package(OpenSceneGraph COMPONENTS osg osgDB osgGA osgViewer osgVolume osgText QUIET)

    if(NOT wxWidgets_FOUND)
        message(WARNING "wxWidgets not found. Viewer will not be built.")
        message(STATUS "Install via: brew install wxwidgets (macOS) or apt install libwxgtk3.0-gtk3-dev (Linux)")
        set(BUILD_VIEWER OFF)
    endif()

    if(NOT OpenSceneGraph_FOUND)
        message(WARNING "OpenSceneGraph not found. Viewer will not be built.")
        message(STATUS "Install via: brew install open-scene-graph (macOS) or apt install libopenscenegraph-dev (Linux)")
        set(BUILD_VIEWER OFF)
    endif()
endif()

if(BUILD_CUDA)
    include(CheckLanguage)
    check_language(CUDA)

    if(CMAKE_CUDA_COMPILER)
        enable_language(CUDA)
        set(CMAKE_CUDA_STANDARD 17)
        set(CMAKE_CUDA_STANDARD_REQUIRED ON)

        # Modern CUDA architectures (adjust based on target GPUs)
        if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
            # Common modern architectures: Pascal, Volta, Turing, Ampere, Ada Lovelace, Hopper
            set(CMAKE_CUDA_ARCHITECTURES 60 70 75 80 86 89 90)
        endif()

        message(STATUS "CUDA support enabled - CUDA ${CMAKE_CUDA_COMPILER_VERSION}")
        message(STATUS "Target CUDA architectures: ${CMAKE_CUDA_ARCHITECTURES}")
    else()
        message(WARNING "CUDA compiler not found. CUDA features will be disabled.")
        message(STATUS "This is expected on macOS. Full functionality requires Linux/Windows with NVIDIA GPU.")
        set(BUILD_CUDA OFF)
    endif()
endif()

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Core libraries
add_subdirectory(src/common)
add_subdirectory(src/clustering)

if(BUILD_CUDA)
    add_subdirectory(src/cuda)
endif()

if(BUILD_VIEWER)
    add_subdirectory(src/viewer)
endif()

if(BUILD_CLI)
    add_subdirectory(src/cli)
endif()

# Installation
install(DIRECTORY data/
    DESTINATION share/seismic-occlusion-editor/data
    PATTERN "*.sgy" EXCLUDE
    PATTERN "*.vol" EXCLUDE
    PATTERN "*.raw" EXCLUDE)

# Print configuration summary
message(STATUS "")
message(STATUS "========================================")
message(STATUS "Seismic Occlusion Editor Configuration")
message(STATUS "========================================")
message(STATUS "Build type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard:      C++${CMAKE_CXX_STANDARD}")
if(BUILD_CUDA)
    message(STATUS "CUDA standard:     CUDA ${CMAKE_CUDA_STANDARD}")
    message(STATUS "CUDA compiler:     ${CMAKE_CUDA_COMPILER}")
endif()
message(STATUS "")
message(STATUS "Components:")
message(STATUS "  Viewer:          ${BUILD_VIEWER}")
message(STATUS "  CUDA:            ${BUILD_CUDA}")
message(STATUS "  CLI tools:       ${BUILD_CLI}")
message(STATUS "  Tests:           ${BUILD_TESTS}")
message(STATUS "  Documentation:   ${BUILD_DOCS}")
message(STATUS "========================================")
message(STATUS "")
