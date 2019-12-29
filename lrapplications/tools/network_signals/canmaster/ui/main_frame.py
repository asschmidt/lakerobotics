'''
Main frame (wx) class for the main window

@author Andreas Schmidt
'''

import wx

from can_global import *

from ui.dialogs.hw_interface_dlg import *
from ui.frames.pwr_manager_monitor_frame import *


class MainFrame(wx.Frame):
    '''
    Main window class based on wx Frame class for the CAN-Master GUI
    '''

    def __init__(self):
        '''
        Initializes the main window of the CAN Master
        '''
        super().__init__(parent=None, title='CAN Master', size=(1280, 768))

        # Bind some events of the main frame
        self.Bind(wx.EVT_CLOSE, handler=self._onCloseEvent)
        self.Bind(wx.EVT_IDLE, handler=self._onIdleEvent)

        # Create the UI elements
        self._createMenu()
        self._createStatusBar()

        self.Show()
        self.Center()

    def _createMenu(self):
        '''
        Creates the main menus including the binding of the event handler
        '''
        # Create the menu bar
        menuBar = wx.MenuBar()

        # Create the file Menu
        fileMenu = wx.Menu()
        exitMenuItem = fileMenu.Append(wx.ID_ANY, 'Exit', 'Close the application')
        self.Bind(event=wx.EVT_MENU, handler=self._onExitApplication, source=exitMenuItem)
        menuBar.Append(fileMenu, "&File")

        # Create the "Interface" menu
        interfaceMenu = wx.Menu()
        self._startInterfaceItem = interfaceMenu.Append(wx.ID_ANY, 'Start HW Interface...')
        self.Bind(event=wx.EVT_MENU, handler=self._onStartInterface, source=self._startInterfaceItem)

        self._stopInterfaceItem = interfaceMenu.Append(wx.ID_ANY, 'Stop HW Interface')
        self.Bind(event=wx.EVT_MENU, handler=self._onStopInterface, source=self._stopInterfaceItem)

        menuBar.Append(interfaceMenu, "&Interface")

        # Create the data menu which holds all possible "UI panels" for the different topics of the CAN
        dataMenu = wx.Menu()

        # Create the sub-menu for "Chassis and Body"
        bodyMenu = wx.Menu()
        # Create the "Power Manager ECU" Menu and add it to the body menu
        self._createPowerManagerMenu(bodyMenu)
        # Add the "Chassis and Body" sub-menu to the "Data" menu
        dataMenu.Append(wx.ID_ANY, 'Chassis and Body', bodyMenu)

        # Create the sub-menu for "Powertrain"
        powerTrainMenu = wx.Menu()
        # Create the "Engine ECU" menus and add them to the "Powertrain menu"
        self._createEngineControlUnitMenu(powerTrainMenu)
        # Add the "Powertrain" sub-menu to the "Data" menu
        dataMenu.Append(wx.ID_ANY, 'Powertrain', powerTrainMenu)

        menuBar.Append(dataMenu, "&Data")

        self.SetMenuBar(menuBar)

    def _createPowerManagerMenu(self, parentMenu):
        '''
        Creates the sub-menu for the "Power Manager ECU" and adds it as sub-menu to the
        provided parent menu.
        '''
        powerManagerMenu = wx.Menu()
        self._pwrManagerMonitorMenuItem = powerManagerMenu.Append(wx.ID_ANY, 'Monitor PwrMgr ECU', '')
        self._pwrManagerControlMenuItem = powerManagerMenu.Append(wx.ID_ANY, 'Control PwrMgr ECU', '')

        self.Bind(event=wx.EVT_MENU, handler=self._onOpenPwrManagerMonitor, source=self._pwrManagerMonitorMenuItem)
        self.Bind(event=wx.EVT_MENU, handler=self._onOpenPwrManagerControl, source=self._pwrManagerControlMenuItem)

        parentMenu.Append(wx.ID_ANY, 'Power Manager ECU', powerManagerMenu)

    def _createEngineControlUnitMenu(self, parentMenu):
        '''
        Creates the sub-menu for the "Engine Control ECUs" and adds it as sub-menu to the
        provided parent menu.
        '''
        frontEngineECU = wx.Menu()
        self._frontEngineECUMonitorMenuItem = frontEngineECU.Append(wx.ID_ANY, 'Monitor Front Axle Engine ECU', '')
        self._frontEngineECUMControlMenuItem = frontEngineECU.Append(wx.ID_ANY, 'Control Front Axle Engine ECU', '')

        #self.Bind(event=wx.EVT_MENU, handler=self._onOpenEngineECUMonitor, source=self._frontEngineECUMonitorMenuItem)
        #self.Bind(event=wx.EVT_MENU, handler=self._onOpenEngineECUControl, source=self._frontEngineECUMControlMenuItem)

        parentMenu.Append(wx.ID_ANY, 'Front Axle Engine ECU', frontEngineECU)

        middleEngineECU = wx.Menu()
        self._middleEngineECUMonitorMenuItem = middleEngineECU.Append(wx.ID_ANY, 'Monitor Middle Axle Engine ECU', '')
        self._middleEngineECUMControlMenuItem = middleEngineECU.Append(wx.ID_ANY, 'Control Middle Axle Engine ECU', '')

        #self.Bind(event=wx.EVT_MENU, handler=self._onOpenEngineECUMonitor, source=self._middleEngineECUMonitorMenuItem)
        #self.Bind(event=wx.EVT_MENU, handler=self._onOpenEngineECUControl, source=self._middleEngineECUMControlMenuItem)

        parentMenu.Append(wx.ID_ANY, 'Middle Axle Engine ECU', middleEngineECU)

        rearEngineECU = wx.Menu()
        self._rearEngineECUMonitorMenuItem = rearEngineECU.Append(wx.ID_ANY, 'Monitor Rear Axle Engine ECU', '')
        self._rearEngineECUMControlMenuItem = rearEngineECU.Append(wx.ID_ANY, 'Control Rear Axle Engine ECU', '')

        #self.Bind(event=wx.EVT_MENU, handler=self._onOpenEngineECUMonitor, source=self._rearEngineECUMonitorMenuItem)
        #self.Bind(event=wx.EVT_MENU, handler=self._onOpenEngineECUControl, source=self._rearEngineECUMControlMenuItem)

        parentMenu.Append(wx.ID_ANY, 'Rear Axle Engine ECU', rearEngineECU)

    def _createStatusBar(self):
        '''
        Creates the status bar in the main window
        '''
        self._statusBar = self.CreateStatusBar()
        self._statusBar.SetStatusText("CAN Master ready")

    def _onStartInterface(self, event):
        '''
        Opens the HW Interface Dialog and Starts the CAN Interface
        '''
        # Create the Dialog and show it modal
        hwInterfaceDlg = HardwareInterfaceDialog(self)
        result = hwInterfaceDlg.ShowModal()

        # If the user pressed OK, the HW Interface is started
        if result == wx.ID_OK:
            # The the parameter from the Dialog
            comPort = hwInterfaceDlg.getCOM()
            canBaudrate = hwInterfaceDlg.getBaudrate()
            xmlFile = hwInterfaceDlg.getXMLFile()
            # Initialize the CAN interface by loading the XML definitions, connect the CAN
            # and start the CAN thread
            print("Using XML File: " + xmlFile)
            print("Starting CAN on " + comPort)
            print("With Baudrate: " + str(canBaudrate))

            CANGlobal.getInstance().initializeCAN(xmlFile, comPort, canBaudrate)

    def _onStopInterface(self, event):
        '''
        Event-Handler to stop the HW interface and close the connection
        '''
        CANGlobal.getInstance().finalizeCAN()

    def _onOpenPwrManagerMonitor(self, event):
        '''
        Event Handler to open the "Power Manager" UI Panel
        '''
        pwrManagerMonitorFrame = PowerManagerMonitorFrame(self)
        pwrManagerMonitorFrame.Show()

    def _onOpenPwrManagerControl(self, event):
        '''
        '''
        pass

    def _onExitApplication(self, event):
        '''
        Event Handler to close the main application
        '''
        wx.CallAfter(self.Close)

    def _onCloseEvent(self, event):
        '''
        Close event of the main window.

        It closes the CAN connection and disconnects the CAN HW Interface. After that, the main window
        is destroyed
        '''
        try:
            CANGlobal.getInstance().finalizeCAN()
        except:
            pass

        self.Destroy()

    def _onIdleEvent(self, event):
        '''
        Event Handler for the On-Idle Event.

        Used to enable/disable some UI elements based on the application status
        '''

        # Enable/Disable the Start/Stop Interface commands
        canIsRunning = CANGlobal.getInstance().isCANInitialize()
        self._startInterfaceItem.Enable(not canIsRunning)
        self._stopInterfaceItem.Enable(canIsRunning)