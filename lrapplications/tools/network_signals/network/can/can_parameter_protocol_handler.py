from util.logger import LoggerEntryType
from util.logger_global import defaultLog

from network.can.can_base_protocol_handler import CANBaseProtocolHandler

# CAN ID for the Parameter Request/Response Frame
PARAMETER_REQUEST_CAN_ID  = 0x010
PARAMETER_RESPONSE_CAN_ID = 0x011

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

    def shouldHandleCANMessage(self, canConnector, canMessage):
        '''
        Returns True if the protocol handler object is responsible for
        handling the CAN message
        '''
        if canMessage.mid == PARAMETER_RESPONSE_CAN_ID:
            defaultLog("Received Parameter Response CAN-ID")
            pass
        else:
            return False

    def handleCANMessage(self, canConnector, canMessage):
        '''
        Interface function for handling a CAN message inside a protocol handlers
        '''
        pass