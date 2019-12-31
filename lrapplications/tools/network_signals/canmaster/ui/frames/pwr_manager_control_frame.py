'''
Frame for the controlling of the CAN Signals for the Power Manager ECU

@author Andreas Schmidt
'''
import wx

from ui.panels.pwr_manager_control_panel import *

class PowerManagerControlFrame(wx.Frame):
    '''
    Frame for the Power Manager ECU monitoring
    '''

    def __init__(self, parent):
        '''
        Initializes the frame and adds the PowerManagerPanel to it
        '''
        super().__init__(parent, title='Power Manager ECU Control', size=(350, 300))

        # Create the PowerManagerPanel
        self._mainPanel = PowerManagerControlPanel(self)