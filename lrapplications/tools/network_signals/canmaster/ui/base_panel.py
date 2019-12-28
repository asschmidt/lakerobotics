'''
Base class for all "can-related" data panels

@author Andreas Schmidt
'''

import wx

from can_global import *

class BasePanel(wx.Panel):
    '''
    Base panel for CAN connected panels
    '''

    def __init__(self, parent):
        '''
        Initializes the base panel and calls the internal _createListControl() method
        '''
        super().__init__(parent)

        # Dictionary to hold the signal IDs and the row-index mapping for the data
        self._signalToRowMap = {}

        self._mainListCtrl = self._createListControl()

        # Initialize the sizer component for this panel
        self._mainSizer = wx.BoxSizer(wx.VERTICAL)
        self._mainSizer.Add(self._mainListCtrl, 0, wx.ALL | wx.EXPAND, 5)
        self.SetSizer(self._mainSizer)

    def _createListControl(self):
        '''
        Creates the ListControl used to display the CAN main data for this panel.

        If the panel does not need a list control, this method can return None
        '''
        listCtrl = wx.ListCtrl(self, wx.NewIdRef(), size=(300,400), style=wx.LC_REPORT | wx.BORDER_SUNKEN)
        listCtrl.InsertColumn(0, 'Signal', width=240)
        listCtrl.InsertColumn(1, 'Value', width=100)
        listCtrl.InsertColumn(2, 'Unit', width=80)

        return listCtrl

    def _addSignalToList(self, signalID):
        '''
        '''
        lastIndex = self._mainListCtrl.GetItemCount()
        newIndex = -1

        signalEntry = CANGlobal.getInstance().getDynamicModel().getDataModelEntry(signalID)

        if signalEntry != None:
            itemData = wx.ListItem()
            itemData.SetId(lastIndex)
            itemData.SetText(signalEntry.getDataDefRef().getSignal().ID)

            newIndex = self._mainListCtrl.InsertItem(itemData)
            self._mainListCtrl.SetItem(newIndex, 1, "NA")
            self._mainListCtrl.SetItem(newIndex, 2, signalEntry.getDataDefRef().getSignal().PhysicalUnit)

            # Add the signal ID and the newIndex to the internal signal-Id-to-row-map
            self._signalToRowMap[signalEntry.getDataDefRef().getSignal().ID] = newIndex
        return newIndex

    def receiveDataForUI(self, data):
        '''
        Called by the UI-Model-Connector component if a data item in the model has changed

        DynamicDataModel --> notifySubscriber() --> Subscriber --> notify() --> UI Connector
            --> provideDataToUI() --> UI --> receiveDataForUI()
        '''
        if data != None:
            try:
                signalID = data.getDataDefRef().getSignal().ID
                row = self._signalToRowMap[signalID]
                self._mainListCtrl.SetItem(row, 1, str(data.getData()))
            except:
                pass