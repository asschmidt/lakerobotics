'''
Created on 16.05.2019

@author: Andreas
'''

from model.messages import *
from model.signals import *
from model.additional_model_data import *

'''
'''
class CANMessagePreprocessor:
    '''
    '''
    def __init__(self, networkBuilder):
        self._networkBuilder = networkBuilder

    '''
    '''
    def _calculateMessageIDs(self):
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodes():
            if node != None:
                actualMsgNumber = 1

                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        txMessage.Message.GeneratorData[MessageGeneratorData.CAN_ID] = interface.NetworkID + actualMsgNumber
                        txMessage.Message.GeneratorData[MessageGeneratorData.CAN_ID_HEX] = hex(txMessage.Message.GeneratorData[MessageGeneratorData.CAN_ID])
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
                        txMessage.Message.GeneratorData['DLC'] = int(msgDLC / 8)

    '''
    '''
    def _findCorrespondingTxMessage(self, rxMessage):
        foundTxMessage = None

        # Iterate over all Nodes
        for node in self._networkBuilder.getNodes():
            if node != None:
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        if txMessage.Message.ID == rxMessage.Message.ID:
                            foundTxMessage = txMessage
                            break

        return foundTxMessage

    '''
    '''
    def _updateRxMessageGeneratorData(self):
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodes():
            if node != None:
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Rx Messages of a Interface
                    for rxMessage in interface.RxMessages.values():
                        # Find txMessage in Network tree
                        txMessage = self._findCorrespondingTxMessage(rxMessage)
                        if txMessage != None:
                            rxMessage.Message.GeneratorData = txMessage.Message.GeneratorData
                        else:
                            print("Rx Message " + rxMessage.Message.ID + " not found in Tx list of any node")
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
            for interface in node.Interfaces.values():
                print("Node: " + node.ID + "\t\tNetwork-ID: " + hex(interface.NetworkID) + "(" + str(interface.NetworkID) + ")")

        print("")

    '''
    '''
    def _printTxMessageList(self, txMessageList):
        print("TX Messages")
        print("==================================")
        for msg in txMessageList.values():
            print("TX Message: " + msg.Message.ID + "\t\tfrom Node " + msg.Node.ID + "\tCAN-ID: " + hex(msg.Message.GeneratorData[MessageGeneratorData.CAN_ID]))

        print("")

    '''
    '''
    def prepareCANMessageDatabase(self):
        # Calculate the Node IDs
        self._calculateMessageIDs()
        self._calculateMessageDLCs()
        self._updateRxMessageGeneratorData()

        self._printNodeIDs()

        txMessageList = self._buildTxMessageList()
        self._printTxMessageList(txMessageList)