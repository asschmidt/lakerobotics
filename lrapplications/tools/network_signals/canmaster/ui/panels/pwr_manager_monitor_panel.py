'''
Panel to show the data and interact with the PowerManager ECU

@author Andreas Schmidt
'''

import wx

from model.can.can_datamodel import *
from model.can.can_data_connector import *
from model.can.can_data_subscriber import *
from model.ui.wx_ui_model_connector import *

from ui.base_panel import *

from can_global import *

class PowerManagerMonitorPanel(BasePanel):
    '''
    Panel to show the CAN values of the Power Manager ECU
    '''

    # Signal IDs of the Power Manager ECU which should be shown in the List Control
    PWR_SUPPLY_ELEC_VOLTAGE = "Power_Supply_Electronic_Voltage"
    PWR_SUPPLY_ELEC_CURRENT = "Power_Supply_Electronic_Current"
    PWR_SUPPLY_MOTOR_VOLTAGE = "Power_Supply_Motor_Voltage"
    PWR_SUPPLY_MOTOR_CURRENT = "Power_Supply_Motor_Current"

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
        self._addSignalToList(self.PWR_SUPPLY_ELEC_VOLTAGE)
        self._addSignalToList(self.PWR_SUPPLY_ELEC_CURRENT)
        self._addSignalToList(self.PWR_SUPPLY_MOTOR_VOLTAGE)
        self._addSignalToList(self.PWR_SUPPLY_MOTOR_CURRENT)