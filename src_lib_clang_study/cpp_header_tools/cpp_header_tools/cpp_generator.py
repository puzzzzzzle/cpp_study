from pathlib import Path
import logging
from pprint import pprint

import clang.cindex as cl

from cpp_header_tools.tools.show_info_tools import *

logger = logging.getLogger(__name__)


def get_macro_instantiation(node, result):
    if result is None:
        result = []
    for child in node.get_children():
        get_macro_instantiation(child, result)
    if node.kind == cl.CursorKind.MACRO_INSTANTIATION:
        result.append(get_node_info(node))
    return result


class Generator:
    """
    generator for one compile unit
    """

    def __init__(self, cmd: str, src: str, templates, out_header_dir: str):
        self.cpp_tu = None
        self.cmd = cmd
        self.templates = templates
        self.out_dir = out_header_dir

        # get file name
        self.src = Path(src)
        assert self.src.is_file() and self.src.exists()
        self.file_name = self.src.stem
        logger.debug(f"file name {self.file_name}")

        # init out file
        self.out_header = Path(out_header_dir) / (self.file_name + ".generated.h")
        with open(self.out_header, "w+t") as f:
            f.write(self._pre_gen_macro())

    def _pre_gen_macro(self):
        """
        pre gen all macros for clang to analyze
        :return:
        """
        macros: dict = self.templates.templates
        result = "#define CH_GENERATED(...)\n"
        for name, _ in macros.items():
            result += f"#define {name}(...)\n"
        return result

    def _traverse(self, node: cl.Cursor, depth):
        src_file: str = node.location.file
        if src_file is not None and not src_file.name.endswith(f"{self.file_name}.h"):
            return
        try:
            kind = node.kind
        except ValueError as e:
            kind = f"unknown value {node._kind_id}"
        print(f"{'|    ' * depth}{kind},{node.spelling}")
        for n in node.get_children():
            self._traverse(n, depth + 1)

    def _analyze_all_macro(self):
        tu: cl.TranslationUnit = self.cpp_tu
        self._traverse(tu.cursor, 0)

        pass

    def _pre_check_includes(self):
        """
        xxx.generated.h mast be included at last of the xxx.h
        """
        tu: cl.TranslationUnit = self.cpp_tu
        found = False
        for item in tu.get_includes():
            if not item.include.name.endswith(f"{self.file_name}.h"):
                continue
            header_index = cl.Index.create()
            header_tu = header_index.parse(None, [f"{item.include.name}"], options=cl.TranslationUnit.PARSE_INCOMPLETE)
            includes = [x for x in header_tu.get_includes()]
            if len(includes) <= 0:
                raise RuntimeError(f"{self.file_name}.generated.h must be included by {self.file_name}.h")
            last = includes[-1]
            if not last.include.name.endswith(f"{self.file_name}.generated.h"):
                raise RuntimeError(f"{self.file_name}.generated.h must be included at last")
            found = True
        if not found:
            raise RuntimeError(f"{self.file_name}.generated.h must be included by {self.file_name}.h")
        logger.debug(f"pass header check")

    def gen(self):
        index = cl.Index.create()
        args = self.cmd.split(" ")
        # needs processing macro info
        tu = index.parse(None, args, options=cl.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        if not tu:
            raise RuntimeError("parse cmd fail")
        self.cpp_tu = tu
        self._pre_check_includes()
        self._analyze_all_macro()
