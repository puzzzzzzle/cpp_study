---
description: Create a new subproject by copying _template/ to the target path
argument-hint: <target-path> (e.g. src_algorithm/my_new_algo)
allowed-tools: ["Bash", "Read", "Write", "Edit"]
---

Create a new C++ subproject in this repository.

## Instructions

The user wants to create a new subproject at: $ARGUMENTS

1. Validate the target path:
   - It must be a relative path under one of the `src_*` directories (e.g. `src_algorithm/`, `src_cpp_language/`, `src_lib_tests/`, etc.)
   - If the user provides only a name without a `src_*` prefix, ask which `src_*` directory to place it in
   - If the target directory already exists, warn the user and ask for confirmation before overwriting

2. Copy the template:
   - Copy `_template/CMakeLists.txt` and `_template/main.cpp` to the target directory
   - Create any intermediate directories as needed

3. After copying, inform the user:
   - The build target name (relative path with `/` replaced by `_`, e.g. `src_algorithm_my_new_algo`)
   - How to build: `cd build && cmake .. && make <target_name>`
   - How to run: `./build/bin/<target_name>`
