from struct import pack, unpack
from pyusbtin import CANMessage


from model.additional_model_data import MessageGeneratorData
from network.can.can_base_connector import CANBaseConnector

class CANDataConnector(CANBaseConnector):
    '''
    Connects the CAN Interface Thread with the dynamic data model object
    As soon as a CAN message is received by the CAN Interface thread, the CAN Message
    is decoded and added to the dynamic data model. For this, the CAN-ID is used as
    search key to find the definition of the CAN Message structure
    This class is also responsible for connecting so called protocol handler to a 
    CAN-ID.
    '''

    def __init__(self, dynamicDataModel, protocolHandlerManager = None):
        '''
        Initializes the CAN Data Connector with the provided Dynamic Data Model
        object. It also initializes the CAN-ID Lookup Table
        Additionally a protocol handler manager class can be provided which is responsible
        to the protocol handler hooks
        '''
        super().__init__()

        self._dataModel = dynamicDataModel
        self._protocolHandlerManager = protocolHandlerManager
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

    def registerProtocolHandlerManager(self, protocolHandlerManager):
        '''
        Sets the internal used Protocol Handler Manager object
        '''
        self._protocolHandlerManager = protocolHandlerManager

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

        if msgObj is not None:
            # Convert the data to a byte array
            dataArray = list(pack('<Q', canMessage.get_data()))

            # Iterate over all signals in the message
            for signalRef in msgObj.Signals:
                self._dataModel.updateDataModelEntry(signalRef.Signal.ID, dataArray)
        else:
            # If the CAN-ID is not associated with a message, check for 
            # special CAN-IDs used for prototcols
            if self._protocolHandlerManager is not None:
                self._protocolHandlerManager.handleCANMessage(self, canMessage)

    def transmitCANMessage(self, canMessage):
        '''
        Transmit a CAN Message via the internally referenced CAN Thread
        '''
        if self._canThreadInterface is not None:
            self._canThreadInterface.transmitFrame(canMessage)