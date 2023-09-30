import logging
from pathlib import Path

import clang.cindex as cl
from cpp_header_tools.class_analyze import CppClassAnalyze, BuildArgsGetter
from cpp_header_tools.generate_dirver import GenerateDriver
from cpp_header_tools.templates_mng import TemplatesMng
from cpp_header_tools.generate_session import GenerateSession
from cpp_header_tools.utils.exceptions import GeneratedException

logger = logging.getLogger(__name__)


class CompileCommandsBuildArgsGetter(BuildArgsGetter):
    def __init__(self, db):
        self.db = db

    def get_compile_cmd(self, path, is_header: bool):
        commands = self.db.getCompileCommands(path)
        file_args = []
        for command in commands:
            for arg in command.arguments:
                file_args.append(arg)
        # do not define target language type
        if is_header:
            file_args.insert(-2, '-x')
            file_args.insert(-2, 'none')
        logger.debug(f"build cmd : {file_args}")
        return file_args


class CompileDBBuilder:
    def __init__(self, cmd_db_path: str, outer_templates=None):
        db: cl.CompilationDatabase = cl.CompilationDatabase.fromDirectory(cmd_db_path)
        self.db = db
        self.templates = TemplatesMng(outer_templates)
        self.args_getter = CompileCommandsBuildArgsGetter(self.db)
        self.generated_sessions = []
        pass

    def build_one_target(self, header_path: str, cpp_path: str, outer_header_path: str, out_cpp_path: str = None):
        assert Path(header_path).exists() and Path(header_path).is_file()
        analyzer = CppClassAnalyze(header_path, cpp_path, self.args_getter, self.templates, outer_header_path)
        analyzer.analyze()
        session = GenerateSession(analyzer, analyzer.relations, outer_header_path, out_cpp_path)
        driver = GenerateDriver(self.templates, analyzer, session)
        driver.generate()
        self.generated_sessions.append(session)
        return session

    def write_all(self):
        global_generated = {}
        item: GenerateSession
        for item in self.generated_sessions:
            item.write_all()
            for name, content in item.shared_generated_files.items():
                if name not in global_generated:
                    global_generated[name] = content
                    continue
                if global_generated[name] != content:
                    raise GeneratedException(
                        f"one global file generated multi times, but content is not the same {name} {content} {global_generated[name]}")
