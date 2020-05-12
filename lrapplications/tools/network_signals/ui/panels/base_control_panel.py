'''
Base class for all "can-related" control data panels

@author Andreas Schmidt
'''

import wx

from network.can.can_global import *

class BaseControlPanel(wx.Panel):
    '''
    Base panel for CAN connected control panels
    '''

    def __init__(self, parent):
        '''
        Initializes the base panel
        '''
        super().__init__(parent)

        self._sizer = wx.GridBagSizer(5, 5)

        self._createUI()

        # Set the sizer and fit it to the content
        self.SetSizer(self._sizer)
        self._sizer.Fit(self)

    def _createUI(self):
        '''
        '''
        # Create the title text including a horizontal line
        titleText = wx.StaticText(self, label="Base Control Panel UI")
        self._sizer.Add(titleText, pos=(0,0), flag=wx.TOP | wx.LEFT | wx.BOTTOM, border = 5)

    def _getCheckboxValue(self, chkBox):
        '''
        '''
        val = 0
        if chkBox.GetValue() == True:
            val = 1
        else:
            val = 0

        return val

