from model.dynamic.model_subscriber import Subscriber

class CANDataUISubscriber(Subscriber):
    '''
    Subscriber for CAN messages. Connects a model change to an UI

    DynamicDataModel --> notifySubscriber() --> Subscriber --> notify() --> UI Connector --> provideDataToUI()
    '''

    def __init__(self, uiConnector):
        '''
        Initializes the CAN DAta UI Subscriber object with the provided UI Connector
        '''
        self._uiConnector = uiConnector

    def notify(self, dataEntry):
        '''
        Called if new data has been received in the DynamicData Model.

        The call is initiated via a Subscriber instance which is registered at the Dynamic Data Model
        '''
        #print("Got Notify for: " + dataEntry.getDataID())

        if self._uiConnector != None:
            self._uiConnector.provideDataToUI(dataEntry)