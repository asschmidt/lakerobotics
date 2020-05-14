from codegen.base_generator import BaseCodeGenerator, CodeTemplateStruct

class CANMessageGenerator(BaseCodeGenerator):
    '''
    Class to generate code for the CAN message creation and parsing for different controllers
    Currently the controllers MCP2515 and the STMF103 are supported.
    '''
    def __init__(self, networkBuilder, jinjaEnv):
        super().__init__(networkBuilder)

        self._jinjaEnv = jinjaEnv

        self._templates = {}
        self._templates['Default'] = CodeTemplateStruct('Default', self._jinjaEnv.get_template('node_can_code_mcp2515.j2'), self._jinjaEnv.get_template('node_can_header_mcp2515.j2'))
        self._templates['MCP2515'] = CodeTemplateStruct('MCP2515', self._jinjaEnv.get_template('node_can_code_mcp2515.j2'), self._jinjaEnv.get_template('node_can_header_mcp2515.j2'))
        self._templates['STM32F103'] = CodeTemplateStruct('STM32F103', self._jinjaEnv.get_template('node_can_code_stm32.j2'), self._jinjaEnv.get_template('node_can_header_stm32.j2'))

    def generateCode(self):
        '''
        Generates the code based on the internal data model provided via the networkBuilder instance. The
        generated code is directly saved in source and header files.
        '''
        for node in self._networkBuilder.getNodeList():
            # Iterate over all Interfaces of a node
            for interface in node.Interfaces.values():
                templateCtx = {}
                templateCtx['nodeName'] = node.ID
                templateCtx['nodeNetworkID'] = hex(interface.NetworkID)

                templateCtx['interfaceHeaderName'] = "_" + node.ID.upper() + "_CAN_" + interface.NetworkController + "_H_"
                templateCtx['interfaceName'] = interface.ID
                templateCtx['interfaceController'] = interface.NetworkController

                outputHeaderFile = open("codegen/output/" + node.ID + "_CAN_" + interface.NetworkController + ".h", "w")
                outputCodeFile = open("codegen/output/" + node.ID + "_CAN_" + interface.NetworkController + ".cpp", "w")

                try:
                    headerTemplate = self._templates[interface.NetworkController].HeaderTemplate
                    codeTemplate = self._templates[interface.NetworkController].CodeTemplate
                except:
                    headerTemplate = self._templates['Default'].HeaderTemplate
                    codeTemplate = self._templates['Default'].CodeTemplate

                templateCtx['networkVersion'] = self._networkBuilder.getNetworkVersion()
                templateCtx['txMessages'] = interface.TxMessages.values()
                templateCtx['rxMessages'] = interface.RxMessages.values()

                templateContent = headerTemplate.render(templateCtx)
                outputHeaderFile.write(templateContent)

                templateContent = codeTemplate.render(templateCtx)
                outputCodeFile.write(templateContent)

            outputHeaderFile.close()
            outputCodeFile.close()