# Seismic Occlusion Editor

GPU-accelerated volumetric occlusion-based classification for seismic and scientific data visualization.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CUDA](https://img.shields.io/badge/CUDA-11%2B-76B900.svg)](https://developer.nvidia.com/cuda-toolkit)

> **Developed as part of the [VRGEO Consortium](http://www.vrgeo.org/) at [Fraunhofer IAIS](https://www.iais.fraunhofer.de/)**
> Research on advanced visualization techniques for geoscientific 3D volume data

## Overview

This project implements a novel approach to volumetric data classification using GPU-accelerated occlusion generation. Originally developed as part of an MSc thesis (2012) within the VRGEO consortium at Fraunhofer IAIS, it has been modernized to use contemporary build systems and coding practices while maintaining the core research contributions.

### Key Features

- **Interactive 3D Volume Rendering** - Real-time ray-casting with OpenSceneGraph
- **CUDA-Accelerated Occlusion** - GPU kernels optimized with shared memory and texture caching
- **Transfer Function Editing** - Interactive histogram-based color mapping
- **Seismic Data Support** - Native SEG-Y format import with inline/crossline navigation
- **K-Means Clustering** - Automated feature classification
- **Cross-Platform** - Builds on Linux, macOS, and Windows


## Applications

- **Seismic Interpretation** - Analyze 3D seismic survey data
- **Medical Imaging** - CT/MRI volume visualization
- **Scientific Visualization** - Any volumetric dataset (geology, physics, etc.)

## Screenshots

<img width="1245" height="430" alt="SCR-20260131-ngkn" src="https://github.com/user-attachments/assets/9722c497-04f6-4431-870f-61625b17d0a8" />
<img width="1246" height="803" alt="SCR-20260131-ngho" src="https://github.com/user-attachments/assets/76dae45c-653a-4d57-9103-e1bcc8645c11" />

## Technical Highlights

### Occlusion-Based Classification

The core innovation is using local occlusion (visibility) as a feature for volumetric classification:

1. For each voxel, compute how much it is occluded by neighbors within a spherical radius
2. Apply a user-defined visibility transfer function
3. Use occlusion maps to enhance boundaries and structures in volume rendering
4. Classify features based on their occlusion characteristics

### GPU Optimization

- **Shared Memory Tiling** - 150x150 tiles to minimize global memory access
- **Texture Caching** - 3D texture sampling with hardware interpolation
- **Slice-Wise Processing** - Incremental occlusion computation with caching
- **Multiple Architectures** - Supports Pascal through Hopper GPUs (SM 60-90)

## Building from Source

### Prerequisites

**Required:**
- CMake 3.20+
- C++17 compliant compiler (GCC 7+, Clang 5+, MSVC 2019+)
- OpenGL 3.0+

**For GUI (Viewer):**
- wxWidgets 3.0+ (`brew install wxwidgets` on macOS, `apt install libwxgtk3.0-gtk3-dev` on Linux)
- OpenSceneGraph 3.4+ (`brew install open-scene-graph` on macOS, `apt install libopenscenegraph-dev` on Linux)

**For CUDA Acceleration (Optional):**
- CUDA Toolkit 11.0+ with compatible NVIDIA GPU
- Note: macOS does not support CUDA (viewer-only mode available)

### Quick Start

```bash
# Clone the repository
git clone https://github.com/yourusername/seismic-occlusion-editor.git
cd seismic-occlusion-editor

# Create build directory
mkdir build && cd build

# Configure (auto-detects available features)
cmake ..

# Build
cmake --build . -j$(nproc)

# Run the viewer
./bin/occlusion-viewer
```

### Build Options

```bash
# Build without CUDA (macOS or no GPU)
cmake .. -DBUILD_CUDA=OFF

# Build only CUDA kernels, skip GUI
cmake .. -DBUILD_VIEWER=OFF

# Build only the viewer, skip CLI tools
cmake .. -DBUILD_CLI=OFF

# Specify CUDA architectures (optional)
cmake .. -DCMAKE_CUDA_ARCHITECTURES="75;80;86"
```

### Platform-Specific Notes

#### macOS
```bash
# Install dependencies via Homebrew
brew install cmake wxwidgets open-scene-graph

# CUDA not available on macOS - build viewer only
cmake .. -DBUILD_CUDA=OFF
cmake --build .
```

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake
sudo apt install libwxgtk3.0-gtk3-dev libopenscenegraph-dev

# With CUDA (if NVIDIA GPU present)
# Install CUDA Toolkit from https://developer.nvidia.com/cuda-downloads
cmake ..
cmake --build .
```

#### Windows
```bash
# Use vcpkg for dependencies
vcpkg install wxwidgets openscenegraph

# Configure with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

## Usage

### Interactive Viewer

```bash
# Launch the viewer
./bin/occlusion-viewer

# Load a volume: File → Import → RAW or SEG-Y
# Adjust transfer function: Tools → Color Table Editor
# Generate occlusion: Tools → Occlusion Generation
# Configure visualization: View → Settings
```

### Command-Line Tool

```bash
# Basic usage
./bin/occgen-cli -w 256 -h 256 -d 256 -r 5 -s 1.0

Options:
  -w <width>    Volume width
  -h <height>   Volume height
  -d <depth>    Volume depth
  -r <radius>   Occlusion filter radius
  -s <scale>    Occlusion scale factor
```

## Supported File Formats

### Input Formats
- **RAW** - Unstructured binary volume data (8-bit or 16-bit)
- **SEG-Y** - Seismic Exchange Group format (IBM float or integer)
- **DDS** - DirectDraw Surface (for texture volumes)

### Output Formats
- **RAW** - Occlusion maps and processed volumes
- **Images** - Screenshots and depth buffers (PNG, TGA, BMP)

## Sample Data

Small test datasets are included in `data/samples/`:
- `cornell_128x128x128.raw` - Cornell box test volume (2 MB)
- `blobs_128x128x128.raw` - Synthetic blob test (2 MB)
- `test.sgy` - Small SEG-Y sample (3 MB)

Larger real-world datasets available separately:
- **Parihaka 3D** (2.5 GB) - New Zealand seismic survey
- **Unterhaching** (600 MB) - German geothermal seismic

## Project Structure

```
seismic-occlusion-editor/
├── CMakeLists.txt              # Root build configuration
├── src/
│   ├── viewer/                 # Interactive GUI application
│   ├── cuda/                   # CUDA occlusion kernels
│   ├── clustering/             # K-means clustering library
│   ├── common/                 # Shared utilities
│   └── cli/                    # Command-line tools
├── data/
│   ├── shaders/                # GLSL volume rendering shaders
│   ├── colortables/            # Transfer function presets (81 colormaps)
│   └── samples/                # Small test datasets
├── cmake/                      # CMake modules
└── docs/                       # Additional documentation
```

## Architecture

### Core Components

**Volume Rendering Pipeline:**
```
Volume File (SEG-Y/RAW)
    ↓
VolumeManager (CPU)
    ↓
RayCastTechnique (GPU)
    ├─ Intensity Texture (3D)
    ├─ Transfer Function (1D)
    └─ Occlusion Texture (3D)
    ↓
Ray-Casting Shader (GLSL)
    ↓
Frame Buffer
```

**Occlusion Generation:**
```
Input Volume
    ↓
bindVolume() - Upload to CUDA 3D texture
    ↓
bindMappingLookup() - Transfer function to device
    ↓
kernel() - Slice-wise occlusion computation
    ├─ Shared memory tiling
    ├─ Spherical neighborhood sampling
    └─ Cached incremental results
    ↓
Output Occlusion Map
```

### Key Classes

- **VolumeViewer** - OSG-based 3D viewer with trackball navigation
- **VolumeManager** - Volume data management and I/O
- **RayCastTechnique** - Custom OSG rendering technique
- **KMeansClusterer** - Feature-based segmentation
- **RawManager / SegyManager** - Format-specific loaders

## Performance

Typical performance on modern hardware (RTX 3080, 512³ volume):

| Operation | Time |
|-----------|------|
| Volume load (RAW) | 0.5s |
| Occlusion generation (radius 5) | 2.3s |
| Frame rendering (512 samples) | 16ms (60 FPS) |
| Transfer function update | <1ms |

## Research Background

This project originated from MSc thesis research on occlusion-based classification for seismic interpretation, conducted within the **VRGEO consortium** at **Fraunhofer IAIS** (Institute for Intelligent Analysis and Information Systems). The core contribution is using local visibility as a feature to distinguish geological structures.

**Original Development (2012):**
- **Institution**: Fraunhofer IAIS, Sankt Augustin, Germany
- **Project**: VRGEO - Virtual Reality for Geosciences
- **Thesis**: "Occlusion-Based Classification for Volumetric Data"
- **Focus**: Advanced visualization for seismic interpretation and geoscientific data analysis

**Modernization (2026):**
- Migrated from Visual Studio 2010 to CMake
- Updated CUDA 4.0 → CUDA 12
- C++03 → C++17
- Removed Windows-only dependencies
- Cross-platform support

## Contributing

This is primarily a portfolio project, but contributions are welcome:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## Future Work

Potential enhancements:

- [ ] Vulkan rendering backend
- [ ] Python bindings (pybind11)
- [ ] Web viewer (WebGPU/WebGL)
- [ ] Multi-GPU support
- [ ] HDF5 file format support
- [ ] Automated testing suite
- [ ] Docker containerization

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This work was conducted as part of the **VRGEO consortium** (Virtual Reality for Geosciences) at **Fraunhofer IAIS** (Institute for Intelligent Analysis and Information Systems), Sankt Augustin, Germany.

Special thanks to:
- **VRGEO consortium partners** for project support and collaboration
- **Fraunhofer IAIS** for providing research infrastructure and guidance
- OpenSceneGraph community for excellent 3D graphics framework
- NVIDIA CUDA team for GPU computing platform
- wxWidgets project for cross-platform GUI toolkit

## Citation

If you use this software in academic work, please cite:

```bibtex
@mastersthesis{panknin2012occlusion,
  title={Occlusion-Based Classification for Volumetric Data},
  author={Martin Panknin},
  year={2012},
  school={Fraunhofer IAIS},
  note={VRGEO Consortium - Virtual Reality for Geosciences}
}
```

## Contact

- **Author**: Martin Panknin
- **GitHub**: [@MPanknin](https://github.com/MPanknin)

---

**Built with** ❤️ **and CUDA**

