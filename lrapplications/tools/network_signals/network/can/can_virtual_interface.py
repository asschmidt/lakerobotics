'''
Classes for CAN Virtual Interface

@author: Andreas
'''

import queue
import threading
import random
import time

from pyusbtin.usbtin import CANMessage

from util.logger import LoggerEntryType
from util.logger_global import defaultLog

from network.can.can_interface import CANInterface

class CANVirtualInterface(CANInterface):
    '''
    Represents a virtual CAN interface used for simulation purposes without a real
    CAN connections
    '''

    def __init__(self):
        '''
        Initializes the Virtual CAN Interface
        '''
        super().__init__("Virtual")

        self._stopRxThread = False
        self._rxThread = threading.Thread(target=self._rxThreadFunction)

        self._canRxQueue = queue.Queue()

    def _rxThreadFunction(self):
        '''
        Function which is executed inside the internal RX thread which simulates the receiption of
        CAN frames.
        '''
        while self._stopRxThread == False:
            canID = random.randrange(0x5FF, 0x610)
            val1 = random.randrange(0x0, 0xFF)
            val2 = random.randrange(0x0, 0xFF)
            msg = CANMessage(canID, [val1, 0, val2, 0])

            self._receiveFrame(msg)
            time.sleep(0.1)

    def _receiveFrame(self, msg):
        '''
        Adds the provided CAN frame to the internal RX qeueu
        '''
        defaultLog(str(msg), LoggerEntryType.LOG_ACTIVITY)
        self._canRxQueue.put(msg)

    def getInterfaceObject(self):
        '''
        Returns a reference to it self because there is no internal interface object
        '''
        return self

    def initializeInterface(self):
        '''
        Starts the internal RX thread
        '''
        self._rxThread.start()

    def finalizeInterface(self):
        '''
        Stops the RX thread and waits till it finishes
        '''
        self._stopRxThread = True
        self._rxThread.join()

    def getNextFrame(self):
        '''
        Returns the next CAN frame from the internal RX queue.
        '''
        return self._canRxQueue.get(timeout=0.01)

    def hasNextFrame(self):
        '''
        Returns true, if the internal RX queue has at least one CAN frame
        '''
        return not self._canRxQueue.empty()

    def sendFrame(self, frame):
        '''
        Just adds a log message with the CAN Message to the logger backend
        '''
        defaultLog("Sending virtual CAN Frame: " + str(frame), LoggerEntryType.LOG_ACTIVITY)

    def isOpen(self):
        '''
        Returns alsways true for the virtual Interface
        '''
        return True