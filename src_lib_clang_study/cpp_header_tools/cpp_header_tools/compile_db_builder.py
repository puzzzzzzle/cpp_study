import logging
from pathlib import Path

import clang.cindex as cl
from cpp_header_tools.header_analyze import HeaderAnalyze
from cpp_header_tools.templates_mng import TemplatesMng

logger = logging.getLogger(__name__)


class CompileDBBuilder:
    def __init__(self, cmd_db_path: str, outer_templates=None):
        db: cl.CompilationDatabase = cl.CompilationDatabase.fromDirectory(cmd_db_path)
        self.db = db
        self.templates = TemplatesMng(outer_templates)
        pass

    def build(self, header_path: str, outer_header_path: str):
        assert Path(header_path).exists() and Path(header_path).is_file()
        commands = self.db.getCompileCommands(header_path)
        file_args = []
        for command in commands:
            for arg in command.arguments:
                file_args.append(arg)
        logger.debug(f"build cmd : {file_args}")
        analyze = HeaderAnalyze(header_path, file_args, self.templates, outer_header_path)
        analyze.build()
        pass

    pass
