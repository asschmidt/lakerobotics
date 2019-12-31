'''
Classes to build a CAN message based on the structure definition out of the XML data
and the values for the signals provided via parameter

@author Andreas Schmidt
'''

from model.networks import *
from model.signals import *
from model.messages import *
from model.nodes import *
from model.network_builder import *
from model.dynamic_datamodel import *
from model.measurement_model import *
from model.model_subscriber import *

from model.can.can_datamodel import *

from pyusbtin.usbtin import CANMessage


class CANMessageSignalValue:
    '''
    Class to hold the information about a signal ID and the corresponding value
    for a specific CAN message
    '''

    def __init__(self, signalID="Unkown", signalValue=None):
        '''
        Initializes the Signal-Value Mapping
        '''
        self.SignalID = signalID
        self.SignalValue = signalValue

    def __repr__(self):
        '''
        Returns a string representing the Signal-ID/Value pair
        '''
        return self.SignalID + " = " + str(self.SignalValue)#

class CANMessageBuilder:
    '''
    Class to create a CAN message out of a data definition (based on XML) and the values
    (based on a Signal-Value Mapping)
    '''

    def __init__(self, networkBuilder):
        '''
        Initializes the instance of the CAN Message Builder
        '''
        self._networkBuilder = networkBuilder

    def buildMessage(self, messageID, signalValueDict):
        '''
        Builds a CAN Message object based on the data definition and the provided
        signal value mapping
        '''
        try:
            msgDef = self._networkBuilder.getMessages()[messageID]

            dataArray = []

            for signalIdx in range(0, len(msgDef.Signals)):
                signal = msgDef.Signals[signalIdx].Signal

                signalValue = signalValueDict[signal.ID]

                if signal.Size == 1 or signal.Size == 8:
                    dataArray = dataArray + self._makeByteValue(signalValue)
                elif signal.Size == 16:
                    dataArray = dataArray + self._makeWordValue(signalValue, signal.Endianess)

            canMessage = CANMessage(msgDef.GeneratorData['CAN_ID'], dataArray)
            return canMessage
        except:
            print("Message " + str(messageID) + " not found")

    def _makeByteValue(self, value):
        '''
        '''
        return [int(value & 0xFF)]

    def _makeWordValue(self, value, endianess):
        '''
        '''
        valueA = int(value & 0x00FF)
        valueB = int((value & 0xFF00) >> 8)

        if endianess == SignalEndianess.ENDIAN_BIG:
            return [valueB, valueA]
        elif endianess == SignalEndianess.ENDIAN_LITTLE:
            return [valueA, valueB]
        else:
            return -1