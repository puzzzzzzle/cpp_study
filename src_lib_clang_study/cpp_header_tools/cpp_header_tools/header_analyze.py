from pathlib import Path
import logging
from pprint import pprint, pformat

import clang.cindex as cl

from cpp_header_tools.tools.show_info_tools import *

logger = logging.getLogger(__name__)


class HeaderAnalyze:
    """
    generator for one header define
    one header must have only one class with generated macros
    """

    def __init__(self, header_path: str, cmd: list, templates, out_header_dir: str):
        self.header_tu = None
        self.header_path = header_path
        self.cmd = cmd
        self.templates = templates
        self.out_dir = out_header_dir
        self.file_name = Path(header_path).stem

    def build(self):
        """
        build generated code for header define
        :return:
        """
        # init out header
        self.out_header = Path(self.out_dir) / (self.file_name + ".generated.h")
        with open(self.out_header, "w+t") as f:
            f.write(self._pre_gen_macro())

        # analyze header
        index = cl.Index.create()

        cmd = self.cmd
        # do not define target language type
        cmd.insert(-2, '-x')
        cmd.insert(-2, 'none')
        header_tu = index.parse(None, cmd,
                                       options=cl.TranslationUnit.PARSE_INCOMPLETE | cl.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        self.header_tu = header_tu
        logger.info(f"\n{pformat([get_diag_info(x) for x in header_tu.diagnostics])}\n")

        # check include
        self._pre_check_includes()

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

    def _pre_check_includes(self):
        """
        xxx.generated.h mast be included at last of the xxx.h
        """
        header_tu = self.header_tu
        includes = [x for x in header_tu.get_includes()]
        self._traverse(header_tu.cursor, 0)
        if len(includes) <= 0:
            raise RuntimeError(f"{self.file_name}.generated.h must be included by {self.header_path}")
        last = includes[-1]
        if not last.include.name.endswith(f"{self.file_name}.generated.h"):
            raise RuntimeError(f"{self.file_name}.generated.h must be included at last")
        logger.debug(f"pass include check")

    def _traverse(self, node: cl.Cursor, depth):
        src_file: str = node.location.file
        # if src_file is not None and not src_file.name.endswith(f"{self.file_name}.h"):
        #     return
        try:
            kind = node.kind
            if kind == cl.CursorKind.MACRO_INSTANTIATION or kind==cl.CursorKind.MACRO_DEFINITION:
                pass
        except ValueError as e:
            kind = f"unknown kind {node._kind_id}"
        print(f"{'|    ' * depth}{kind},{node.spelling}")
        for n in node.get_children():
            self._traverse(n, depth + 1)

    def _analyze_all_macro(self):
        tu: cl.TranslationUnit = self.cpp_tu
        self._traverse(tu.cursor, 0)

        pass
