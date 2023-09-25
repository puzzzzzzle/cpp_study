import json
import cpp_header_tools.cpp_header_tools as ch
from cpp_header_tools.tools.logger_init import init_logger

if __name__ == '__main__':
    init_logger("./")
    with open("/tmp/tmp.O6S6c6tjik/cmake-build-debug-dev-docker/compile_commands.json") as f:
        db = json.load(f)
    proc_item = None
    for item in db:
        name: str = item["file"]
        if name.endswith("book_actor.cpp"):
            proc_item = item
            break
    assert proc_item is not None
    ch.generated_one(proc_item["command"], proc_item["file"], "/tmp/tmp.O6S6c6tjik/src_lib_clang_study/generated_test/")
    # proc_item = fix_compile_db(proc_item,"")

    pass
pass
