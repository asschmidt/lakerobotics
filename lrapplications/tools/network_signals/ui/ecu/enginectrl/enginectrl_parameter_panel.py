'''
Panel to show the parameter and interact with the Engine control ECU

@author Andreas Schmidt
'''

import wx

from network.can.can_data_extract import *
from network.can.can_data_connector import *
from network.can.can_parameter_subscriber import *

from ui.wx_ui_model_connector import *
from ui.panels.base_parameter_panel import *

from network.can.can_global import *

class EngCtrlParameterPanel(BaseParameterPanel):
    '''
    Panel to show the CAN Parameter of the Engine Control Front ECU
    '''

    def __init__(self, parent):
        '''
        Initializes the UI panel including the UI Connector and the Subscriber
        '''
        super().__init__(parent)
        self._initializeData()

        # Create and register a CAN subscriber for the dynamic model
        self._uiConnector = WxUIModelConnector(self)
        self._paramSubscriber = CANParameterUISubscriber(self._uiConnector)
        CANGlobal.getInstance().getParameterModel().registerSubscriber(self._paramSubscriber)

    def _initializeData(self):
        '''
        Adds the CAN Parameter to the internal list
        '''
        networkBuilder = CANGlobal.getInstance().getNetworkBuilder()
        rearECU = networkBuilder.getNode('Node_ECU_Rear')
        if rearECU is not None:
            paramList = CANGlobal.getInstance().getParameterModel().getParameterListForNode(rearECU.getMainNetworkID())
            for param in paramList:
                self._addParameterToList(rearECU.getMainNetworkID(), param.getParameterDefinition().ID)
                #print("Param: " + param.getParameterDefinition().ID)
