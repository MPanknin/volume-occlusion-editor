# Contributing to Seismic Occlusion Editor

Thank you for your interest in contributing! This document provides guidelines for contributing to the project.

## Code of Conduct

- Be respectful and inclusive
- Focus on constructive feedback
- Help others learn and grow

## How to Contribute

### Reporting Bugs

If you find a bug, please open an issue with:
- Clear description of the problem
- Steps to reproduce
- Expected vs actual behavior
- System information (OS, GPU, CUDA version)
- Error messages or logs

### Suggesting Features

Feature requests are welcome! Please:
- Check if the feature already exists or is planned
- Clearly describe the use case
- Explain why it would be valuable

### Pull Requests

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/my-new-feature
   ```
3. **Make your changes**
   - Follow existing code style
   - Add comments for complex logic
   - Update documentation as needed
4. **Test your changes**
   - Ensure the project builds successfully
   - Test on your target platform
5. **Commit with clear messages**
   ```bash
   git commit -m "Add feature: brief description"
   ```
6. **Push to your fork**
   ```bash
   git push origin feature/my-new-feature
   ```
7. **Open a Pull Request**
   - Describe what changed and why
   - Reference any related issues

## Development Setup

### Prerequisites
- CMake 3.20+
- C++17 compiler
- Git

### Building
```bash
git clone https://github.com/yourusername/seismic-occlusion-editor.git
cd seismic-occlusion-editor
mkdir build && cd build
cmake ..
cmake --build .
```

## Code Style

### C++
- Use C++17 features where appropriate
- Follow existing naming conventions:
  - Classes: `PascalCase`
  - Functions: `camelCase`
  - Variables: `camelCase`
  - Constants: `UPPER_SNAKE_CASE`
- Add comments for non-obvious code
- Keep functions focused and reasonably sized

### CUDA
- Document kernel launch parameters
- Explain shared memory usage
- Note performance considerations

### CMake
- Use modern CMake (3.20+) patterns
- Clearly separate public and private dependencies
- Add comments for complex logic

## Testing

Currently, the project uses manual testing. Automated tests are welcome contributions!

Areas that would benefit from tests:
- Volume loading (RAW, SEG-Y)
- CUDA kernel correctness
- Transfer function generation
- Clustering algorithms

## Documentation

When adding features:
- Update README.md if user-visible
- Add inline code comments
- Consider adding to docs/ folder for detailed explanations

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

## Questions?

Feel free to open an issue for any questions about contributing!
