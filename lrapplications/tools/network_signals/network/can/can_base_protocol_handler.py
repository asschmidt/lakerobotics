
class CANBaseProtocolHandler:
    '''
    Base class for all protocol handlers for CAN messages
    '''

    def __init__(self, networkBuilder, canConnector):
        '''
        Initializes the CAN Base Protocol Handler object
        '''
        self._networkBuilder = networkBuilder
        self._canConnector = canConnector


    def shouldHandleCANMessage(self, canConnector, canMessage):
        '''
        Returns True if the protocol handler object is responsible for
        handling the CAN message
        '''
        raise NotImplementedError

    def handleCANMessage(self, canConnector, canMessage):
        '''
        Interface function for handling a CAN message inside a protocol handlers
        '''
        raise NotImplementedError
