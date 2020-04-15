
class CodeTemplateStruct:
    '''
    Structure for a code template including the template filename for code and header file
    and also the type of microcontroller for which the code should be generated
    '''
    def __init__(self, ctrlName, codeTpl, headerTpl):
        '''
        Initializes the struct with the provided controller name, code template file and header template file
        '''
        self.ControllerName = ctrlName
        self.CodeTemplate = codeTpl
        self.HeaderTemplate = headerTpl

class BaseCodeGenerator:
    '''
    Base class for a Code Generator. This generator includes methods to generate
    C-Structures and access function out of messages
    '''

    def __init__(self, networkBuilder):
        '''
        Initializes the Code generator class with the provided networkBuilder instance
        '''
        self._networkBuilder = networkBuilder

    def generateCode(self, nodeBlockSize):
        '''
        Generates code typically based on jinja2 templates
        '''
        raise NotImplementedError
