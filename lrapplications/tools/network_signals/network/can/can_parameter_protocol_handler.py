
from network.can.can_base_protocol_handler import CANBaseProtocolHandler

class CANParameterProtocolHandler(CANBaseProtocolHandler):
    '''
    Implementation of a Parameter Protocol Handler for CAN
    '''

    def __init__(self, networkBuilder, canConnector):
        '''
        Initializes the CAN Parameter Protocol Handler object
        '''
        super().__init__(networkBuilder, canConnector)

    def shouldHandleCANMessage(self, canConnector, canMessage):
        '''
        Returns True if the protocol handler object is responsible for
        handling the CAN message
        '''
        return False

    def handleCANMessage(self, canConnector, canMessage):
        '''
        Interface function for handling a CAN message inside a protocol handlers
        '''
        pass