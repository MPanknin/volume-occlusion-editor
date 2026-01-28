add_library(common INTERFACE)

target_include_directories(common INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

# Install headers
install(DIRECTORY include/
    DESTINATION include/seismic-occlusion-editor
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
