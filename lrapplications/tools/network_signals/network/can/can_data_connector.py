'''
Created on 05.11.2019

@author: Andreas
'''
from struct import pack, unpack
from pyusbtin import CANMessage

from model.static.messages import *
from model.static.signals import *
from model.additional_model_data import *

from network.can.can_datamodel import *


'''
'''
class CANDataConnector:
    '''
    '''
    def __init__(self, dynamicDataModel):
        self._dataModel = dynamicDataModel
        self._canLookUp = {}

        self._generateCANLookUpTable()

    '''
    '''
    def _generateCANLookUpTable(self):
        # Iterate over all data entries in the model
        for dataEntry in self._dataModel.getDataModelEntryIterator():
            # Get the CAN-ID
            canID = dataEntry.getDataDefRef().getMessage().getGeneratorData(MessageGeneratorData.CAN_ID)
            # Get the message for that CAN-ID
            msgObj = dataEntry.getDataDefRef().getMessage()

            if canID != None:
                try:
                    # Check if we already have that CAN-ID
                    existingMsg = self._canLookUp[canID]
                except:
                    # If not, add it to the dictionary
                    self._canLookUp[canID] = msgObj

    '''
    '''
    def updateWithCANMessage(self, canMessage):
        msgObj = None

        try:
            # At first, get the message object in the data container
            msgObj = self._canLookUp[canMessage.mid]
        except:
            pass

        if msgObj != None:
            # Iterate over all signals in the message
            for signalRef in msgObj.Signals:
                # Convert the data to a byte array
                dataArray = list(pack('<Q', canMessage.get_data()))
                self._dataModel.updateDataModelEntry(signalRef.Signal.ID, dataArray)