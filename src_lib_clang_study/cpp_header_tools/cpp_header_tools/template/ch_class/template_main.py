import jinja2
import clang.cindex as cl

macro_name = "CH_CLASS"
interest_kinds = [cl.CursorKind.CLASS_DECL]
