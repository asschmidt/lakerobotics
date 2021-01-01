import wx

from network.can.can_global import *

from pyusbtin.usbtin import CANMessage

class EngineCtrlParameterCtrlPanel(wx.Panel):
    '''
    Panel for controlling parameter for the Engine Control ECUs
    '''

    def __init__(self, parent):
        '''
        Initializes the panel
        '''
        super().__init__(parent)

        requestBtn = wx.Button(self, wx.ID_ANY, 'Request Values')
        self.Bind(wx.EVT_BUTTON, self.onRequestValue, requestBtn)

        setValueBtn = wx.Button(self, wx.ID_ANY, 'Set Values')
        self.Bind(wx.EVT_BUTTON, self.onSetValue, setValueBtn)

        topSizer = wx.BoxSizer(wx.VERTICAL)
        btnSizer = wx.BoxSizer(wx.VERTICAL)

        btnSizer.Add(requestBtn, 0, wx.ALL | wx.ALIGN_RIGHT, 5)
        btnSizer.Add(setValueBtn, 0, wx.ALL | wx.ALIGN_RIGHT, 5)

        topSizer.Add(btnSizer, 0, wx.EXPAND | wx.ALL | wx.ALIGN_RIGHT | wx.ALIGN_TOP, 5)

        self.SetSizer(topSizer)
        topSizer.Fit(self)

    def onSetValue(self, event):
        '''
        '''
        networkBuilder = CANGlobal.getInstance().getNetworkBuilder()
        rearECU = networkBuilder.getNode('Node_ECU_Rear')
        if rearECU is not None:
            paramList = CANGlobal.getInstance().getParameterModel().getParameterListForNode(rearECU.getMainNetworkID())
            for param in paramList:
                paramDef = param.getParameterDefinition()
                reqMessage = CANMessage(rearECU.getMainNetworkID() + 1, (paramDef.GeneratorData['PARAM_NO'], 0x00, 0xAB, 0xCD, 0x00, 0x00))
                CANGlobal.getInstance().getCANThread().transmitFrame(reqMessage)
                time.sleep(0.1)

    def onRequestValue(self, event):
        '''
        '''
        networkBuilder = CANGlobal.getInstance().getNetworkBuilder()
        rearECU = networkBuilder.getNode('Node_ECU_Rear')
        if rearECU is not None:
            paramList = CANGlobal.getInstance().getParameterModel().getParameterListForNode(rearECU.getMainNetworkID())
            for param in paramList:
                paramDef = param.getParameterDefinition()
                reqMessage = CANMessage(rearECU.getMainNetworkID() + 1, (paramDef.GeneratorData['PARAM_NO'], 0x00))
                CANGlobal.getInstance().getCANThread().transmitFrame(reqMessage)
                time.sleep(0.1)