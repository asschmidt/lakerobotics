from PyQt6.QtCore import QAbstractItemModel, QModelIndex, QObject, Qt

from ui.generic_tree_item import TreeItem

from model.static.nodes import *
from model.static.messages import *
from model.static.signals import *

class NodeTreeItem(TreeItem):
    def __init__(self, data, parent=None):
        super().__init__(data, parent)

    def data(self, column):
        if type(self.itemData) == NodeData:
            return self.itemData.Name

class NodeIterfaceTreeItem(TreeItem):
    def __init__(self, data, parent=None):
        super().__init__(data, parent)

    def data(self, column):
        if type(self.itemData) == NodeInterfaceData:
            return self.itemData.Name

class NodeIterfaceRxMessageTreeItem(TreeItem):
    def __init__(self, data, parent=None):
        super().__init__(data, parent)

    def data(self, column):
        return "RX Messages"

class NodeIterfaceTxMessageTreeItem(TreeItem):
    def __init__(self, data, parent=None):
        super().__init__(data, parent)

    def data(self, column):
        return "TX Messages"

class InterfaceMessageTreeItem(TreeItem):
    def __init__(self, data, parent=None):
        super().__init__(data, parent)

    def data(self, column):
        if type(self.itemData) == MessageData:
            return self.itemData.Name

class MessageSignalTreeItem(TreeItem):
    def __init__(self, data, parent=None):
        super().__init__(data, parent)

    def data(self, column):
        if type(self.itemData) == SignalData:
            return self.itemData.Name


class SystemTreeModel(QAbstractItemModel):
    def __init__(self, parent, topLevelNodes):
        super().__init__(parent)

        self.rootItem = TreeItem("System Definition")
        self.topLevelNodes = topLevelNodes
        self._setupModel()


    def _setupModel(self):
        # Add Nodes
        for node in self.topLevelNodes:
            nodeItem = NodeTreeItem(node, self.rootItem)
            self.rootItem.appendChild(nodeItem)
            # Add Interfaces for each node
            for interface in node.Interfaces.values():
                interfaceItem = NodeIterfaceTreeItem(interface, nodeItem)
                nodeItem.appendChild(interfaceItem)
                # Add RX Messages from each interface
                rxMessagesItem = NodeIterfaceRxMessageTreeItem(None, interfaceItem)
                interfaceItem.appendChild(rxMessagesItem)
                for rxMessageRef in interface.RxMessages.values():
                    rxMsg = InterfaceMessageTreeItem(rxMessageRef.Message, rxMessagesItem)
                    rxMessagesItem.appendChild(rxMsg)
                    # Add Signals from each RX message
                    for signalRef in rxMessageRef.Message.Signals:
                        signalItem = MessageSignalTreeItem(signalRef.Signal, rxMsg)
                        rxMsg.appendChild(signalItem)

                # Add TX Messages from each interface
                txMessagesItem = NodeIterfaceTxMessageTreeItem(None, interfaceItem)
                interfaceItem.appendChild(txMessagesItem)
                for txMessageRef in interface.TxMessages.values():
                    txMsg = InterfaceMessageTreeItem(txMessageRef.Message, txMessagesItem)
                    txMessagesItem.appendChild(txMsg)
                    # Add Signals from each TX Message
                    for signalRef in txMessageRef.Message.Signals:
                        signalItem = MessageSignalTreeItem(signalRef.Signal, txMsg)
                        txMsg.appendChild(signalItem)

    def columnCount(self, parent):
        return 1

    def data(self, index, role):
        if not index.isValid():
            return None

        if role != Qt.ItemDataRole.DisplayRole:
            return None

        item = index.internalPointer()

        return item.data(index.column())

    def flags(self, index):
        if not index.isValid():
            return Qt.NoItemFlags

        return Qt.ItemFlag.ItemIsEnabled | Qt.ItemFlag.ItemIsSelectable

    def headerData(self, section, orientation, role):
        if orientation == Qt.Orientation.Horizontal and role == Qt.ItemDataRole.DisplayRole:
            return self.rootItem.data(section)

        return None

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

    def parent(self, index):
        if not index.isValid():
            return QModelIndex()

        childItem = index.internalPointer()
        parentItem = childItem.parent()

        if parentItem == self.rootItem:
            return QModelIndex()

        return self.createIndex(parentItem.row(), 0, parentItem)

    def rowCount(self, parent):
        if parent.column() > 0:
            return 0

        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()

        return parentItem.childCount()
