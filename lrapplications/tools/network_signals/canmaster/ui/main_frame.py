'''
Main frame (wx) class for the main window

@author Andreas Schmidt
'''

import wx

from can_global import *

from ui.dialogs.hw_interface_dlg import *
from ui.panels.pwr_manager_panel import *

class MainFrame(wx.Frame):
    '''
    Main window class based on wx Frame class for the CAN-Master GUI
    '''

    def __init__(self):
        '''
        Initializes the main window of the CAN Master
        '''
        super().__init__(parent=None, title='CAN Master', size=(1280, 768))

        self.Bind(wx.EVT_CLOSE, handler=self._onCloseEvent)

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
        startInterfaceItem = interfaceMenu.Append(wx.ID_ANY, 'Start HW Interface...')
        self.Bind(event=wx.EVT_MENU, handler=self._onHwInterfaceDlg, source=startInterfaceItem)
        stopInterfaceItem = interfaceMenu.Append(wx.ID_ANY, 'Stop HW Interface')
        stopInterfaceItem.Enable(False)

        menuBar.Append(interfaceMenu, "&Interface")

        # Create the data menu which holds all possible "UI panels" for the different topics of the CAN
        dataMenu = wx.Menu()

        # Create the sub-menu for "Chassis and Body"
        bodyMenu = wx.Menu()
        pwrManagerMenuItem = bodyMenu.Append(wx.ID_ANY, 'Power Manager ECU', '')
        self.Bind(event=wx.EVT_MENU, handler=self._onOpenPwrManager, source=pwrManagerMenuItem)

        # Add the "Chassis and Body" sub-menu to the  "Data" menu
        dataMenu.Append(wx.ID_ANY, 'Chassis and Body', bodyMenu)

        menuBar.Append(dataMenu, "&Data")

        self.SetMenuBar(menuBar)

    def _createStatusBar(self):
        '''
        Creates the status bar in the main window
        '''
        self._statusBar = self.CreateStatusBar()
        self._statusBar.SetStatusText("CAN Master ready")

    def _onHwInterfaceDlg(self, event):
        '''
        '''
        hwInterfaceDlg = HardwareInterfaceDialog(self)
        result = hwInterfaceDlg.ShowModal()
        if result == wx.ID_OK:
            comPort = hwInterfaceDlg.getCOM()
            canBaudrate = hwInterfaceDlg.getBaudrate()
            print("Starting CAN on " + comPort)
            print("With Baudrate: " + str(canBaudrate))
            CANGlobal.getInstance().initializeCAN("../j2p.xml", comPort, canBaudrate)

    def _onOpenPwrManager(self, event):
        '''
        Event Handler to open the "Power Manager" UI Panel
        '''
        pwrManagerFrame = wx.Frame(parent=self)
        pwrManagerPanel = PwrManagerPanel(pwrManagerFrame)
        pwrManagerFrame.Show()

    def _onExitApplication(self, event):
        '''
        Event Handler to close the main application
        '''
        wx.CallAfter(self.Close)

    def _onCloseEvent(self, event):
        '''
        '''
        CANGlobal.getInstance().finalizeCAN()
        self.Destroy()