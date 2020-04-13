'''
Classes for CAN hardware interface of type USBtin

@author: Andreas
'''

import queue

from pyusbtin.usbtin import CANMessage, USBtin

from util.logger import LoggerEntryType
from util.logger_global import *
from network.can.can_interface import *

'''
'''
class CANUSBtinInterface(CANInterface):
    '''
    CAN Interface which wrapps the USBtin interface
    '''

    def __init__(self):
        '''
        Initializes the USBtin Interface object
        '''
        super().__init__("USBtin")

        self._usbtin = USBtin()
        self._usbtin.add_message_listener(self._receiveFrame)

        self._canRxQueue = queue.Queue()

    def _receiveFrame(self, msg):
        '''
        Called by the USBtin internal message listener thread if a new CAN frame has
        been received. The received CAN message is added to the internal RX queue
        '''
        defaultLog(str(msg), LoggerEntryType.LOG_ACTIVITY)
        self._canRxQueue.put(msg)

    def getInterfaceObject(self):
        '''
        Returns the internal USBtin object
        '''
        return self._usbtin

    def initializeInterface(self):
        '''
        Initializes the USBtin interface with the configured COM interface and the 
        baudrate
        '''
        self._usbtin.connect(self._comInterface)
        self._usbtin.open_can_channel(self._baudrate, USBtin.ACTIVE)

    def finalizeInterface(self):
        '''
        Closes the CAN Channel and disconnects the USBtin interface from the COM port
        '''
        if self._usbtin != None:
            self._usbtin.close_can_channel()
            self._usbtin.disconnect()

    def getNextFrame(self):
        '''
        Returns the next CAN frame from the internal RX queue. If there is no CAN frame
        available, there is a timeout of 10ms and after that, None is returned
        '''
        return self._canRxQueue.get(timeout=0.01)

    def hasNextFrame(self):
        '''
        Returns true if the internal RX queue is not empty
        '''
        return not self._canRxQueue.empty()

    def sendFrame(self, frame):
        '''
        Sends the provided CAN frame via the USBtin interface
        '''
        self._usbtin.send(frame)

    def isOpen(self):
        '''
        Returns true if the USBtin interface is connected
        '''
        return self._usbtin.is_connected()