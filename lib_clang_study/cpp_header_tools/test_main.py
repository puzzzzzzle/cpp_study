import json


def fix_compile_db(db, old_path, new_path):
    pass


if __name__ == '__main__':
    with open("run_data/compile_commands.json") as f:
        db = json.load(f)
    for item in db:
        if item["file"].endwith("book_actor.h"):
            proc_item = item
            break
        raise RuntimeError("item not found")
    # proc_item = fix_compile_db(proc_item,"")

    pass
print(f"hello world")
pass
