'''
Frame for the monitoring of the CAN Signals for the Power Manager ECU

@author Andreas Schmidt
'''
import wx

from ui.panels.pwr_manager_monitor_panel import *

class PowerManagerMonitorFrame(wx.Frame):
    '''
    Frame for the Power Manager ECU monitoring
    '''

    def __init__(self, parent):
        '''
        Initializes the frame and adds the PowerManagerPanel to it
        '''
        super().__init__(parent, title='Power Manager ECU Monitor', size=(500, 200))

        # Create the PowerManagerPanel
        self._mainPanel = PowerManagerMonitorPanel(self)