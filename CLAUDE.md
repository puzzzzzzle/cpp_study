# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

A C++ study/learning repository organized into independent subprojects covering algorithms, language features, Boost libraries, Linux system programming, and third-party library experiments. Subprojects change frequently — don't assume a fixed list.

## Build System

CMake 3.22+ with automatic subproject discovery. Each directory containing a `CMakeLists.txt` under the `src_*` roots becomes an independent build target.

```bash
# Configure (from repo root)
mkdir -p build && cd build && cmake ..

# Build a specific target — target name is relative path with / replaced by _
make src_algorithm_aoi_orthogonal_list_aoi

# List all available targets
make help

# Release build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

Binary naming convention: `src_linux_tests/src/asm/at_t_asm/c_call_asm` → target `src_linux_tests_src_asm_at_t_asm_c_call_asm`. Binaries output to `build/bin/`.

### Dependencies

- Dependencies managed via Docker (see `cpp_bootstrap/Docker/arch_clion_local.Dockerfile`)
- Optional Conan support: `cd build && conan install .. --build missing`
- `cpp_bootstrap` is a git submodule — clone with `--recursive` or run `git submodule update --init`
- Required: GTest, pthread. Optional: Boost (static linking by default)

### C++ Standard

Auto-detected by CMake: tries C++23 first, falls back to C++20, then C++17.

## Creating, Building, and Running a Subproject

### Create

Copy `_template/` into any `src_*` directory (or use `/new-subproject` skill):

```bash
cp -r _template src_algorithm/my_new_project
```

The template contains `CMakeLists.txt` and a GTest `main.cpp`. `CURRENT_TASK` is automatically set by the build system to the underscore-joined relative path (e.g. `src_algorithm/my_new_project` → `src_algorithm_my_new_project`).

Template `CMakeLists.txt`:

```cmake
aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})
target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS})
```

### Build

新增子工程后需要重新 cmake 生成（增量 cmake 偶尔不能识别新目录，`rm -rf build/*` 后重新 cmake 可解决）：

```bash
cd build && rm -rf * && cmake .. && make <target_name> -j$(nproc)
```

日常修改代码后直接 make 即可：

```bash
cd build && make <target_name> -j$(nproc)
```

### Run

二进制输出到 `build/bin/`，直接执行：

```bash
./build/bin/<target_name>
```

GTest 支持 `--gtest_filter` 运行单个测试：

```bash
./build/bin/<target_name> --gtest_filter=SuiteName.CaseName
```

## Key CMake Functions (cpp_bootstrap/common/CMake/FuncDefs.cmake)

- `AddAllSubDir()` — recursively discovers and adds all subprojects under `SRC_DIR_ROOTS`
- `SetCommonBuildFlag()` — platform-specific flags (Debug: `-ggdb3 -g3 -fno-omit-frame-pointer`, Release: `-O3`)
- `FindCommonLib()` — finds GTest, pthread, optional Boost; populates `COMMON_LIBS`
- `OpenAsmSupport()` — enables NASM and GAS assembler for assembly subprojects
- `OpenCoroutine()` — adds `-fcoroutines` flag for coroutine subprojects

## Testing

Uses Google Test. Most subprojects follow a GTest main pattern:

```cpp
#include "common_includes.h"  // includes gtest, logging, quick_define macros

TEST(suite, case) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

Run a test by building and executing the target binary directly: `./build/bin/<target_name>`

## Common Headers (cpp_bootstrap/common/common_include/)

- `common_includes.h` — umbrella header pulling in GTest, logging, and utility macros
- `log_init.h` / `quick_define.h` / `stl_to_steam.h` — logging setup, convenience macros, STL stream operators

## Code Style

- `.clang-format`: Google base style, 120 column limit, Allman-style braces, C++11 formatting
- `.clangd`: clang-tidy enabled with `performance-*`, `modernize-*`, `bugprone-*`, `readability-*`, `cppcoreguidelines-*` checks; strict unused-include detection

## Repository Layout

| Directory | Content |
|---|---|
| `src_algorithm/` | Data structures and algorithms (AOI, pathfinding, ring buffer, object pool, etc.) |
| `src_boost_study/` | Boost library experiments (Asio, Interprocess, Lockfree, Serialization, etc.) |
| `src_cpp_language/` | Core C++ features (templates, memory, concurrency, STL, vtable, etc.) |
| `src_cpp_tools/` | Meta-programming and utility tools |
| `src_cxx_newest_20/` | C++20 features (coroutines, ranges, concepts) |
| `src_cxx_newest_23/` | C++23 features (modules) |
| `src_lib_tests/` | Third-party library tests (protobuf, rocksdb, SIMD, asio, spdlog, etc.) |
| `src_linux_tests/` | Linux system programming (assembly, io_uring, dynamic loading) |
| `src_linux_driver/` | Linux kernel driver development |
| `src_old_uinx_study/` | Legacy Unix/POSIX (socket, epoll, select) |
| `cpp_bootstrap/` | Shared CMake functions, common headers, Docker configs (git submodule) |
| `_template/` | Template for new subprojects |
