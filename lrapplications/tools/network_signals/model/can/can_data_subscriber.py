'''
Created on 05.11.2019

@author: Andreas
'''

from model.model_subscriber import *

class CANDataUISubscriber(Subscriber):
    '''
    Subscriber for CAN messages. Connects a model change to an UI

    DynamicDataModel --> notifySubscriber() --> Subscriber --> notify() --> UI Connector --> provideDataToUI()
    '''

    def __init__(self, uiConnector):
        '''
        '''
        self._uiConnector = uiConnector

    def notify(self, dataEntry):
        '''
        '''
        #print("Got Notify for: " + dataEntry.getDataID())

        if self._uiConnector != None:
            self._uiConnector.provideDataToUI(dataEntry)