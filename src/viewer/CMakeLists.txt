if(NOT BUILD_VIEWER)
    message(FATAL_ERROR "Viewer build is disabled but this target was requested")
endif()

# Find required dependencies
find_package(wxWidgets REQUIRED COMPONENTS core base gl)
find_package(OpenSceneGraph REQUIRED COMPONENTS
    osg osgDB osgGA osgViewer osgVolume osgText osgUtil)
find_package(OpenGL REQUIRED)

include(${wxWidgets_USE_FILE})

# Collect all source files
file(GLOB VIEWER_SOURCES
    "*.cpp"
    "*.h")

# Exclude files that require optional dependencies or are orphaned
list(REMOVE_ITEM VIEWER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/LocalhistTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RawLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SegyLoader.cpp")

# Create viewer executable
add_executable(occlusion-viewer ${VIEWER_SOURCES})

# Include directories
target_include_directories(occlusion-viewer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${wxWidgets_INCLUDE_DIRS}
    ${OPENSCENEGRAPH_INCLUDE_DIRS})

# Link libraries
target_link_libraries(occlusion-viewer PRIVATE
    common
    clustering
    ${wxWidgets_LIBRARIES}
    ${OPENSCENEGRAPH_LIBRARIES}
    OpenGL::GL
    ${CMAKE_DL_LIBS})

# Optionally link CUDA if available
if(BUILD_CUDA)
    target_link_libraries(occlusion-viewer PRIVATE occgen_cuda)
    target_compile_definitions(occlusion-viewer PRIVATE HAVE_CUDA)
endif()

# Platform-specific settings
if(APPLE)
    set_target_properties(occlusion-viewer PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in)
endif()

# Compiler flags
target_compile_options(occlusion-viewer PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wno-deprecated -Wno-unused-parameter>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4996>)

# Installation
install(TARGETS occlusion-viewer
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION bin)

# Install data files alongside executable
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
    DESTINATION bin/data
    PATTERN "*.sgy" EXCLUDE
    PATTERN "*.vol" EXCLUDE)
