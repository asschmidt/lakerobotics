from PyQt6.QtCore import QAbstractItemModel, QAbstractListModel, QModelIndex, QObject, Qt

from util.logger import *

from model.static.nodes import *
from model.static.messages import *
from model.static.signals import *

from model.dynamic.model_subscriber import *
from model.dynamic.dynamic_datamodel import *

from ui.generic_tree_item import TreeItem

class SignalViewModelSubscriber(Subscriber):
    def __init__(self, viewModel):
        super().__init__()
        self.viewModel = viewModel

    def notify(self, dataEntry):
        # Get the Row Index for the Signal ID
        signalID = dataEntry.getDataID()
        if signalID in self.viewModel.signalDict:
            rowIdx = self.viewModel.signalDict[signalID]
            self.viewModel.dataChanged.emit(self.viewModel.createIndex(rowIdx, 1), self.viewModel.createIndex(rowIdx, 1));


class SignalViewModel(QAbstractItemModel):
    def __init__(self, parent, networkBuilder, dynModel):
        super().__init__(parent)
        self.networkBuilder = networkBuilder
        self.dynamicModel = dynModel

        self.modelSubscriber = SignalViewModelSubscriber(self)
        self.dynamicModel.registerSubscriber(self.modelSubscriber)

        self.signalDict = {}

        self.rootItem = TreeItem("")
        self.setHeaderData(0, Qt.Orientation.Horizontal, "Signal")
        self.setHeaderData(1, Qt.Orientation.Horizontal, "Value")

    def addSignalToWatchList(self, signalID):
        try:
            signal = self.networkBuilder.getSignals()[signalID]
            if signal != None and signalID not in self.signalDict:
                lastIndex = self.rootItem.childCount()

                self.beginInsertRows(QModelIndex(), lastIndex, lastIndex)

                signalItem = TreeItem(signal, self.rootItem)
                self.rootItem.appendChild(signalItem)
                self.endInsertRows()

                self.signalDict[signalID] = self.rootItem.childCount() - 1
                #lastIndex = self.rootItem.childCount() - 1
                #self.dataChanged.emit(self.createIndex(lastIndex, 0), self.createIndex(lastIndex, 1));
        except:
            defaultLog("Signal {0} not found".format(signalID), LoggerEntryType.LOG_ERROR)
            pass

    def columnCount(self, parent):
        return 2

    def rowCount(self, parent):
        if parent.column() > 0:
            return 0

        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()

        return parentItem.childCount()

    def parent(self, index):
        if not index.isValid():
            return QModelIndex()

        parentItem = self.rootItem

        if parentItem == self.rootItem:
            return QModelIndex()

        return self.createIndex(parentItem.row(), 0, parentItem)

    def index(self, row, column, parent):
        if not self.hasIndex(row, column, parent):
            return QModelIndex()

        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()

        childItem = parentItem.child(row)
        if childItem:
            return self.createIndex(row, column, childItem)
        else:
            return QModelIndex()

    def data(self, index, role):
        if not index.isValid():
            return None

        if role == Qt.ItemDataRole.DisplayRole:
            row = index.row()
            if row >= 0 and row < self.rootItem.childCount():
                signalItem = self.rootItem.child(row)
                signal = signalItem.data(index.column())
                if index.column() == 0:
                    return signal.Name
                else:
                    dataEntry = self.dynamicModel.getDataModelEntry(signal.ID)
                    if dataEntry != None:
                        return str(dataEntry.getData())
                    else:
                        return "No Value"
            else:
                return None

    def headerData(self, section, orientation, role):
        if orientation != Qt.Orientation.Horizontal:
            return None

        if role != Qt.ItemDataRole.DisplayRole:
            return None

        if section == 0:
            return "Signal"
        elif section == 1:
            return "Value"
        else:
            return None