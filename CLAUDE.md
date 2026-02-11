# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C++ study repository containing various algorithm implementations, C++ language feature tests, and experimental code. The project uses CMake for building, with Docker support for development environments.

## Build System

### Development Environment
- **Docker-based development**: Dependencies are defined in `cpp_bootstrap/Docker/arch_clion_local.Dockerfile`
- **Dependencies**: Boost, GTest, OpenCV, and various system libraries installed via Arch Linux pacman

### Building the Project
1. **Standard build**:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make TARGET
   ```
   - Binary names are created by converting directory paths: `/` replaced with `_`
   - Example: `make src_linux_tests_src_asm_at_t_asm_c_call_asm`

### Project Structure
The CMake build system automatically scans and builds subdirectories containing `CMakeLists.txt` files within these root directories:
- `src_algorithm/`: Algorithm implementations (AOI systems, graph algorithms, data structures)
- `src_boost_study/`: Boost library experiments
- `src_cpp_language/`: C++ language feature tests
- `src_cpp_tools/`: C++ utility classes
- `src_cxx_newest_20/`: C++20 feature experiments
- `src_cxx_newest_23/`: C++23 feature experiments
- `src_lib_tests/`: Third-party library tests (spdlog, protobuf, asio, etc.)
- `src_linux_tests/`: Linux system programming and assembly tests
- `src_old_uinx_study/`: Legacy Unix programming studies
- `src_linux_driver/`: Linux kernel module experiments

### Target Naming Convention
Executable targets are automatically named by converting directory paths to underscores:
- Example: `src_algorithm/aoi/orthogonal_list_aoi/` → `src_algorithm_aoi_orthogonal_list_aoi`
- Full target list available in the build directory's Makefile

## Development Patterns

### Adding New Code
1. **Manual creation**:
   - Create a new directory with a `CMakeLists.txt` file (use `_template/` as reference)
   - Place source files in the directory
   - The build system automatically discovers and builds it

### CMakeLists.txt Template
```cmake
aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# Executable
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})

# Link common libraries
target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS})
```

### Build System Features
- **Automatic subdirectory discovery**: CMake scans specified root directories for `CMakeLists.txt` files
- **Common build flags**: Set in `cpp_bootstrap/common/CMake/FuncDefs.cmake`
- **Assembly support**: NASM and GAS assembly via `OpenAsmSupport()` function
- **Compile commands**: Exported for tooling integration (`CMAKE_EXPORT_COMPILE_COMMANDS ON`)

## Key Directories

### `cpp_bootstrap/`
Build system utilities and Docker configurations:
- `common/CMake/FuncDefs.cmake`: Core CMake functions for project setup
- `Docker/`: Dockerfiles for development environments
- Automatic subdirectory discovery and target creation

### `data/`
Runtime configuration files (e.g., `boost_log_settings.ini`)

### `_template/`
Template for new project directories

### `cmake_install_template/`
Example of creating installable CMake packages

## Testing

### Test Structure
- Tests are integrated into executable targets
- GTest is available for unit testing
- Test files follow naming patterns: `*test*.cpp`, `*Test*.cpp`, `*_test.cpp`

### Running Tests
1. Build the project: `cd build && make`
2. Executables are placed in `build/bin/`
3. Run individual test executables directly

## Development Tools

### VS Code Configuration
- Launch configuration in `.vscode/launch.json` for debugging
- Build tasks integrated with CMake

### Code Formatting
- `.clang-format` file for consistent code style

### Git Submodules
- Submodules are used for `cpp_bootstrap/` build utilities

## Notes

- The project extensively uses modern C++ features (C++20/23)
- Assembly language support includes both AT&T and NASM syntax
- Multiple concurrency models tested: libgo, libco, Boost.Coroutine, C++20 coroutines
- Linux-specific features: io_uring, kernel modules, system calls
- Binary output is centralized in `build/bin/`
- Each subdirectory is an independent build target