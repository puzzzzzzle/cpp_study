import json
from pathlib import Path

import cpp_header_tools.cpp_header_tools as ch
from cpp_header_tools.tools.logger_init import init_logger


def fix_path(cmd: str, old, new):
    return cmd.replace(old, new)


def win_main():
    win_path = Path("../..").absolute()
    linux_path = "/tmp/cpp_study"
    cmake_dir = "cmake-build-debug-docker"
    with open(win_path / cmake_dir / "compile_commands.json") as f:
        db = json.load(f)
    proc_item = None
    for item in db:
        name: str = item["file"]
        if name.endswith("book_actor.cpp"):
            proc_item = item
            break
    assert proc_item is not None
    cmd = fix_path(proc_item["command"], linux_path, str(win_path))
    src = fix_path(proc_item["file"], linux_path, str(win_path))
    out = win_path / "src_lib_clang_study/generated_test/"
    ch.generated_one(cmd, src, out)
    # proc_item = fix_compile_db(proc_item,"")


def linux_main():
    cmd_db = Path("/tmp/tmp.O6S6c6tjik/cmake-build-debug-docker/")
    with open(cmd_db / "compile_commands.json") as f:
        db = json.load(f)
    proc_item = None
    for item in db:
        name: str = item["file"]
        if name.endswith("book_actor.cpp"):
            proc_item = item
            break
    assert proc_item is not None
    cmd = proc_item["command"]
    src = proc_item["file"]
    out = Path("/tmp/tmp.O6S6c6tjik/") / "src_lib_clang_study/generated_test/"
    ch.generated_one(cmd, src, out)
    import clang.cindex as cl
    index = cl.Index.create()

    # Step 1: load the compilation database
    compdb:cl.CompilationDatabase = cl.CompilationDatabase.fromDirectory(str(cmd_db))
    pass


if __name__ == '__main__':
    init_logger("./log/")
    # win_main()
    linux_main()
