'''
Classes for CAN Virtual Interface

@author: Andreas
'''

import queue
import threading
import random
import time

from pyusbtin.usbtin import CANMessage

from model.can.can_interface import *

'''
'''
class CANVirtualInterface(CANInterface):
    '''
    '''
    def __init__(self):
        super().__init__("Virtual")

        self._stopRxThread = False
        self._rxThread = threading.Thread(target=self._rxThread)

        self._canRxQueue = queue.Queue()

    def _rxThread(self):
        '''
        '''
        while self._stopRxThread == False:
            canID = random.randrange(0x200, 0x210)
            val1 = random.randrange(0x0, 0xFF)
            val2 = random.randrange(0x0, 0xFF)
            msg = CANMessage(canID, [val1, 0, val2, 0])

            self._receiveFrame(msg)
            time.sleep(0.5)

    '''
    '''
    def _receiveFrame(self, msg):
        print("Got Frame: " + str(msg))
        self._canRxQueue.put(msg)

    '''
    '''
    def getInterfaceObject(self):
        return self

    '''
    '''
    def initializeInterface(self):
        self._rxThread.start()

    '''
    '''
    def finalizeInterface(self):
        self._stopRxThread = True
        self._rxThread.join()

    def getNextFrame(self):
        '''
        '''
        return self._canRxQueue.get(timeout=0.01)

    def hasNextFrame(self):
        '''
        '''
        return not self._canRxQueue.empty()

    def sendFrame(self, frame):
        '''
        '''
        print("Sending frame from virtual interface")

    def isOpen(self):
        '''
        '''
        return True