
from model.additional_model_data import MessageGeneratorData

'''
'''
class CANMessagePreprocessor:
    '''
    Class which represents a CAN Message preprocessor object to pre-process
    CAN messages
    '''

    def __init__(self, networkBuilder):
        '''
        Initializes the CAN Message preprocessor with the provided networkBuilder object
        '''
        self._networkBuilder = networkBuilder

    def _calculateMessageIDs(self):
        '''
        Calculates the CAN Message IDs for all TX Messages based on the Node-Network-ID and
        a sequential numbering scheme
        '''
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node is not None:
                actualMsgNumber = 1

                canIDOffset = 10

                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        txMessage.Message.GeneratorData[MessageGeneratorData.CAN_ID] = interface.NetworkID + canIDOffset + actualMsgNumber
                        txMessage.Message.GeneratorData[MessageGeneratorData.CAN_ID_HEX] = hex(txMessage.Message.GeneratorData[MessageGeneratorData.CAN_ID])
                        actualMsgNumber = actualMsgNumber + 1


    def _calculateMessageDLCs(self):
        '''
        Calculates the CAN message DLCs for all TX messages based on the signals and their specific size
        '''
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node is not None:
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

    def _generateMessageCodeNames(self):
        '''
        Generates the message names used in the code generation
        '''
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node is not None:
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        if txMessage.InstanceIndepName is not None:
                            txMessage.Message.GeneratorData['CODE_NAME'] = txMessage.InstanceIndepName
                        else:
                            txMessage.Message.GeneratorData['CODE_NAME'] = txMessage.Message.ID

                        # Iterate over all Signals inside the Tx Message
                        for sig in txMessage.Message.Signals:
                            if sig.InstanceIndepName is not None:
                                sig.Signal.GeneratorData['CODE_NAME'] = sig.InstanceIndepName
                            else:
                                sig.Signal.GeneratorData['CODE_NAME'] = sig.Signal.ID

                    # Iterate over all Rx Messages of a Interface
                    for rxMessage in interface.RxMessages.values():
                        if rxMessage.InstanceIndepName is not None:
                            rxMessage.Message.GeneratorData['CODE_NAME'] = rxMessage.InstanceIndepName
                        else:
                            rxMessage.Message.GeneratorData['CODE_NAME'] = rxMessage.Message.ID

                        # Iterate over all Signals inside the Rx Message
                        for sig in rxMessage.Message.Signals:
                            if sig.InstanceIndepName is not None:
                                sig.Signal.GeneratorData['CODE_NAME'] = sig.InstanceIndepName
                            else:
                                sig.Signal.GeneratorData['CODE_NAME'] = sig.Signal.ID


    def _findCorrespondingTxMessage(self, rxMessage):
        '''
        Returns a TX message which corresponds to the RX message provided as argument. If no
        message was found, None is returned
        '''
        foundTxMessage = None

        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node is not None:
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Tx Messages of a Interface
                    for txMessage in interface.TxMessages.values():
                        if txMessage.Message.ID == rxMessage.Message.ID:
                            foundTxMessage = txMessage
                            break

        return foundTxMessage

    def _updateRxMessageGeneratorData(self):
        '''
        Assignes the GeneratorData object a al TX messages to the corresponding RX message. This is
        needed because the TX messages get a CAN-ID and a DLC but this information is also needed for
        the RX messages due to e.g. Code-Generation
        '''
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node is not None:
                # Iterate over all Interfaces of a node
                for interface in node.Interfaces.values():
                    # Iterate over all Rx Messages of a Interface
                    for rxMessage in interface.RxMessages.values():
                        # Find txMessage in Network tree
                        txMessage = self._findCorrespondingTxMessage(rxMessage)
                        if txMessage is not None:
                            rxMessage.Message.GeneratorData = txMessage.Message.GeneratorData
                        else:
                            print("Rx Message " + rxMessage.Message.ID + " not found in Tx list of any node")

    def _buildTxMessageList(self):
        '''
        Returns a list of all TX messages
        '''
        txMessageList = {}

        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node is not None:
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

    def _printNodeIDs(self):
        '''
        Helper method to print all nodes and their IDs on the console
        '''
        print("Node-IDs")
        print("==================================")
        for node in self._networkBuilder.getNodeList():
            for interface in node.Interfaces.values():
                nodeString = "Node: {0:20} Network-ID: {1} ({2})".format(node.ID, hex(interface.NetworkID), interface.NetworkID)
                print(nodeString)

        print("")

    def _printTxMessageList(self, txMessageList):
        '''
        Helper method to print all TX messages on the console. The list of TX messages is
        provided with the txMessageList argument
        '''
        print("TX Messages")
        print("==================================")
        for msg in txMessageList.values():
            msgString = "TX Message {0:35} from Node {1:20} with CAN-ID: {2:5}".format(msg.Message.ID, msg.Node.ID, hex(msg.Message.GeneratorData[MessageGeneratorData.CAN_ID]))
            print(msgString)

        print("")

    def prepareCANMessageDatabase(self):
        '''
        Calculates the CAN-IDs and CAN-DLC values for all TX messages and assignes afterwards this
        information also to all RX message objects. Additionally this methods prints all the information
        on the console
        '''
        # Calculate the Node IDs
        self._calculateMessageIDs()
        self._calculateMessageDLCs()
        self._generateMessageCodeNames()
        self._updateRxMessageGeneratorData()

        self._printNodeIDs()

        txMessageList = self._buildTxMessageList()
        self._printTxMessageList(txMessageList)