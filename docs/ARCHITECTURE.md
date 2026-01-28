# Architecture Overview

This document describes the high-level architecture of the Seismic Occlusion Editor.

## System Components

```
┌─────────────────────────────────────────────────────────┐
│                  User Interface Layer                    │
│  (wxWidgets GUI - UIContainer, UIColorTable, etc.)      │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│              Visualization Layer                         │
│  (OpenSceneGraph - VolumeViewer, RayCastTechnique)     │
└────────────┬───────────────────────┬────────────────────┘
             │                       │
             ▼                       ▼
┌────────────────────┐    ┌────────────────────────────┐
│  Volume Manager    │    │   Rendering Pipeline       │
│  (Data I/O)        │    │   (GPU Shaders)            │
│  - RAW Loader      │    │   - Ray Casting            │
│  - SEG-Y Loader    │    │   - Transfer Functions     │
│  - Data Cache      │    │   - Lighting               │
└────────┬───────────┘    └────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────────────────────┐
│              Computation Layer                           │
│                                                          │
│  ┌─────────────────┐      ┌──────────────────────┐     │
│  │ CUDA Kernels    │      │ CPU Algorithms       │     │
│  │ - Occlusion Gen │      │ - K-Means Clustering │     │
│  │ - Local Hist    │      │ - Histogram Gen      │     │
│  └─────────────────┘      └──────────────────────┘     │
└─────────────────────────────────────────────────────────┘
```

## Key Classes

### Visualization

**VolumeViewer**
- Manages OSG viewer instance
- Handles user interaction (trackball, picking)
- Coordinates between UI and rendering

**RayCastTechnique**
- Custom OSG volume rendering technique
- Manages GPU textures (intensity, transfer, occlusion)
- Configures shader uniforms
- Handles clipping planes

**VoxelSlice**
- Renders 2D slice lines (inline, crossline, timeslice)
- Provides seismic-style navigation

### Data Management

**VolumeManager**
- Central data management (singleton pattern)
- Loads and caches volume data
- Computes occlusion (CPU or GPU)
- Manages multiple volumes (intensity + occlusion)

**RawManager / SegyManager**
- Format-specific loaders
- Parse headers and trace data
- Convert to internal representation

### User Interface

**UIContainer**
- Main application window
- Coordinates all UI panels
- Manages application state

**UIColorTable**
- Transfer function editor
- Histogram visualization
- Control point manipulation

**UIOcclusionGeneration**
- Interface for occlusion parameters
- Visibility mapping configuration
- Real-time preview

### Computation

**CUDA Kernels (kernel.cu)**
- `d_occ()` - Main occlusion kernel with shared memory
- `bindVolume()` - Upload data to GPU texture
- `bindMappingLookup()` - Transfer function to device

**KMeansClusterer**
- Feature-based segmentation
- Configurable cluster count
- Automatic centroid calculation

## Data Flow

### Volume Loading
```
File (RAW/SEG-Y)
  ↓ [RawManager/SegyManager]
Volume Data (CPU)
  ↓ [VolumeManager]
OSG Image
  ↓ [RayCastTechnique]
3D Texture (GPU)
```

### Occlusion Generation
```
User Defines Visibility Mapping
  ↓ [UIOcclusionGeneration]
Configuration File (vis.cfg)
  ↓ [VolumeManager]
bindVolume() + bindMappingLookup()
  ↓ [CUDA]
kernel() - Compute Occlusion
  ↓
Occlusion Map (GPU/CPU)
  ↓ [RayCastTechnique]
Occlusion Texture (GPU)
```

### Rendering Pipeline
```
Camera Position
  ↓ [VolumeViewer]
Ray Generation
  ↓ [GLSL Vertex Shader]
Ray Marching (512 samples)
  ↓ [GLSL Fragment Shader]
  ├─ Sample Intensity Texture
  ├─ Apply Transfer Function
  ├─ Sample Occlusion Texture
  ├─ Compute Gradient (Lighting)
  └─ Accumulate Color/Alpha
  ↓
Frame Buffer
```

## Threading Model

- **Main Thread**: UI event handling, OSG rendering
- **CUDA Streams**: Asynchronous kernel launches (potential future enhancement)
- **Worker Threads**: File I/O (currently synchronous, could be improved)

## Memory Management

### CPU
- OSG ref_ptr<> for automatic reference counting
- STL containers for data structures
- Manual allocation for large volumes (consider std::vector migration)

### GPU
- CUDA managed memory for occlusion cache
- 3D texture memory for volumes
- Device constant memory for lookup tables

## Performance Considerations

### Bottlenecks
1. **Volume Loading**: I/O bound, could benefit from async loading
2. **Occlusion Generation**: Memory bound, optimized with caching
3. **Rendering**: Fill rate bound, 512 samples per ray

### Optimizations
- Shared memory tiling in CUDA kernels
- Texture hardware for interpolation
- Slice-wise occlusion with caching
- Early ray termination in shader

## Extension Points

### Adding New File Formats
1. Create new loader class (inherit from base pattern)
2. Implement header parsing and data extraction
3. Register with VolumeManager
4. Add UI import dialog

### Adding New Visualization Techniques
1. Create OSG technique class (inherit from osgVolume::VolumeTechnique)
2. Implement shader programs
3. Configure textures and uniforms
4. Register with volume tile

### Adding New Occlusion Algorithms
1. Implement CUDA kernel in new .cu file
2. Add wrapper function (extern "C")
3. Update VolumeManager to call new kernel
4. Add UI controls if needed

## Dependencies Graph

```
viewer
  ├─ wxWidgets (GUI)
  ├─ OpenSceneGraph (3D rendering)
  ├─ OpenGL (GPU graphics)
  ├─ clustering (K-means)
  ├─ common (utilities)
  └─ occgen_cuda (optional, occlusion)

occgen_cuda
  ├─ CUDA Toolkit (GPU compute)
  └─ common (utilities)

clustering
  └─ common (utilities)
```

## Build System

CMake manages the build with these key targets:

- **common**: Header-only utility library
- **clustering**: Static library for K-means
- **occgen_cuda**: Static library for CUDA kernels (optional)
- **occlusion-viewer**: Main executable (GUI)
- **occgen-cli**: Command-line tool (optional)

Conditional compilation based on:
- `BUILD_VIEWER` - GUI dependencies available
- `BUILD_CUDA` - CUDA toolkit present
- `BUILD_CLI` - Command-line tools
- `HAVE_CUDA` - Preprocessor define in viewer

## Future Architectural Improvements

1. **Async I/O**: Load volumes in background thread
2. **Plugin System**: Dynamic loading of file format handlers
3. **GPU Streaming**: Process volumes larger than GPU memory
4. **Multi-GPU**: Distribute occlusion computation
5. **Web Backend**: Separate rendering from UI (REST API)
6. **State Management**: Save/load full application state
