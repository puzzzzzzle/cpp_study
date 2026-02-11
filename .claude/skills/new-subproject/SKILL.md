---
name: new-subproject
description: Create a new C++ subproject by copying _template/ to a target path. Use when the user asks to "create a new subproject", "add a new project", "new module", "scaffold a project", or wants to start a new coding exercise/study in this repo.
tools: Bash, Read, Write, Edit
---

# New Subproject Skill

Create a new C++ subproject in this repository by copying `_template/` to the target directory.

## Instructions

1. Determine the target path from the user's request.

2. Validate the target path:
   - It must be a relative path under one of the `src_*` directories (e.g. `src_algorithm/`, `src_cpp_language/`, `src_lib_tests/`, etc.)
   - If the user provides only a name without a `src_*` prefix, ask which `src_*` directory to place it in
   - If the target directory already exists, warn the user and ask for confirmation before overwriting

3. Copy the template:
   - Copy `_template/CMakeLists.txt` and `_template/main.cpp` to the target directory
   - Create any intermediate directories as needed

4. After copying, inform the user:
   - The build target name (relative path with `/` replaced by `_`, e.g. `src_algorithm_my_new_algo`)
   - How to build: `cd build && cmake .. && make <target_name>`
   - How to run: `./build/bin/<target_name>`
