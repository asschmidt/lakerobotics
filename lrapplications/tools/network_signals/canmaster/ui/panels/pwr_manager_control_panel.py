'''
Panel to show the data and interact with the PowerManager ECU

@author Andreas Schmidt
'''

import wx

from model.can.can_datamodel import *
from model.can.can_data_connector import *
from model.can.can_data_subscriber import *
from model.can.can_message_builder import *

from model.ui.wx_ui_model_connector import *

from ui.base_control_panel import *

from can_global import *

class PowerManagerControlPanel(BaseControlPanel):
    '''
    Panel to control the CAN values of the Power Manager ECU
    '''

    def __init__(self, parent):
        '''
        Initializes the UI panel
        '''
        super().__init__(parent)

    def _createUI(self):
        '''
        '''
        # Create the title text including a horizontal line
        titleText = wx.StaticText(self, label="Power Manager Control Panel")
        self._sizer.Add(titleText, pos=(0,0), flag=wx.TOP | wx.LEFT | wx.BOTTOM, border = 5)

        self._createPowerActivationGroup(1)

    def _createPowerActivationGroup(self, rowNumber):
        '''
        '''
        # Create a static box to group the signals for the message
        sb = wx.StaticBox(self, label="Message: Power Stage Activation")
        staticSizer = wx.StaticBoxSizer(sb, wx.VERTICAL)

        boxsizer = wx.GridBagSizer(5, 5)

        boxsizer.Add(wx.StaticText(self, label="Activate Stage #1"), pos=(0, 0), flag=wx.LEFT | wx.TOP, border=5)
        self._chkActivateStage1 = wx.CheckBox(self, label="")
        boxsizer.Add(self._chkActivateStage1, pos=(0,1), flag=wx.LEFT | wx.TOP, border=5)

        boxsizer.Add(wx.StaticText(self, label="Activate Stage #2"), pos=(1, 0), flag=wx.LEFT | wx.TOP, border=5)
        self._chkActivateStage2 = wx.CheckBox(self, label="")
        boxsizer.Add(self._chkActivateStage2, pos=(1,1), flag=wx.LEFT | wx.TOP, border=5)

        boxsizer.Add(wx.StaticText(self, label="Activate Stage #3"), pos=(2, 0), flag=wx.LEFT | wx.TOP, border=5)
        self._chkActivateStage3 = wx.CheckBox(self, label="")
        boxsizer.Add(self._chkActivateStage3, pos=(2,1), flag=wx.LEFT | wx.TOP, border=5)

        boxsizer.Add(wx.StaticText(self, label="Activate Stage #4"), pos=(3, 0), flag=wx.LEFT | wx.TOP, border=5)
        self._chkActivateStage4 = wx.CheckBox(self, label="")
        boxsizer.Add(self._chkActivateStage4, pos=(3,1), flag=wx.LEFT | wx.TOP, border=5)

        sendButton = wx.Button(self, label="Send")
        sendButton.Bind(wx.EVT_BUTTON, self.sendMessageHandler)
        boxsizer.Add(sendButton, pos=(4, 0), flag=wx.RIGHT | wx.TOP)

        staticSizer.Add(boxsizer, flag=wx.EXPAND)
        self._sizer.Add(staticSizer, pos=(rowNumber, 0), span=(1, 3), flag=wx.EXPAND | wx.TOP | wx.LEFT | wx.RIGHT , border=10)

    def sendMessageHandler(self, event):
        '''
        '''
        signalValueDict = {'Power_Electronic_1_Active' : self._getCheckboxValue(self._chkActivateStage1),
                            'Power_Electronic_2_Active' : self._getCheckboxValue(self._chkActivateStage2),
                            'Power_Electronic_3_Active' : self._getCheckboxValue(self._chkActivateStage3),
                            'Power_Electronic_4_Active' : self._getCheckboxValue(self._chkActivateStage4)}

        msgBuilder = CANMessageBuilder(CANGlobal.getInstance().getNetworkBuilder())
        canMsg = msgBuilder.buildMessage("Power_Control", signalValueDict)

        CANGlobal.getInstance().getCANThread().transmitFrame(canMsg)
