import logging
from cpp_header_tools.templates_mng import TemplatesMng
from cpp_header_tools.cpp_generator import Generator

logger = logging.getLogger(__name__)


def generated_one(cmake_cmd, src,out_dir, outer_templates=None):
    templates = TemplatesMng(outer_templates)
    analyze = Generator(cmake_cmd, src, templates, out_dir)
    files = analyze.gen()

    pass
