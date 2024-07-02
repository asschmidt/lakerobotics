from PyQt6.QtCore import (QFile, QFileInfo, QPoint, QSettings, QSignalMapper, QSize, QTextStream, Qt)
from PyQt6.QtGui import QIcon, QKeySequence, QAction
from PyQt6.QtWidgets import (QFileDialog, QMainWindow, QMessageBox, QHBoxLayout, QWidget, QTreeView)

from ui.windows.win_signal_viewer import SignalViewerWindow
from ui.windows.system_tree_model import SystemTreeModel, MessageSignalTreeItem

class SystemBrowserWindow(QWidget):
    def __init__(self, parent, networkBuilder):
        super().__init__(parent)
        self.networkBuilder = networkBuilder

        self.setWindowTitle("System Browser")

        nodeList = list(self.networkBuilder.getNodeList())
        self.systemTreeModel = SystemTreeModel(None, nodeList)
        self.systemTreeView = QTreeView(self)
        self.systemTreeView.setModel(self.systemTreeModel)

        dataLayout = QHBoxLayout()
        dataLayout.addWidget(self.systemTreeView)
        self.setLayout(dataLayout)

        self.systemTreeView.doubleClicked.connect(self.doubleClickItem)

    def doubleClickItem(self, item):
        if item.isValid():
            dataItem = item.internalPointer()
            if type(dataItem) == MessageSignalTreeItem:
                print("Double Click on {0}".format(dataItem.itemData.Name))
                # Find Signal Viewer Window
                signalViewer = self._findSignalViewer()
                if signalViewer != None:
                    signalViewer.connectSignal(dataItem.itemData)

    def _findSignalViewer(self):
        # Returns a QMdiSubWindow
        parentWindow = self.parentWidget()
        try:
            mdiArea = parentWindow.mdiArea()
            windows = mdiArea.subWindowList()

            # Iterate over alls MDI child windows
            for i, window in enumerate(windows):
                mdiChild = window.widget()
                if type(mdiChild) == SignalViewerWindow:
                    return mdiChild
        except:
            return None

        return None