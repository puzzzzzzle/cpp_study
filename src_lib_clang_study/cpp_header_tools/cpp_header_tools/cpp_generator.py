from pathlib import Path
from pprint import pprint
import logging

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
        self.tu = None
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

    def _analyze_all_macro(self):
        tu: cl.TranslationUnit = self.tu

        pass

    def _pre_check_includes(self):
        tu: cl.TranslationUnit = self.tu
        for inc in tu.get_includes():
            logger.debug(f"{inc.source}")
        includes = tu.get_includes()
        *_, last = includes
        last_file: str = last.source.name
        if not last_file.endswith(f"{self.file_name}.generated.h"):
            raise RuntimeError(f"generated.h mast include last :{self.file_name}")
        pass

    def gen(self):
        index = cl.Index.create()
        args = self.cmd.split(" ")
        # needs processing macro info
        tu = index.parse(None, args, options=cl.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        if not tu:
            raise RuntimeError("parse cmd fail")
        self.tu = tu
        self._pre_check_includes()
        self._analyze_all_macro()
