
class CANBaseConnector:
    '''
    Base class for providing an interface of a CAN connector class with
    a callback when receiving messages and a function to transmit messages
    '''

    def __init__(self):
        '''
        Initializes the CAN Base connector object
        '''
        self._canInterfaceThread = None

    def setCANInterfaceThread(self, threadObj):
        '''
        Sets the interface thread object used to access the RX and TX queues
        '''
        self._canInterfaceThread = threadObj

    def transmitCANMessage(self, canMessage):
        '''
        Transmits a CAN message
        '''
        raise NotImplementedError

    def updateWithCANMessage(self, canMessage):
        '''
        Callback function which is called if a CAN message has been received
        '''
        raise NotImplementedError