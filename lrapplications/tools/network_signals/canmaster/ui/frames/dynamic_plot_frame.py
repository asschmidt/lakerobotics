'''
Frame for the monitoring of the CAN Signals for the Power Manager ECU

@author Andreas Schmidt
'''
import wx

from ui.base_plot_panel import *

class DynamicPlotFrame(wx.Frame):
    '''
    Frame for the dynamic plotting of signals
    '''

    def __init__(self, parent, frameTitle):
        '''
        Initializes the frame and adds the PlotPabel to it
        '''
        super().__init__(parent, title=frameTitle, size=(500, 200))

        # Create the PowerManagerPanel
        self._plotPanel = BasePlotPanel(self)

    def addSignalToPlot(self, signalID):
        '''
        '''
        self._plotPanel.addSignalToPlot(signalID)