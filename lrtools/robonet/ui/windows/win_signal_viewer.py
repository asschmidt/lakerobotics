from PyQt6.QtCore import (QFile, QFileInfo, QPoint, QSettings, QSignalMapper, QSize, QTextStream, Qt)
from PyQt6.QtGui import QIcon, QKeySequence, QAction
from PyQt6.QtWidgets import (QFileDialog, QMainWindow, QMessageBox, QHBoxLayout, QWidget, QListView, QTreeView)

from ui.generic_tree_item import TreeItem
from ui.windows.signal_view_model import SignalViewModel

from ui.windows.win_signal_plot import SignalPlotWindow

class SignalViewerWindow(QWidget):
    def __init__(self, parent, networkBuilder, dynamicModel):
        super().__init__(parent)
        self.networkBuilder = networkBuilder
        self.dynamicModel = dynamicModel

        self.setWindowTitle("Signal Viewer")
        self.resize(800, 500)
        self.updateGeometry()

        self.signalModel = SignalViewModel(self, self.networkBuilder, self.dynamicModel)

        self.signalView = QTreeView(self)
        self.signalView.setModel(self.signalModel)

        dataLayout = QHBoxLayout()
        dataLayout.addWidget(self.signalView)
        self.setLayout(dataLayout)

        self.signalView.doubleClicked.connect(self.doubleClickItem)

    def connectSignal(self, signal):
        self.signalModel.addSignalToWatchList(signal.ID)

    def doubleClickItem(self, item):
        if item.isValid():
            dataItem = item.internalPointer()
            if type(dataItem) == TreeItem:
                print("Double Click on {0}".format(dataItem))

                parentWindow = self.parentWidget()
                mdiArea = parentWindow.mdiArea()

                plotWindow = SignalPlotWindow(mdiArea.parent(), dataItem.itemData.ID, self.networkBuilder, self.dynamicModel)
                plotWindow.setWindowTitle("Signal-Plot: [{0}]".format(dataItem.itemData.Name))
                mdiArea.addSubWindow(plotWindow)
                plotWindow.show()

