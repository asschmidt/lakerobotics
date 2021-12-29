'''
Frame for the monitoring of the CAN Signals for the Power Manager ECU

@author Andreas Schmidt
'''
import wx

from ui.ecu.enginectrl.enginectrl_monitor_panel import *

class EngCtrlMonitorFrame(wx.Frame):
    '''
    Frame for the Engine Control Front ECU monitoring
    '''

    def __init__(self, parent):
        '''
        Initializes the frame and adds the PowerManagerPanel to it
        '''
        super().__init__(parent, title='Engine Control Front ECU Monitor', size=(500, 200))

        # Create the PowerManagerPanel
        self._mainPanel = EngCtrlMonitorPanel(self)