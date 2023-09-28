import jinja2
import clang.cindex as cl

macro_name = "CH_PRIORITY"
interest_kinds = [cl.CursorKind.FIELD_DECL]
