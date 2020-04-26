from codegen.base_generator import BaseCodeGenerator, CodeTemplateStruct

class ParameterGenerator(BaseCodeGenerator):
    '''
    Class to generate code for the Parameter structures for different controllers
    Currently the controllers MCP2515 and the STMF103 are supported.
    '''
    def __init__(self, networkBuilder, jinjaEnv):
        super().__init__(networkBuilder)

        self._jinjaEnv = jinjaEnv

        self._templates = {}
        self._templates['Default'] = CodeTemplateStruct('Default', self._jinjaEnv.get_template('node_param_code_arduino.j2'), self._jinjaEnv.get_template('node_param_header_arduino.j2'))
        self._templates['Arduino'] = CodeTemplateStruct('Arduino', self._jinjaEnv.get_template('node_param_code_arduino.j2'), self._jinjaEnv.get_template('node_param_header_arduino.j2'))
        self._templates['STM32F103'] = CodeTemplateStruct('STM32F103', self._jinjaEnv.get_template('node_param_code_stm32.j2'), self._jinjaEnv.get_template('node_param_header_stm32.j2'))

    def generateCode(self):
        '''
        Generates the code based on the internal data model provided via the networkBuilder instance. The
        generated code is directly saved in source and header files.
        '''
        for node in self._networkBuilder.getNodeList():
            templateCtx = {}
            templateCtx['nodeName'] = node.ID

            templateCtx['nodeHeaderName'] = "_" + node.ID.upper() + "_Param_" + node.NodeController + "_H_"
            templateCtx['nodeController'] = node.NodeController

            outputHeaderFile = open("_output/" + node.ID + "_Param_" + node.NodeController + ".h", "w")
            outputCodeFile = open("_output/" + node.ID + "_Param_" + node.NodeController + ".cpp", "w")

            try:
                headerTemplate = self._templates[node.NodeController].HeaderTemplate
                codeTemplate = self._templates[node.NodeController].CodeTemplate
            except:
                headerTemplate = self._templates['Default'].HeaderTemplate
                codeTemplate = self._templates['Default'].CodeTemplate

            templateCtx['networkVersion'] = self._networkBuilder.getNetworkVersion()
            templateCtx['parameters'] = node.Parameters.values()

            templateContent = headerTemplate.render(templateCtx)
            outputHeaderFile.write(templateContent)

            templateContent = codeTemplate.render(templateCtx)
            outputCodeFile.write(templateContent)

            outputHeaderFile.close()
            outputCodeFile.close()