import json
import cpp_header_tools.cpp_header_tools as ch

if __name__ == '__main__':
    with open("../../cmake-build-debug-docker/compile_commands.json") as f:
        db = json.load(f)
    proc_item = None
    for item in db:
        name: str = item["file"]
        print(f"{name}")
        if name.endswith("book_actor.cpp"):
            proc_item = item
            break
    assert proc_item is not None
    ch.generated_one(proc_item["command"], proc_item["file"])
    # proc_item = fix_compile_db(proc_item,"")

    pass
print(f"hello world")
pass
