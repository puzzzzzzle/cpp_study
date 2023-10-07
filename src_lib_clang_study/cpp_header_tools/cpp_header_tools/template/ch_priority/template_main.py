import sys
from importlib import resources

import clang.cindex as cl
import logging
import jinja2

from cpp_header_tools.generate_session import GenerateSession, GeneratedItem
from cpp_header_tools.utils.generate_tools import merge_all_decorated, get_class_namespace
from cpp_header_tools.utils.exceptions import GeneratedException

logger = logging.getLogger(__name__)

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
generated_template = jinja2.Template(
R"""{% if gen_getter -%}
public: const {{ filed_type }}& get_{{ field_alias }}();
{% endif -%}
{% if gen_setter -%}
public: void set_{{ field_alias }} ( const {{ filed_type}}& {{ field_alias}}_val);
{% endif -%}""")

cpp_template = jinja2.Template(
R"""{% if gen_getter -%}
// getter for {{ field_name }}
const {{ filed_type }}& {{ namespace }}::{{ class_name }}::get_{{ field_alias }}()
{
return this->{{ field_name }};
}
{% endif -%}
{% if gen_setter -%}
// setter for {{ field_name }}
void {{ namespace }}::{{ class_name }}::set_{{ field_alias }}( const {{ filed_type }}& {{ field_alias }}_val)
{
this->{{ field_name }} = {{ field_alias }}_val;
}
{% endif -%}""")


def collect_info(target: cl.Cursor, decorated: cl.Cursor, metas: list):
    assert target.kind == cl.CursorKind.FIELD_DECL
    result = {}

    result["gen_getter"] = not ("NO_GETTER" in metas)
    result["gen_setter"] = not ("NO_SETTER" in metas)
    result["filed_type"] = target.type.spelling

    parent: cl.Cursor = target.semantic_parent
    assert parent.kind == cl.CursorKind.CLASS_DECL

    result["namespace"] = get_class_namespace(parent)
    result["class_name"] = parent.spelling
    result["field_name"] = target.spelling

    alias = result["field_name"]
    if "ALIAS" in metas:
        alias_meta = metas["ALIAS"]
        if len(alias_meta) != 1:
            raise GeneratedException(f"ALIAS only can add once {target.location}")
        alias = alias_meta[0]
        assert alias[0] == "\""
        assert alias[-1] == "\""
        alias = alias[1:-1]
        pass
    result["field_alias"] = alias

    return result


def generate_main(analyzer, session: GenerateSession, self_infos):
    session.get_generated_header().append(GeneratedItem("CH_PROPERTY", "#define CH_PROPERTY(...) "))
    inner_decorated = analyzer.relations["inner_decorated"]
    session.get_generated_header()
    for decorated in inner_decorated:
        target: cl.Cursor = decorated["target"]
        num, metas = merge_all_decorated(decorated, "CH_PROPERTY")
        if num == 0:
            continue
        infos = collect_info(target, decorated, metas)
        generated_inner = generated_template.render(**infos)
        generated_cpp = cpp_template.render(**infos)
        session.get_generated_inner_class().append(GeneratedItem("CH_PROPERTY", generated_inner))
        session.get_generated_cpp().append(GeneratedItem("CH_PROPERTY", generated_cpp))
        pass
