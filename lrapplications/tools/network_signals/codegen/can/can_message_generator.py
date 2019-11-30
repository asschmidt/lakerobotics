'''
Created on 16.05.2019

@author: Andreas
'''

from model.messages import *
from model.signals import *

from codegen.base_generator import *

'''
'''
class CANTemplateStruct:
    '''
    '''
    def __init__(self, ctrlName, codeTpl, headerTpl):
        self.ControllerName = ctrlName
        self.CodeTemplate = codeTpl
        self.HeaderTemplate = headerTpl

'''
'''
class CANMessageGenerator(BaseMessageGenerator):
    '''
    '''
    def __init__(self, networkBuilder, jinjaEnv):
        super().__init__(networkBuilder)
                
        self._jinjaEnv = jinjaEnv
        
        self._templates = {}
        self._templates['Default'] = CANTemplateStruct('Default', self._jinjaEnv.get_template('node_code_mcp2515.j2'), self._jinjaEnv.get_template('node_header_mcp2515.j2'))
        self._templates['MCP2515'] = CANTemplateStruct('MCP2515', self._jinjaEnv.get_template('node_code_mcp2515.j2'), self._jinjaEnv.get_template('node_header_mcp2515.j2'))
        self._templates['STM32F103'] = CANTemplateStruct('STM32F103', self._jinjaEnv.get_template('node_code_stm32.j2'), self._jinjaEnv.get_template('node_header_stm32.j2'))

        #self._nodeCodeTemplate = self._jinjaEnv.get_template('node_code.j2')
        #self._nodeHeaderTemplate = self._jinjaEnv.get_template('node_header.j2')        
            
            
    '''
    '''
    def generateCANMessageCode(self):        
        for node in self._networkBuilder.getNodes():
            # Iterate over all Interfaces of a node
            for interface in node.Interfaces.values():
                templateCtx = {}                
                templateCtx['nodeName'] = node.ID
            
                templateCtx['interfaceHeaderName'] = "_" + node.ID.upper() + "_CAN_" + interface.NetworkController + "_H_"                
                templateCtx['interfaceName'] = interface.ID
                templateCtx['interfaceController'] = interface.NetworkController
            
                outputHeaderFile = open("output\\" + node.ID + "_CAN_" + interface.NetworkController + ".h", "w")
                outputCodeFile = open("output\\" + node.ID + "_CAN_" + interface.NetworkController + ".cpp", "w")

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