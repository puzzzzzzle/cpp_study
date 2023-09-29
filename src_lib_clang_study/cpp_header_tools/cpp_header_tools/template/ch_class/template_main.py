import jinja2
import clang.cindex as cl

macro_names = ["CH_CLASS"]
interest_kinds = [cl.CursorKind.CLASS_DECL]


def generate_main(analyzer, session):
    pass
