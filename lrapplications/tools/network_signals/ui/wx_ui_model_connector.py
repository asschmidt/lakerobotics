'''
UI-Model Connector class for Wx UI components

@author: Andreas
'''

import wx

class WxUIModelConnector:
    '''
    UI-Model Connector for Wx UI components

    Connects a "notify" event from the dynamic data model to the UI system.

    DynamicDataModel --> notifySubscriber() --> Subscriber --> notify() --> UI Connector
        --> provideDataToUI() --> UI --> receiveDataForUI()
    '''

    def __init__(self, targetUI):
        '''
        Initializes the UI-Model-Connector
        '''
        self._ui = targetUI

    def provideDataToUI(self, dataEntry):
        '''
        Calls the receiveDataForUI() method of the provided UI object in a "safe" way to allow updates
        of the UI from outside of the mainloop thread

        For the Wx framework, the method wx.CallAfter is used
        '''
        if self._ui != None:
            wx.CallAfter(self._ui.receiveDataForUI, paramEntry=dataEntry)