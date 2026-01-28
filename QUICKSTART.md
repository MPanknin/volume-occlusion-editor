# Quick Start Guide

Get up and running with the Seismic Occlusion Editor in 5 minutes.

## For Impatient Users (macOS)

```bash
# Install dependencies
brew install cmake wxwidgets open-scene-graph

# Clone and build
git clone https://github.com/yourusername/seismic-occlusion-editor.git
cd seismic-occlusion-editor
mkdir build && cd build
cmake .. -DBUILD_CUDA=OFF
cmake --build . -j$(sysctl -n hw.ncpu)

# Run
./bin/occlusion-viewer
```

## For Linux Users with NVIDIA GPU

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt update
sudo apt install build-essential cmake git
sudo apt install libwxgtk3.0-gtk3-dev libopenscenegraph-dev

# Install CUDA (if not already installed)
# Download from https://developer.nvidia.com/cuda-downloads

# Clone and build
git clone https://github.com/yourusername/seismic-occlusion-editor.git
cd seismic-occlusion-editor
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)

# Run
./bin/occlusion-viewer
```

## First Steps in the Viewer

### 1. Load a Sample Dataset

```
File → Import → RAW Volume
Navigate to: data/samples/cornell_128x128x128.raw
Set dimensions: 128 x 128 x 128
Data type: unsigned char (8-bit)
Click Import
```

### 2. Adjust Visualization

```
View → Settings
- Sample rate: 512 (higher = better quality, lower FPS)
- Intensity multiplier: 1.0-3.0 (brightness)
- Enable/disable clipping planes
```

### 3. Edit Transfer Function

```
Tools → Color Table Editor
- Click on histogram to add control points
- Drag points to adjust color mapping
- Right-click to remove points
- Load preset colortables from data/colortables/
```

### 4. Generate Occlusion (CUDA only)

```
Tools → Occlusion Generation
- Set radius: 3-7 (larger = smoother, slower)
- Define visibility mapping on histogram
- Click "Generate"
- View result in 3D viewer
```

### 5. Navigation

- **Rotate**: Left mouse drag
- **Zoom**: Scroll wheel
- **Pan**: Middle mouse drag or Shift+Left drag
- **Reset**: Press 'Home' key

## Loading Your Own Data

### RAW Format

Your data must be:
- Binary file with no header
- Known dimensions (width × height × depth)
- Known data type (8-bit or 16-bit unsigned)
- C-order memory layout (Z varies fastest)

Example for 256³ volume:
```bash
# Generate test data (256 MB)
dd if=/dev/urandom of=test_256.raw bs=1M count=256

# Load in viewer
File → Import → RAW Volume
Width: 256, Height: 256, Depth: 256
Data type: unsigned char
```

### SEG-Y Format

The viewer supports standard SEG-Y seismic format:
```
File → Import → SEG-Y
Select your .sgy file
Parser will auto-detect inline/crossline/time dimensions
```

## Command-Line Tool (CUDA builds only)

```bash
# Basic usage
./bin/occgen-cli -w 256 -h 256 -d 256 -r 5

# Help
./bin/occgen-cli --help
```

Note: The CLI is simplified. For full functionality, use the viewer.

## Troubleshooting

### "wxWidgets not found"
```bash
# macOS
brew install wxwidgets

# Linux
sudo apt install libwxgtk3.0-gtk3-dev
```

### "OpenSceneGraph not found"
```bash
# macOS
brew install open-scene-graph

# Linux
sudo apt install libopenscenegraph-dev
```

### "CUDA compiler not found"
This is expected on macOS. Build with `-DBUILD_CUDA=OFF`:
```bash
cmake .. -DBUILD_CUDA=OFF
```

### Viewer crashes on startup
Check OpenGL support:
```bash
# Linux
glxinfo | grep "OpenGL version"

# macOS
system_profiler SPDisplaysDataType | grep "OpenGL"
```

Minimum: OpenGL 3.0

### Build errors with C++17
Ensure you have a modern compiler:
- GCC 7+
- Clang 5+
- MSVC 2019+
- Xcode 10+ (macOS)

## Next Steps

- Read [README.md](README.md) for detailed documentation
- Check [ARCHITECTURE.md](docs/ARCHITECTURE.md) for system design
- See [CONTRIBUTING.md](CONTRIBUTING.md) to contribute
- Review [MIGRATION_NOTES.md](MIGRATION_NOTES.md) for history

## Getting Help

- Open an issue on GitHub
- Check existing issues for similar problems
- Provide system info (OS, GPU, CUDA version) when reporting bugs

## Sample Workflows

### Seismic Interpretation
```
1. Load SEG-Y volume
2. Navigate using inline/crossline/timeslice
3. Adjust transfer function to highlight features
4. Generate occlusion to enhance boundaries
5. Export screenshots or depth maps
```

### Medical Imaging
```
1. Load CT/MRI RAW volume
2. Use "Altimetric" or "Depth" color table
3. Set appropriate intensity window
4. Enable iso-surface rendering
5. Export visualizations
```

### Scientific Visualization
```
1. Load custom RAW dataset
2. Experiment with different colortables (81 presets)
3. Use K-means clustering for feature classification
4. Generate occlusion for structure enhancement
5. Extract regions of interest
```

## Performance Tips

### For Better FPS
- Lower sample rate (256 instead of 512)
- Reduce volume dimensions
- Disable occlusion overlay
- Use simpler transfer functions

### For Better Quality
- Increase sample rate (512 or 1024)
- Enable gradient-based lighting
- Use smooth transfer functions
- Higher resolution volumes

### For Faster Occlusion
- Smaller radius (3-5)
- Lower resolution volumes
- Use newer GPU (Ampere/Ada/Hopper)
- Ensure CUDA build is optimized (Release mode)

## Common Parameters

### Recommended Occlusion Radius
- **Small features** (< 10 voxels): radius 2-3
- **Medium features** (10-50 voxels): radius 5-7
- **Large features** (50+ voxels): radius 10-15

### Sample Rate Guidelines
- **Interactive exploration**: 128-256 samples
- **Good quality**: 512 samples
- **Publication quality**: 1024-2048 samples

### Transfer Function Tips
- **Start simple**: 3-5 control points
- **Highlight features**: Sharp transitions
- **Smooth visualization**: Gradual gradients
- **Seismic data**: Use "SeismicRamp" preset

---

**Ready to dive deeper?** Check out the [full documentation](README.md)!
