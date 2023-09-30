from cpp_header_tools.generate_session import GenerateSession
from cpp_header_tools.utils.exceptions import GeneratedException


class GenerateDriver:
    def __init__(self, templates, analyzer, session: GenerateSession):
        self.templates = templates
        self.analyzer = analyzer
        self.session = session
        pass

    def generate(self):
        for name, infos in self.templates.templates.items():
            generate_main = infos["generate_main"]
            generate_main(self.analyzer, self.session,infos)
        pass
