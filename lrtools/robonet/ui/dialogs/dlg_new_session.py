from PyQt6.QtCore import (Qt)
from PyQt6.QtGui import QIcon, QKeySequence, QAction
from PyQt6.QtWidgets import (QFileDialog, QDialog, QMessageBox, QTextEdit, QWidget)

from PyQt6.uic import loadUi

class NewSessionDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        loadUi("ui/dialogs/dlg_new_session.ui", self)

        self.setFixedSize(self.width(), self.height())
        self._initInterfaceCombo()
        self._initBaudrateCombo()
        self._initBrowseButton()


    def _initInterfaceCombo(self):
        self.cmbHwInterface.addItem("/dev/ttyACM0")
        self.cmbHwInterface.addItem("/dev/ttyACM1")
        self.cmbHwInterface.addItem("/dev/ttyACM2")
        self.cmbHwInterface.addItem("/dev/ttyACM3")

        self.cmbHwInterface.setCurrentIndex(0)

    def _initBaudrateCombo(self):
        self.cmbBaudrate.addItems(["125000", "250000", "500000", "1000000"])
        self.cmbBaudrate.setCurrentIndex(2)

    def _initBrowseButton(self):
        self.txtSystemDefinitionFile.setText("/home/andreas/Projects/LR/lakerobotics/lrtools/robonet/j2p.xml")
        self.btnBrowse.clicked.connect(self._browseXmlFile)

    def _browseXmlFile(self):
        dlg = QFileDialog()
        dlg.setFileMode(QFileDialog.FileMode.AnyFile)
        dlg.setNameFilters(["All Files (*.*)", "XML Files (*.xml)"])

        if dlg.exec():
            filenames = dlg.selectedFiles()
            self.txtSystemDefinitionFile.setText(filenames[0])

    def getHwInterface(self):
        return self.cmbHwInterface.currentText()

    def getBaudrate(self):
        baudrate = 125000
        try:
            baudrate = int(self.cmbBaudrate.currentText())
        except:
            baudrate = 125000

        return baudrate

    def getSystemDefinitionFile(self):
        return self.txtSystemDefinitionFile.text()
