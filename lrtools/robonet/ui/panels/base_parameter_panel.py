'''
Base class for all "can-related" parameter panels

@author Andreas Schmidt
'''

import wx

from network.can.can_global import *


class BaseParameterPanel(wx.Panel):
    '''
    Base panel for CAN connected parameter panels
    '''

    def __init__(self, parent):
        '''
        Initializes the base panel and calls the internal _createListControl() method
        '''
        super().__init__(parent)

        # Dictionary to hold the ids for additional data of the listctrl items
        self._signalToRowMap = {}
        self._rowToSignalMap = {}

        self._mainListCtrl = self._createListControl()
        self._createContextMenu()

        # Initialize the sizer component for this panel
        self._mainSizer = wx.BoxSizer(wx.VERTICAL)
        self._mainSizer.Add(self._mainListCtrl, 0, wx.ALL | wx.EXPAND, 5)
        self.SetSizer(self._mainSizer)

    def _createListControl(self):
        '''
        Creates the ListControl used to display the CAN main data for this panel.

        If the panel does not need a list control, this method can return None
        '''
        listCtrl = wx.ListCtrl(self, wx.NewIdRef(), size=(400,400), style=wx.LC_REPORT | wx.BORDER_SUNKEN)
        listCtrl.InsertColumn(0, 'Parameter', width=200)
        listCtrl.InsertColumn(1, 'Default Value', width=100)
        listCtrl.InsertColumn(2, 'Actual Value', width=100)
        listCtrl.InsertColumn(3, 'Unit', width=80)

        return listCtrl

    def _createContextMenu(self):
        '''
        '''
        pass
        #self._contextMenu = wx.Menu()
        #plotItem = self._contextMenu.Append(wx.ID_ANY, "Plot Signal")
        #self.Bind(wx.EVT_MENU, self.onPlotSignal, plotItem)
        #self._mainListCtrl.Bind(wx.EVT_CONTEXT_MENU, self.onShowContext)

    def _addParameterToList(self, nodeNetworkID, parameterId):
        '''
        Helper function to add a Parameter to the ListCtrl and also register it in the internal dict
        '''
        lastIndex = self._mainListCtrl.GetItemCount()
        newIndex = -1

        paramModel = CANGlobal.getInstance().getParameterModel().getParameterModelEntry(nodeNetworkID, parameterId)

        if paramModel is not None:
            paramDef = paramModel.getParameterDefinition()

            itemData = wx.ListItem()
            itemData.SetId(lastIndex)
            itemData.SetText(paramDef.ID)

            newIndex = self._mainListCtrl.InsertItem(itemData)
            self._mainListCtrl.SetItem(newIndex, 1, str(paramModel.getDefaultValue()))
            self._mainListCtrl.SetItem(newIndex, 2, str(paramModel.getActualValue()))
            self._mainListCtrl.SetItem(newIndex, 3, paramDef.Unit)

            # Add the signal ID and the newIndex to the internal signal-Id-to-row-map
            self._signalToRowMap[paramDef.ID] = newIndex
            self._rowToSignalMap[newIndex] = paramDef.ID

        return newIndex

    def receiveDataForUI(self, paramEntry):
        '''
        Called by the UI-Model-Connector component if a data item in the model has changed

        DynamicDataModel --> notifySubscriber() --> Subscriber --> notify() --> UI Connector
            --> provideDataToUI() --> UI --> receiveDataForUI()
        '''
        if paramEntry != None:
            try:
                paramID = paramEntry.getParameterDefinition().ID
                row = self._signalToRowMap[paramID]
                self._mainListCtrl.SetItem(row, 2, str(paramEntry.getActualValue()))
            except:
                pass

    def onShowContext(self, event):
        '''
        '''
        pass
        #pos = event.GetPosition()
        #pos = self._mainListCtrl.ScreenToClient(pos)
        #self._mainListCtrl.PopupMenu(self._contextMenu, pos)