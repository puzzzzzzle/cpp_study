from importlib import resources
from pathlib import Path
import logging
import importlib.util
import clang.cindex as cl

from cpp_header_tools.utils.exceptions import GeneratedException

logger = logging.getLogger(__name__)


class TemplatesMng:
    """
    mng usable generators
    """

    def __init__(self, outer_templates=None):
        self.templates = {}
        self._load_built_in()
        if outer_templates is not None:
            for item in outer_templates:
                self._load_outer(item)
        self.all_macro_names = set()
        self.all_interest_kinds = set()
        for key, value in self.templates.items():
            self.all_macro_names.add(key)
            for item in value["interest_kinds"]:
                assert not cl.CursorKind.is_invalid(item)
                assert item != cl.CursorKind.MACRO_INSTANTIATION
                self.all_interest_kinds.add(item)

    def _load_built_in(self):
        from . import template
        path = resources.files(template)
        if not path.is_dir():
            raise GeneratedException(f"target is not dir {path}")
        for sub_path in path.iterdir():
            if not sub_path.is_dir():
                continue
            main_path = sub_path / "template_main.py"
            if not main_path.exists() or not main_path.is_file():
                continue
            self._load_one(sub_path, "built_in")
        pass

    def _load_outer(self, path):
        path = Path(path)
        if not path.is_dir():
            return
        main_path = path / "template_main.py"
        if not main_path.exists() or not main_path.is_file():
            return
        self._load_one(path, "outer")

    def _load_one(self, path: Path, group):
        """
        load one generator to mem
        :param path:
        :return:
        """
        # load module
        main_path = path / "template_main.py"
        spec = importlib.util.spec_from_file_location(path.stem, main_path)
        module = importlib.util.module_from_spec(spec)
        # sys.modules[file.stem] = module
        spec.loader.exec_module(module)

        # get macro name
        curr_macro_names = getattr(module, "macro_names")
        logger.debug(f"load {curr_macro_names} from {main_path}")

        interest_kinds = getattr(module, "interest_kinds")
        assert isinstance(interest_kinds, list)

        generate_main = getattr(module, "generate_main")
        import types
        assert isinstance(generate_main, types.FunctionType)

        # save
        for macro_name in curr_macro_names:
            old = self.templates.get(macro_name, None)
            if old is not None:
                old_group = old["group"]
                if old_group == group:
                    raise GeneratedException(f"macro already defined {macro_name} {group}")
                if old_group != "built_in":
                    raise GeneratedException(f"outer macro not allow redefine {macro_name} {group}")

            self.templates[macro_name] = {"module": module, "group": group, "interest_kinds": interest_kinds,
                                          "generate_main": generate_main, "path": path}

    pass
