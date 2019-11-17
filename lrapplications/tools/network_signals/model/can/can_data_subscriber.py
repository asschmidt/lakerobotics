'''
Created on 05.11.2019

@author: Andreas
'''

from model.model_subscriber import *

'''
'''
class CANDataSubscriber(Subscriber):

    '''
    '''
    def __init__(self, uiConnector, measurementInfo = None):
        self._uiConnector = uiConnector
        self._measurementInfo = measurementInfo

    '''
    '''
    def notify(self, dataEntry):
        # Check if dataEntry is part of measurement
        if self._measurementInfo != None:
            pass
        
        print("Got Notify for: " + dataEntry.getDataID())

        if self._uiConnector != None:
            self._uiConnector.provideDataToUI(dataEntry)