from collections import defaultdict

import clang.cindex as cl
import jinja2

from cpp_header_tools.utils.exceptions import GeneratedException


def merge_all_decorated(decorated, name):
    count = 0
    merged_meta = defaultdict(list)
    cursor: cl.Cursor
    for cursor in decorated["decorated"]:
        if cursor.spelling != name:
            continue
        count += 1
        tokens = [x for x in cursor.get_tokens()]
        assert tokens[0].kind == cl.TokenKind.IDENTIFIER
        assert tokens[1].kind == cl.TokenKind.PUNCTUATION
        assert tokens[-1].kind == cl.TokenKind.PUNCTUATION

        code = ""
        for x in tokens[2:-1]:
            code += x.spelling
        metas = code.split(",")
        for m in metas:
            if m.strip() == "":
                continue
            kv = m.split("=")
            if len(kv) == 1:
                merged_meta[kv[0]].append("")
            elif len(kv) == 2:
                merged_meta[kv[0]].append(kv[1])
            else:
                raise GeneratedException(f"error when parse decorated info {cursor.location} {code}")
        pass
    return count, merged_meta


def get_template(name, self_infos):
    with open(self_infos["path"] / name) as f:
        s = f.read()
        t = jinja2.Template(s)
    assert t is not None
    return t


def get_class_namespace(target: cl.Cursor):
    assert target.kind == cl.CursorKind.CLASS_DECL
    namespaces = []
    curr: cl.Cursor = target.semantic_parent
    while curr.kind == cl.CursorKind.NAMESPACE:
        namespaces.append(f"{curr.spelling}")
        curr = curr.semantic_parent
    namespaces.reverse()
    return "::" + "::".join(namespaces)
