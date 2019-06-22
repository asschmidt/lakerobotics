'''
Created on 16.05.2019

@author: Andreas
'''

from messages import *
from signals import *

from base_generator import *


'''
'''
class CANMessageGenerator(BaseMessageGenerator):
    '''
    '''
    def __init__(self, networkBuilder, jinjaEnv):
        super().__init__(networkBuilder)
                
        self._jinjaEnv = jinjaEnv
        self._nodeHeaderTemplate = self._jinjaEnv.get_template('node_header.template')
        self._nodeCodeTemplate = self._jinjaEnv.get_template('node_code.template')
        
        self._templateCtx = {}
        
    '''
    '''
    def _calculateNodeIDs(self, nodeBlockSize):
        # Save the Start ID as actual Node ID
        actualNodeNumber = 1
        actualNodeID = (actualNodeNumber * nodeBlockSize)      
        
        # Generate Node IDs
        for node in self._networkBuilder.getNodes():
            if node != None:
                # Store the actual Node ID in the generator data of the node
                node.GeneratorData[NodeGeneratorData.NODE_ID] = actualNodeID
                                            
                # Increment the actual node ID
                actualNodeNumber = actualNodeNumber + 1
                actualNodeID = (actualNodeNumber * nodeBlockSize)
    
    '''
    '''
    def _calculateMessageIDs(self, nodeBlockSize):            
        # Iterate over all Nodes 
        for node in self._networkBuilder.getNodes():
            if node != None:
                actualMsgNumber = 1
                
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():                        
                        txMessage.GeneratorData[MessageGeneratorData.CAN_ID] = txMessage.Node.GeneratorData[NodeGeneratorData.NODE_ID] + actualMsgNumber
                        txMessage.GeneratorData['CAN_ID_HEX'] = hex(txMessage.GeneratorData[MessageGeneratorData.CAN_ID])
                        actualMsgNumber = actualMsgNumber + 1
    
    def _calculateMessageDLCs(self):            
        # Iterate over all Nodes 
        for node in self._networkBuilder.getNodes():
            if node != None:                               
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        msgDLC = 0  
                        # Iterate over all Signals inside the Tx Message
                        for sig in txMessage.Message.Signals:
                            # Sum the amount of bits of each signal for the DLC
                            if sig.Signal.Size == 1:
                                msgDLC = msgDLC + 8
                            else:
                                msgDLC = msgDLC + sig.Signal.Size
                        
                        # Calculate DLC in number of bytes
                        txMessage.GeneratorData['DLC'] = int(msgDLC / 8)
    
    '''
    '''
    def _buildTxMessageList(self):
        txMessageList = {}
       
        # Iterate over all Nodes 
        for node in self._networkBuilder.getNodes():
            if node != None:
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        try:
                            # Add it to the dictionary
                            txMessageList[txMessage.Message.ID] = txMessage
                        except:
                            print("Multiple nodes sending message " + txMessage.Message.ID)
    
        return txMessageList
    
    '''
    '''
    def _printNodeIDs(self):
        print("Node-IDs")
        print("==================================")
        for node in self._networkBuilder.getNodes():
            print("Node: " + node.ID + "\t\tCAN-Node-ID: " + hex(node.GeneratorData[NodeGeneratorData.NODE_ID]) + "(" + str(node.GeneratorData[NodeGeneratorData.NODE_ID]) + ")")
        
        print("")
        
    '''
    '''
    def _printTxMessageList(self, txMessageList):
        print("TX Messages")
        print("==================================")
        for msg in txMessageList.values():
            print("TX Message: " + msg.Message.ID + "\t\tfrom Node " + msg.Node.ID + "\tCAN-ID: " + hex(msg.GeneratorData[MessageGeneratorData.CAN_ID]))
            
        print("")
    
    '''
    '''
    def _generateMessageIDDefine(self, txMessage):
        messageID = txMessage.Message.ID
        canID = hex(txMessage.GeneratorData[MessageGeneratorData.CAN_ID])
        
        defineStr = "#define " + messageID + "\t\t\t" + canID + "\n"
        
        return defineStr
    '''
    '''
    def generateCANMessageCode(self, nodeBlockSize):
        # Calculate the Node IDs
        self._calculateNodeIDs(nodeBlockSize)
        self._calculateMessageIDs(nodeBlockSize)    
        self._calculateMessageDLCs()
            
        self._printNodeIDs()
        
        txMessageList = self._buildTxMessageList()
        self._printTxMessageList(txMessageList)
        
        for node in self._networkBuilder.getNodes():
            self._templateCtx['nodeName'] = node.ID
            self._templateCtx['nodeHeaderName'] = "_" + node.ID.upper() + "_CAN_H_"
            
            outputHeaderFile = open("gen\\" + node.ID + "_CAN.h", "w")
            outputCodeFile = open("gen\\" + node.ID + "_CAN.c", "w")
            
            # Iterate over all Interfaces of a node
            for interface in node.Interfaces.values():
                self._templateCtx['txMessages'] = interface.TxMessages.values()
                self._templateCtx['rxMessages'] = interface.RxMessages.values()

                templateContent = self._nodeHeaderTemplate.render(self._templateCtx)
                outputHeaderFile.write(templateContent)
                
                templateContent = self._nodeCodeTemplate.render(self._templateCtx)
                outputCodeFile.write(templateContent)
                
            outputHeaderFile.close()
            outputCodeFile.close()