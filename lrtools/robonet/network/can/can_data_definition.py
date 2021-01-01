
class CANDataDefinition:
    '''
    Class which represents a combination of a CAN Message and the signal in that message
    The class is used to have a mapping of a signal to a CAN Message
    '''

    def __init__(self, message, signalInMessage):
        '''
        Initializes the CAN Data Definition object with the provided CAN-Message object
        and the Signal object
        '''
        self._message = message
        self._signal = signalInMessage

    def getMessage(self):
        '''
        Returns the internal CAN Message object
        '''
        return self._message

    def getSignal(self):
        '''
        Return the Signal object which is assigned to the CAN Data Definition
        '''
        # We need to return the "Signal" member, because the _signal is a MessageSignalRef object
        return self._signal.Signal

