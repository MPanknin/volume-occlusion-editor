#!/bin/bash

# Build Verification Script
# Tests that the project builds correctly on the current platform

set -e  # Exit on error

echo "=========================================="
echo "Seismic Occlusion Editor - Build Verification"
echo "=========================================="
echo ""

# Detect platform
OS="Unknown"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    OS="Windows"
fi

echo "Detected OS: $OS"
echo ""

# Check for required tools
echo "Checking prerequisites..."

command -v cmake >/dev/null 2>&1 || { echo "❌ cmake not found. Install with: brew install cmake (macOS) or apt install cmake (Linux)"; exit 1; }
echo "✅ CMake found: $(cmake --version | head -n1)"

command -v git >/dev/null 2>&1 || { echo "❌ git not found"; exit 1; }
echo "✅ Git found: $(git --version)"

# Check C++ compiler
if command -v g++ >/dev/null 2>&1; then
    echo "✅ C++ compiler found: $(g++ --version | head -n1)"
elif command -v clang++ >/dev/null 2>&1; then
    echo "✅ C++ compiler found: $(clang++ --version | head -n1)"
else
    echo "❌ No C++ compiler found"
    exit 1
fi

# Check for CUDA (optional)
if command -v nvcc >/dev/null 2>&1; then
    echo "✅ CUDA found: $(nvcc --version | grep release)"
    CUDA_AVAILABLE=true
else
    echo "⚠️  CUDA not found (optional)"
    CUDA_AVAILABLE=false
fi

echo ""
echo "Checking for GUI dependencies..."

# Platform-specific dependency checks
if [[ "$OS" == "Linux" ]]; then
    if dpkg -l | grep -q libwxgtk; then
        echo "✅ wxWidgets found"
    else
        echo "⚠️  wxWidgets not found. Install with: sudo apt install libwxgtk3.0-gtk3-dev"
    fi

    if dpkg -l | grep -q libopenscenegraph; then
        echo "✅ OpenSceneGraph found"
    else
        echo "⚠️  OpenSceneGraph not found. Install with: sudo apt install libopenscenegraph-dev"
    fi
elif [[ "$OS" == "macOS" ]]; then
    if brew list wxwidgets >/dev/null 2>&1; then
        echo "✅ wxWidgets found"
    else
        echo "⚠️  wxWidgets not found. Install with: brew install wxwidgets"
    fi

    if brew list open-scene-graph >/dev/null 2>&1; then
        echo "✅ OpenSceneGraph found"
    else
        echo "⚠️  OpenSceneGraph not found. Install with: brew install open-scene-graph"
    fi
fi

echo ""
echo "=========================================="
echo "Starting build..."
echo "=========================================="
echo ""

# Create build directory
BUILD_DIR="build_test"
if [ -d "$BUILD_DIR" ]; then
    echo "Removing existing test build directory..."
    rm -rf "$BUILD_DIR"
fi

mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure
echo "Configuring CMake..."
if [[ "$OS" == "macOS" ]]; then
    # macOS: CUDA not supported
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_CUDA=OFF
else
    # Linux/Windows: Enable CUDA if available
    if $CUDA_AVAILABLE; then
        cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_CUDA=ON
    else
        cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_CUDA=OFF
    fi
fi

if [ $? -ne 0 ]; then
    echo ""
    echo "❌ CMake configuration failed"
    echo "Check the error messages above for missing dependencies"
    exit 1
fi

echo ""
echo "Building..."

# Determine number of cores
if [[ "$OS" == "macOS" ]]; then
    CORES=$(sysctl -n hw.ncpu)
else
    CORES=$(nproc)
fi

cmake --build . -j${CORES}

if [ $? -ne 0 ]; then
    echo ""
    echo "❌ Build failed"
    echo "Check the error messages above"
    exit 1
fi

echo ""
echo "=========================================="
echo "Build Successful! ✅"
echo "=========================================="
echo ""

# List built executables
echo "Built executables:"
if [ -f "bin/occlusion-viewer" ] || [ -f "bin/Release/occlusion-viewer.exe" ]; then
    echo "  ✅ occlusion-viewer"
fi
if [ -f "bin/occgen-cli" ] || [ -f "bin/Release/occgen-cli.exe" ]; then
    echo "  ✅ occgen-cli"
fi

echo ""
echo "To run the viewer:"
if [[ "$OS" == "Windows" ]]; then
    echo "  cd build_test/bin/Release && ./occlusion-viewer.exe"
else
    echo "  ./build_test/bin/occlusion-viewer"
fi

echo ""
echo "To use the production build:"
echo "  mkdir build && cd build"
echo "  cmake .. -DCMAKE_BUILD_TYPE=Release"
echo "  cmake --build . -j${CORES}"

echo ""
echo "Build verification complete!"
