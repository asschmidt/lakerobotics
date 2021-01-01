'''
Frame for the parameter of the Engine Control ECU

@author Andreas Schmidt
'''
import wx

from ui.ecu.enginectrl.enginectrl_parameter_panel import *
from ui.ecu.enginectrl.enginectrl_parameter_ctrl_panel import *

class EngCtrlParameterFrame(wx.Frame):
    '''
    Frame for the Engine Control Front ECU parameter
    '''

    def __init__(self, parent):
        '''
        Initializes the frame and adds the PowerManagerPanel to it
        '''
        super().__init__(parent, title='Engine Control ECU Parameter', size=(500, 200))

        # Create the PowerManagerPanel
        pan = wx.Panel(self)

        topSizer = wx.BoxSizer(wx.HORIZONTAL)

        self._mainPanel = EngCtrlParameterPanel(pan)
        self._ctrlPanel = EngineCtrlParameterCtrlPanel(pan)

        topSizer.Add(self._mainPanel, 0, wx.ALL | wx.EXPAND, 5)
        topSizer.Add(self._ctrlPanel, 0, wx.ALL | wx.EXPAND, 5)

        pan.SetSizer(topSizer)
        topSizer.Fit(self)