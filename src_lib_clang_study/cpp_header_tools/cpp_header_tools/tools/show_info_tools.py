from pathlib import Path

import clang.cindex as cl


def get_cursor_id(cursor, cursor_list=[]):
    if cursor is None:
        return None

    # FIXME: This is really slow. It would be nice if the index API exposed
    # something that let us hash cursors.
    for i, c in enumerate(cursor_list):
        if cursor == c:
            return i
    cursor_list.append(cursor)
    return len(cursor_list) - 1


def get_node_info(node):
    return {
        "id": get_cursor_id(node),
        "kind": node.kind,
        "usr": node.get_usr(),
        "spelling": node.spelling,
        "location": node.location,
        "extent.start": node.extent.start,
        "extent.end": node.extent.end,
        "is_definition": node.is_definition(),
        "definition id": get_cursor_id(node.get_definition()),
    }


def get_all_info(node):
    children = [get_all_info(c) for c in node.get_children()]
    return {
        "id": get_cursor_id(node),
        "kind": node.kind,
        "usr": node.get_usr(),
        "spelling": node.spelling,
        "location": node.location,
        "extent.start": node.extent.start,
        "extent.end": node.extent.end,
        "is_definition": node.is_definition(),
        "definition id": get_cursor_id(node.get_definition()),
        "children": children,
    }


def traverse(node: cl.Cursor, depth, file=None):
    if file is not None:
        src_file: cl.File = node.location.file
        if src_file is None or Path(src_file.name).resolve() == Path(file).resolve():
            pass
        else:
            return
    try:
        kind = node.kind
    except ValueError as e:
        kind = f"unknown kind {node._kind_id}"
    print(f"{'|    ' * depth}{kind},{node.spelling}")
    for n in node.get_children():
        traverse(n, depth + 1, file)


def get_diag_info(diag):
    return {
        "severity": diag.severity,
        "location": diag.location,
        "spelling": diag.spelling,
        "ranges": diag.ranges,
        "fixits": diag.fixits,
    }


def get_diagnostics(translation_unit, level=3):
    result = []
    for diag in translation_unit.diagnostics:
        if diag.severity >= level:
            result.append(get_diag_info(diag))
    return result
