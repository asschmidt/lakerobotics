
class CANInterface:
    '''
    Interface definition for a CANInterface object which can send and
    receive CAN Frames
    '''

    def __init__(self, interfaceName):
        '''
        Initializes the basic configuration information which is needed for every CAN Interface
        like interface name, hw interface and the baud rate
        '''
        self._interfaceName = interfaceName
        # Default values for COM interface and baudrate
        self._comInterface = "COM4"
        self._baudrate = 500000

    def setInterfaceParameter(self, comInterface, baudrate):
        '''
        Sets the interface parameter for HW inteface and baudrate
        '''
        self._comInterface = comInterface
        self._baudrate = baudrate

    def getInterfaceName(self):
        '''
        Returns the name of the interface
        '''
        return self._interfaceName

    def getInterfaceObject(self):
        '''
        Returns the reaö interface object which is wrapped by this interface
        '''
        raise NotImplementedError

    def initializeInterface(self):
        '''
        Initializes the Interface with the internal parameters for HW interface
        and used baudrate
        '''
        raise NotImplementedError

    def finalizeInterface(self):
        '''
        Closes the interfaces and performs necessary clean-ups
        '''
        raise NotImplementedError

    def getNextFrame(self):
        '''
        Returns the next received CAN frame from the HW inteface (if there is one)
        '''
        raise NotImplementedError

    def hasNextFrame(self):
        '''
        Returns true if the HW interface has a CAN frame in the receive buffer which
        can be read out with the getNextFrame() function
        '''
        raise NotImplementedError

    def sendFrame(self, frame):
        '''
        Sends a CAN frame via the internal HW interface
        '''
        raise NotImplementedError

    def isOpen(self):
        '''
        Returns true if the HW inteface is opened
        '''
        raise NotImplementedError