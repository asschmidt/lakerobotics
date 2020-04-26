'''
Classes for CAN thread handling

@author: Andreas
'''

import threading
import time
import queue

from pyusbtin.usbtin import CANMessage, USBtin

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
        self._wantAbort = False

        self._canConnector = canConnector
        self._canConnector.setCANInterfaceThread(self)

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
        Main Loop of the CAN thread.

        The main loop of the CAN thread handles the CAN-TX and CAN-RX message in the same loop. At first
        it checks for TX messages and if there are TX messages in the queue, it sends the first one. After that
        the threads checks for RX messages and reads the first one
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
