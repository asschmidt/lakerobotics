'''
Classes for CAN thread handling

@author: Andreas
'''

import threading
import time
import queue

from pyusbtin.usbtin import CANMessage, USBtin

from model.can.can_interface import *
from model.can.can_usbtin_interface import *

class CANSimulationThread(threading.Thread):
    def __init__(self, canConnector):
        threading.Thread.__init__(self)
        self._canConnector = canConnector

    def run(self):
        counter = 0
        while counter < 10:
            msg = CANMessage(0x201, [counter, 0, counter, 0])
            self._canConnector.updateWithCANMessage(msg)
            counter = counter + 1
            time.sleep(1)


class CANInterfaceThread(threading.Thread):
    '''
    Thread to handle CAN frame transmission and receiption via a provided CAN Interface object.

    The thread assumes that the RX queue handling is done in the CAN Interface but the TX queue
    handling is performed inside this thread.
    '''

    def __init__(self, canInterface, canConnector):
        '''
        Initializes the CAN thread

        Assigns the internal object for CAN interface and CAN connector and creates also the
        needed internal queues for the TX handling
        '''
        threading.Thread.__init__(self)
        self._canInterface = canInterface
        self._canConnector = canConnector
        self._wantAbort = False

        self._canTxQueue = queue.Queue()

    def stop(self):
        '''
        Sets the internal flag for the thread to stop

        This doesn't stop the thread immediately - it just signals the thread it should stop. But the
        the thread needs to handle this flag in the run() method
        '''
        self._wantAbort = True

    def transmitFrame(self, msg):
        '''
        Puts the CAN message frame into the internal tranmission queue
        '''
        self._canTxQueue.put(msg)

    def run(self):
        '''
        '''
        self._canInterface.initializeInterface()

        while self._wantAbort != True:
            try:
                # Check if the TX queue is empty
                if self._canTxQueue.empty() == False:
                    # If there is a frame to transmit, get it out of the queue
                    canTxMsg = self._canTxQueue.get(timeout=0.01)
                    # Send it via the CAN Interface object
                    self._canInterface.sendFrame(canTxMsg)
            except queue.Empty:
                pass

            try:
                # Try to get the next frame from the CAN interface
                canMsg = self._canInterface.getNextFrame()
                if canMsg != None:
                    # If there was a frame, provide it to the CAN connector for further processing
                    self._canConnector.updateWithCANMessage(canMsg)
            except queue.Empty:
                pass

        self._canInterface.finalizeInterface()
