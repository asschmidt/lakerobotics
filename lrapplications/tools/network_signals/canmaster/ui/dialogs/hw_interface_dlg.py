import wx

class HardwareInterfaceDialog(wx.Dialog):
    '''
    '''

    def __init__(self, parent):
        '''
        Initializes the HW Interface dialog and builds the UI for the dialog
        '''
        super().__init__(parent, title='Hardware Interface')

        self._initUI()

    def _initUI(self):
        '''
        Build the UI for the dialog
        '''
        # Create the base panel and the used sizer
        self._panel = wx.Panel(self)
        self._sizer = wx.GridBagSizer(5, 5)

        # Create the title text including a horizontal line
        titleText = wx.StaticText(self._panel, label="Activate CAN Interface")
        self._sizer.Add(titleText, pos=(0,0), flag=wx.TOP | wx.LEFT | wx.BOTTOM, border = 5)

        titleLine = wx.StaticLine(self._panel)
        self._sizer.Add(titleLine, pos=(1, 0), span=(1, 5), flag=wx.EXPAND | wx.BOTTOM, border=10)

        # Create the HW property UI elements
        lblInterface = wx.StaticText(self._panel, label="COM Interface")
        self._sizer.Add(lblInterface, pos=(2, 0), flag=wx.TOP | wx.LEFT, border=10)

        self._cmbInterface = wx.Choice(self._panel, choices=['COM1', 'COM2', 'COM3', 'COM4', 'COM5', 'Virtual'])
        self._cmbInterface.SetSelection(3)
        self._sizer.Add(self._cmbInterface, pos=(2, 1), span=(1, 4), flag=wx.TOP | wx.EXPAND, border=10)

        lblBaudrate = wx.StaticText(self._panel, label="CAN Baudrate")
        self._sizer.Add(lblBaudrate, pos=(3, 0), flag=wx.TOP | wx.LEFT, border=10)

        self._cmbBaudrate = wx.ComboBox(self._panel, choices=['125000', '250000', '500000', '1000000'])
        self._cmbBaudrate.SetSelection(2)
        self._sizer.Add(self._cmbBaudrate, pos=(3, 1), span=(1, 4), flag=wx.TOP | wx.EXPAND, border=10)

        # Add the file selection for the XML data file
        lblXMLFile = wx.StaticText(self._panel, label="XML Data File")
        self._sizer.Add(lblXMLFile, pos=(4,0), flag = wx.TOP | wx.LEFT, border=10)

        self._txtXMLFile = wx.TextCtrl(self._panel)
        self._txtXMLFile.SetValue('../j2p.xml')
        self._sizer.Add(self._txtXMLFile, pos=(4,1), span=(1,3), flag = wx.TOP | wx.EXPAND, border=5)

        btnBrowse = wx.Button(self._panel, label="Browse...")
        btnBrowse.Bind(wx.EVT_BUTTON, handler=self._onBrowseFile)
        self._sizer.Add(btnBrowse, pos=(4,4), flag = wx.TOP | wx.RIGHT, border=5)

        # Create Optional attributes (for later use)
        sb = wx.StaticBox(self._panel, label="Optional Attributes")

        boxsizer = wx.StaticBoxSizer(sb, wx.VERTICAL)
        boxsizer.Add(wx.CheckBox(self._panel, label="???"), flag=wx.LEFT | wx.TOP, border=5)
        boxsizer.Add(wx.CheckBox(self._panel, label="??????"), flag=wx.LEFT, border=5)
        boxsizer.Add(wx.CheckBox(self._panel, label="??????"), flag=wx.LEFT | wx.BOTTOM, border=5)
        self._sizer.Add(boxsizer, pos=(6, 0), span=(1, 5), flag=wx.EXPAND | wx.TOP | wx.LEFT | wx.RIGHT , border=10)

        # Create the dialog buttons
        helpButton = wx.Button(self._panel, label='Help')
        helpButton.Enable(False)
        self._sizer.Add(helpButton, pos=(7, 0), flag=wx.LEFT, border=10)

        okButton = wx.Button(self._panel, label="Ok")
        okButton.Bind(wx.EVT_BUTTON, self._onOK)
        self._sizer.Add(okButton, pos=(7, 3))

        cancelButton = wx.Button(self._panel, label="Cancel")
        cancelButton.Bind(wx.EVT_BUTTON, self._onCancel)
        self._sizer.Add(cancelButton, pos=(7, 4), span=(1, 1), flag=wx.BOTTOM|wx.RIGHT, border=10)

        # Set the sizer and fit it to the content
        self._panel.SetSizer(self._sizer)
        self._sizer.Fit(self)

    def _onOK(self, event):
        '''
        Event-Handler for the OK button.

        Closes the dialog and set the return code for the Modal-Window to OK
        '''
        self.EndModal(wx.ID_OK)

    def _onCancel(self, event):
        '''
        Event-Handler for the Cancel Button.

        Closes the dialog and set the return code for the Modal-Window to CANCEL
        '''
        self.EndModal(wx.ID_CANCEL)

    def _onBrowseFile(self, event):
        '''
        Event-Handler for the "Browse" button to select a XML data file
        '''
        with wx.FileDialog(self, "Open XML Data file", wildcard="XML Files (*.xml)|*.xml", style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST) as fileDialog:
            if fileDialog.ShowModal() == wx.ID_OK:
                pathname = fileDialog.GetPath()
                self._txtXMLFile.SetValue(pathname)

    def getXMLFile(self):
        '''
        Returns the current selected XML file in the text control
        '''
        return self._txtXMLFile.GetValue()

    def getCOM(self):
        '''
        Returns the selected COM interface string
        '''
        return self._cmbInterface.GetString(self._cmbInterface.GetSelection())

    def getBaudrate(self):
        '''
        Returns the selected CAN baudrate
        '''
        baudrate = 125000
        strBaudrate = self._cmbBaudrate.GetValue()

        try:
            baudrate = int(strBaudrate)
        except:
            pass

        return baudrate