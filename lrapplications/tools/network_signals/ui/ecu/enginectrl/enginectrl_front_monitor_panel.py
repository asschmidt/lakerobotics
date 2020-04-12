'''
Panel to show the data and interact with the PowerManager ECU

@author Andreas Schmidt
'''

import wx

from network.can.can_datamodel import *
from network.can.can_data_connector import *
from network.can.can_data_subscriber import *

from ui.wx_ui_model_connector import *
from ui.panels.base_monitor_panel import *

from network.can.can_global import *

class EngCtrlFrontMonitorPanel(BaseMonitorPanel):
    '''
    Panel to show the CAN values of the Engine Control Front ECU
    '''

    # Signal IDs of the Power Manager ECU which should be shown in the List Control
    ENG_SPEED_FRONT_LEFT = "Engine_Speed_F_L"
    ENG_SPEED_FRONT_RIGHT = "Engine_Speed_F_R"

    WHEEL_SPEED_FRONT_LEFT = "Wheel_Speed_F_L"
    WHEEL_SPEED_FRONT_RIGHT = "Wheel_Speed_F_R"

    def __init__(self, parent):
        '''
        Initializes the UI panel including the UI Connector and the Subscriber
        '''
        super().__init__(parent)
        self._initializeData()

        # Create and register a CAN subscriber for the dynamic model
        self._uiConnector = WxUIModelConnector(self)
        self._canSubscriber = CANDataUISubscriber(self._uiConnector)
        CANGlobal.getInstance().getDynamicModel().registerSubscriber(self._canSubscriber)

    def _initializeData(self):
        '''
        Adds the CAN signals to the internal list
        '''
        self._addSignalToList(self.ENG_SPEED_FRONT_LEFT)
        self._addSignalToList(self.ENG_SPEED_FRONT_RIGHT)

        self._addSignalToList(self.WHEEL_SPEED_FRONT_LEFT)
        self._addSignalToList(self.WHEEL_SPEED_FRONT_RIGHT)
