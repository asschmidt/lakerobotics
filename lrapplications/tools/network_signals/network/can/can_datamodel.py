'''
Created on 05.11.2019

@author: Andreas
'''

from model.static.messages import *
from model.static.signals import *

'''
'''
class CANDataDefinition:
    '''
    '''
    def __init__(self, message, signalInMessage):
        self._message = message
        self._signal = signalInMessage

    '''
    '''
    def getMessage(self):
        return self._message

    '''
    '''
    def getSignal(self):
        # We need to return the "Signal" member, because the _signal is a MessageSignalRef object
        return self._signal.Signal


'''
'''
class CANDataExtractFunctions:
    '''
    Extracts the data in form of an byte array out of the rawData parameter. The rawData parameter is assumed to
    be the payload of a CAN message which is between 1 and 8 Byte at maximum
    '''
    @staticmethod
    def extractDataBytes(dataDefRef, rawData):
        # Get the signal reference object inside the CAN message and get the signal position
        signalRef = dataDefRef.getMessage().findSignalReferenceByID(dataDefRef.getSignal().ID)
        # Adapt the position to a zero based index for the Signals array
        signalPosition = signalRef.Position - 1

        # Calculate the start byte for the signal
        startByte = 0
        for pos in range(0, signalPosition):
            startByte = startByte + int(dataDefRef.getMessage().Signals[pos].Signal.Size / 8)

        # Calculate the end byte for the signal
        endByte = startByte + int(signalRef.Signal.Size / 8)

        data = rawData[startByte:endByte]
        return data

    @staticmethod
    def _getSignedNumber(number, bitLength):
        mask = (2 ** bitLength) - 1
        if number & (1 << (bitLength - 1)):
            return number | ~mask
        else:
            return number & mask

    '''
    '''
    @staticmethod
    def extractInteger(dataDefRef, rawData):
        intValue = None

        # Get the data bytes as an array
        dataBytes = CANDataExtractFunctions.extractDataBytes(dataDefRef, rawData)
        # Check if the data array is valid
        if len(dataBytes) > 0:
            intValue = 0

            # Get a reference to the signal definition. This is needed for the exact data type
            # and the endianess
            signalRef = dataDefRef.getMessage().findSignalReferenceByID(dataDefRef.getSignal().ID).Signal
            # Calculate the number of bytes for this interger value
            numberOfBytes = int(signalRef.Size / 8)

            # Check if the signal has little endian or big endian data format
            if signalRef.Endianess == SignalEndianess.ENDIAN_LITTLE:
                # Little endian starts with last byte in the array
                startByte = numberOfBytes
                endByte = 0

                # Iterate over the byte array and build an integer value
                for bytePos in range(startByte, endByte, -1):
                    intValue = intValue + (dataBytes[bytePos - 1] << ((bytePos - 1) * 8))
            elif signalRef.Endianess == SignalEndianess.ENDIAN_BIG:
                # Big endian starts with the first byte in the array
                startByte = 0
                endByte = numberOfBytes

                # Iterate over the byte array and build an integer value
                for bytePos in range(startByte, endByte):
                    shiftCount = (numberOfBytes - 1) - bytePos
                    intValue = intValue + (dataBytes[bytePos] << (shiftCount * 8))
                
                intValue = CANDataExtractFunctions._getSignedNumber(intValue, 16)
            else:
                intValue = None

        return intValue