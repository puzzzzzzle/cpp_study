from pathlib import Path
from pprint import pprint
import logging

import clang.cindex as cl

logger = logging.getLogger(__name__)


def get_diag_info(diag):
    return {
        "severity": diag.severity,
        "location": diag.location,
        "spelling": diag.spelling,
        "ranges": diag.ranges,
        "fixits": diag.fixits,
    }


def get_cursor_id(cursor, cursor_list=[]):
    if cursor is None:
        return None

    # FIXME: This is really slow. It would be nice if the index API exposed
    # something that let us hash cursors.
    for i, c in enumerate(cursor_list):
        if cursor == c:
            return i
    cursor_list.append(cursor)
    return len(cursor_list) - 1


def get_node_info(node):
    return {
        "id": get_cursor_id(node),
        "kind": node.kind,
        "usr": node.get_usr(),
        "spelling": node.spelling,
        "location": node.location,
        "extent.start": node.extent.start,
        "extent.end": node.extent.end,
        "is_definition": node.is_definition(),
        "definition id": get_cursor_id(node.get_definition()),
    }


def get_all_info(node):
    children = [get_all_info(c) for c in node.get_children()]
    return {
        "id": get_cursor_id(node),
        "kind": node.kind,
        "usr": node.get_usr(),
        "spelling": node.spelling,
        "location": node.location,
        "extent.start": node.extent.start,
        "extent.end": node.extent.end,
        "is_definition": node.is_definition(),
        "definition id": get_cursor_id(node.get_definition()),
        "children": children,
    }


def get_macro_instantiation(node, result):
    if result is None:
        result = []
    for child in node.get_children():
        get_macro_instantiation(child, result)
    if node.kind == cl.CursorKind.MACRO_INSTANTIATION:
        result.append(get_node_info(node))
    return result


class GeneratorMng:
    def __init__(self, cmd: str, src: str, templates, out_dir: str):
        self.cmd = cmd
        self.templates = templates
        self.out_dir = out_dir

        # get file name
        self.src = Path(src)
        assert self.src.is_file() and self.src.exists()
        self.file_name = self.src.stem
        logger.debug(f"file name {self.file_name}")

        # init out file
        self.out_header = Path(out_dir) / (self.file_name + ".generated.h")
        self.out_cpp = Path(out_dir) / (self.file_name + ".generated.cpp")
        with open(self.out_header, "w+t") as f:
            f.write("""
#define CH_CLASS(...) 
#define CH_GENERATED(...)
            """)
        pass
        with open(self.out_cpp, "w+t") as f:
            pass

    def gen(self):
        self.run_in_cpp()

        pass

    def run_in_cpp(self):
        index = cl.Index.create()
        args = self.cmd.split(" ")
        tu = index.parse(None, args, options=cl.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        if not tu:
            raise RuntimeError("parse cmd fail")
        pprint(("diags", [get_diag_info(d) for d in tu.diagnostics]))
        # pprint(("nodes", get_all_info(tu.cursor)))
        logger.debug(f"++++++++++")
        pprint(get_macro_instantiation(tu.cursor,None))

    pass
