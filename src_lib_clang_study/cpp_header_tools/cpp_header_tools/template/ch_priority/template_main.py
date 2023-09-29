import jinja2
import clang.cindex as cl
from cpp_header_tools.utils.exceptions import GeneratedException

macro_names = ["CH_PROPERTY"]
docs = {"CH_PROPERTY": "mark one filed as property"}

interest_kinds = [cl.CursorKind.FIELD_DECL]

# docs for meta info
meta_infos = {
    "NO_GETTER": {"targets": ["CH_PROPERTY"], "desc": "prevent generating getter"},
    "NO_SETTER": {"targets": ["CH_PROPERTY"], "desc": "prevent generating setter"},
    "NO_REFLECTION": {"targets": ["CH_PROPERTY"], "desc": "prevent generating refaction"},
    "ALIAS": {"targets": ["CH_PROPERTY"],
              "desc": "When serialized (jsons,tream...) ,  default name is field's name. "
                      "Use this tag can  change name to the specified name, "
                      "eg: ALIAS = 'pageNum'"},
}



def merge_all_decorated(decorated, name):
    ret = []
    for item in decorated["decorated"]:
        pass
    return 0, ret


def generate_main(analyzer, session):
    inner_decorated = analyzer.relations["inner_decorated"]
    for decorated in inner_decorated:
        target: cl.Cursor = decorated["target"]
        num, metas = merge_all_decorated(decorated, "CH_PROPERTY")

        pass
