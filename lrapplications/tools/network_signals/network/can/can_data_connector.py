from struct import pack, unpack
from pyusbtin import CANMessage


from model.additional_model_data import MessageGeneratorData


class CANDataConnector:
    '''
    Connects the CAN Interface Thread with the dynamic data model object
    As soon as a CAN message is received by the CAN Interface thread, the CAN Message
    is decoded and added to the dynamic data model. For this, the CAN-ID is used as
    search key to find the definition of the CAN Message structure
    '''

    def __init__(self, dynamicDataModel):
        '''
        Initializes the CAN Data Connector with the provided Dynamic Data Model
        object. It also initializes the CAN-ID Lookup Table
        '''
        self._dataModel = dynamicDataModel
        self._canLookUp = {}

        self._generateCANLookUpTable()

    def _generateCANLookUpTable(self):
        '''
        Generates a Loop-Up Table based on the CAN-IDs out of the Network Model
        This Look-Up Table is used to get the data definition objects for a known
        CAN-ID
        '''
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

    def updateWithCANMessage(self, canMessage):
        '''
        Called by the CAN-Interface Thread as soon as a new CAN Message has been received.
        The function checks the internal look-up table if the CAN-ID is known and if yes
        it decodes the CAN-Message payload according the signal definition of the CAN-Message
        '''
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