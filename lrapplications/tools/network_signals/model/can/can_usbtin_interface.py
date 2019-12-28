'''
Classes for CAN hardware interface of type USBtin

@author: Andreas
'''

import queue

from pyusbtin.usbtin import CANMessage, USBtin

from model.can.can_interface import *

'''
'''
class CANUSBtinInterface(CANInterface):
    '''
    '''
    def __init__(self):
        super().__init__("USBtin")

        self._usbtin = USBtin()
        self._usbtin.add_message_listener(self._receiveFrame)

        self._canRxQueue = queue.Queue()

    '''
    '''
    def _receiveFrame(self, msg):
        print("Got Frame: " + str(msg))
        self._canRxQueue.put(msg)

    '''
    '''
    def getInterfaceObject(self):
        return self._usbtin

    '''
    '''
    def initializeInterface(self):
        #self.finalizeInterface()

        self._usbtin.connect(self._comInterface)
        self._usbtin.open_can_channel(self._baudrate, USBtin.ACTIVE)

    '''
    '''
    def finalizeInterface(self):
        if self._usbtin != None:
            self._usbtin.close_can_channel()
            self._usbtin.disconnect()

    '''
    '''
    def getNextFrame(self):
        return self._canRxQueue.get(timeout=0.01)

    '''
    '''
    def hasNextFrame(self):
        return not self._canRxQueue.empty()

    '''
    '''
    def sendFrame(self, frame):
        self._usbtin.send(frame)