import wx
import wx.grid

'''
'''
class DataInterpreterFrame(wx.Frame):

    '''
    '''
    def __init__(self, parent):
        wx.Frame.__init__(self, parent)

        # Create a wxGrid object
        self.grid = wx.grid.Grid(self, -1)
        self._rowSignalMap = {}


    def initUI(self, measurement):
        # Then we call CreateGrid to set the dimensions of the grid
        self.grid.CreateGrid(len(measurement.Signals), 3)

        self.grid.SetColLabelValue(0, "Value")
        self.grid.SetColLabelValue(1, "Unit")

        rowCount = 0
        for signal in measurement.Signals.values():
            self.grid.SetRowLabelValue(rowCount, signal.SignalID)
            self.grid.SetCellValue(rowCount, 1, signal.SignalRef.PhysicalUnit)

            self._rowSignalMap[signal.SignalID] = rowCount
            rowCount = rowCount + 1

        self.grid.SetRowLabelSize(300)

    '''
    '''
    def receiveDataForUI(self, data):
        if data != None:
            try:
                signalID = data.getDataDefRef().getSignal().ID
                row = self._rowSignalMap[signalID]
                self.grid.SetCellValue(row,0, str(data.getData()))
            except:
                pass

