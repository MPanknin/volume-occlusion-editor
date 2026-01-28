add_library(clustering STATIC
    Clusterer.cpp
    Clusterer.h
    KMeansClusterer.cpp
    KMeansClusterer.h)

target_include_directories(clustering PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(clustering PUBLIC common)

# Installation
install(TARGETS clustering
    EXPORT SeismicOcclusionEditorTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(FILES
    Clusterer.h
    KMeansClusterer.h
    DESTINATION include/seismic-occlusion-editor/clustering)
