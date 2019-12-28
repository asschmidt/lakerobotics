'''
Classes for CAN hardware interfaces

@author: Andreas
'''

'''
'''
class CANInterface:
    '''
    '''
    def __init__(self, interfaceName):
        self._interfaceName = interfaceName
        # Default values for COM interface and baudrate
        self._comInterface = "COM4"
        self._baudrate = 500000

    '''
    '''
    def setInterfaceParameter(self, comInterface, baudrate):
        self._comInterface = comInterface
        self._baudrate = baudrate

    '''
    '''
    def getInterfaceName(self):
        return self._interfaceName

    '''
    '''
    def getInterfaceObject(self):
        raise NotImplementedError

    '''
    '''
    def initializeInterface(self):
        raise NotImplementedError

    '''
    '''
    def finalizeInterface(self):
        raise NotImplementedError

    '''
    '''
    def getNextFrame(self):
        raise NotImplementedError

    '''
    '''
    def hasNextFrame(self):
        raise NotImplementedError

    '''
    '''
    def sendFrame(self, frame):
        raise NotImplementedError