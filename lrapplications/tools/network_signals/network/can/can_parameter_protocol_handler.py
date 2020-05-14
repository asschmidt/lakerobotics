from struct import pack, unpack

from util.logger import LoggerEntryType
from util.logger_global import defaultLog

from network.can.can_base_protocol_handler import CANBaseProtocolHandler

# CAN ID Offsets for the Parameter Request/Response Frame
# Those CAN-IDs are calculated by "NodeNetworkID + CAN-ID Offset"
# For example: Node 0x10FF + 0x01 = CAN-ID for Parameter Request 0x1100
PARAMETER_REQUEST_CAN_ID  = 0x01
PARAMETER_RESPONSE_CAN_ID = 0x02

class CANParameterProtocolHandler(CANBaseProtocolHandler):
    '''
    Implementation of a Parameter Protocol Handler for CAN
    '''

    def __init__(self, networkBuilder, canConnector, parameterModel):
        '''
        Initializes the CAN Parameter Protocol Handler object
        '''
        super().__init__(networkBuilder, canConnector)
        self._parameterModel = parameterModel

        self._nodeParameterCANIDMap = {}
        self._calculateNodeParameterCANIDs()

    def _calculateNodeParameterCANIDs(self):
        '''
        Calculates the CAN-IDs for the Parameter CAN Frames for each node
        The CAN-ID is calculated by NodeNetworkID + CAN-ID-Offset
        '''
        nodeList = self._networkBuilder.getNodeList()
        for node in nodeList:
            nodeNetworkID = node.getMainNetworkID()
            if nodeNetworkID is not None:
                parameterCANID =  nodeNetworkID + PARAMETER_RESPONSE_CAN_ID
                self._nodeParameterCANIDMap[parameterCANID] = node

    def shouldHandleCANMessage(self, canConnector, canMessage):
        '''
        Returns True if the protocol handler object is responsible for
        handling the CAN message
        '''
        if canMessage.mid in self._nodeParameterCANIDMap:
            relatedNode = self._nodeParameterCANIDMap[canMessage.mid]
            defaultLog("Received Parameter Response for Node {0}".format(relatedNode.ID))
            return True
        else:
            return False

    def handleCANMessage(self, canConnector, canMessage):
        '''
        Interface function for handling a CAN message inside a protocol handlers
        '''
        networkID = canMessage.mid - PARAMETER_RESPONSE_CAN_ID
        paramNo = self._extractParameterNumber(canMessage)
        paramVal = self._extractParameterValue(canMessage)

        self._parameterModel.setParameterActualValue(networkID, paramNo, paramVal)

    def _extractParameterNumber(self, canMessage):
        '''
        Returns the parameter number from the Parameter Request CAN Message
        '''
        dataArray = list(pack('<Q', canMessage.get_data()))

        lowByte = dataArray[0]
        highByte = dataArray[1]

        intValue = lowByte + highByte

        return intValue

    def _extractParameterValue(self, canMessage):
        '''
        '''
        dataArray = list(pack('<Q', canMessage.get_data()))

        intValue = dataArray[2] + dataArray[3] + dataArray[4] + dataArray[5]
        return intValue