import json
from pathlib import Path

import cpp_header_tools.cpp_header_tools as ch
from cpp_header_tools.tools.logger_init import init_logger


def fix_path(cmd: str, old, new):
    return cmd.replace(old, new)


if __name__ == '__main__':
    init_logger("./log/")
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

    pass
    pass
