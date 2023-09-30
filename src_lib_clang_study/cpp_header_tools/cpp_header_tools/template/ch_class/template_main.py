import clang.cindex as cl

from cpp_header_tools.generate_session import GeneratedItem

macro_names = ["CH_CLASS"]
interest_kinds = [cl.CursorKind.CLASS_DECL]


def generate_main(analyzer, session, self_infos):
    session.get_generated_header().append(GeneratedItem("CH_CLASS", "#define CH_CLASS(...) "))
    pass
