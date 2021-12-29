'''
Base class for a matplotlib based plot panel

@author Andreas Schmidt
'''

import wx
import matplotlib as mpl
#mpl.use('WXAgg')

import matplotlib.pyplot as plt
from matplotlib.backends.backend_wxagg import FigureCanvasWxAgg as Canvas

from network.can.can_global import *

class BasePlotPanel(wx.Panel):
    '''
    '''

    def __init__(self, parent, id = -1, dpi = None, **kwargs):
        '''
        '''
        super().__init__(parent, id=id, **kwargs)

        # Dictionary to hold the signal IDs and the data-list
        self._signalToListMap = {}

        self._figure = mpl.figure.Figure(dpi=dpi, figsize=(2,2))
        self._canvas = Canvas(self, -1, self._figure)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self._canvas, -1 ,wx.EXPAND)
        self.SetSizer(sizer)

    def addSignalToPlot(self, signalID):
        '''
        Helper function to add a Signal to the Plot and also register it in the internal Signal-List-Map
        '''
        signalEntry = CANGlobal.getInstance().getDynamicModel().getDataModelEntry(signalID)

        if signalEntry != None:
            #pass
            #newIndex = self._mainListCtrl.InsertItem(itemData)
            #self._mainListCtrl.SetItem(newIndex, 1, "NA")
            #self._mainListCtrl.SetItem(newIndex, 2, signalEntry.getDataDefRef().getSignal().PhysicalUnit)

            # Add the signal ID and the newIndex to the internal signal-Id-to-row-map
            #self._signalToRowMap[signalEntry.getDataDefRef().getSignal().ID] = newIndex

            self.getFigure().gca().clear()
            self.getFigure().gca().set_xlim(0,20)
            self.getFigure().gca().set_ylim(0,20)
            self.getFigure().gca().plot([1,2,3,4,5],[2,1,4,2,3])
            plt.draw()
            print("Tried to redraw")

    def receiveDataForUI(self, data):
        '''
        Called by the UI-Model-Connector component if a data item in the model has changed

        DynamicDataModel --> notifySubscriber() --> Subscriber --> notify() --> UI Connector
            --> provideDataToUI() --> UI --> receiveDataForUI()
        '''
        if data != None:
            try:
                signalID = data.getDataDefRef().getSignal().ID
                #row = self._signalToRowMap[signalID]
                # Update plot
            except:
                pass

    def getFigure(self):
        '''
        Returns the figure instance of the plot
        '''
        return self._figure

    def getCanvas(self):
        '''
        Returns the canvas instance of the figure
        '''
        return self._canvas