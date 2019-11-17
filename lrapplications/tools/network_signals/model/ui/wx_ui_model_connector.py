'''
Created on 05.11.2019

@author: Andreas
'''

import wx

'''
'''
class WxUIModelConnector:

    '''
    '''
    def __init__(self, targetUI):
        self._ui = targetUI

    '''
    '''
    def provideDataToUI(self, dataEntry):
        if self._ui != None:
            wx.CallAfter(self._ui.receiveDataForUI, data=dataEntry)