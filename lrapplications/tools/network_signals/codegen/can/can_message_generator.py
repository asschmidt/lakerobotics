'''
Created on 16.05.2019

@author: Andreas
'''

from model.messages import *
from model.signals import *

from codegen.base_generator import *


'''
'''
class CANMessageGenerator(BaseMessageGenerator):
    '''
    '''
    def __init__(self, networkBuilder, jinjaEnv):
        super().__init__(networkBuilder)
                
        self._jinjaEnv = jinjaEnv
        self._nodeCodeTemplate = self._jinjaEnv.get_template('node_code.j2')
        self._nodeHeaderTemplate = self._jinjaEnv.get_template('node_header.j2')        
        
        self._templateCtx = {}
            
    '''
    '''
    def generateCANMessageCode(self):        
        for node in self._networkBuilder.getNodes():
            self._templateCtx['nodeName'] = node.ID
            self._templateCtx['nodeHeaderName'] = "_" + node.ID.upper() + "_CAN_H_"
            
            outputHeaderFile = open("output\\" + node.ID + "_CAN.h", "w")
            outputCodeFile = open("output\\" + node.ID + "_CAN.cpp", "w")
            
            # Iterate over all Interfaces of a node
            for interface in node.Interfaces.values():
                self._templateCtx['networkVersion'] = self._networkBuilder.getNetworkVersion()
                self._templateCtx['txMessages'] = interface.TxMessages.values()
                self._templateCtx['rxMessages'] = interface.RxMessages.values()

                templateContent = self._nodeHeaderTemplate.render(self._templateCtx)
                outputHeaderFile.write(templateContent)
                
                templateContent = self._nodeCodeTemplate.render(self._templateCtx)
                outputCodeFile.write(templateContent)
                
            outputHeaderFile.close()
            outputCodeFile.close()