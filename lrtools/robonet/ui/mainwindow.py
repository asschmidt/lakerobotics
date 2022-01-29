from PyQt5.QtCore import (QFile, QFileInfo, QPoint, QSettings, QSignalMapper, QSize, QTextStream, Qt)
from PyQt5.QtGui import QIcon, QKeySequence
from PyQt5.QtWidgets import (QAction, QApplication, QFileDialog, QMainWindow, QMdiArea, QMessageBox, QTextEdit, QWidget)

class MainWindow(QMainWindow):
    '''
    Main window of the NetMaster Application.
    The main window also contains a reference to the global application context instance
    which contains the global data used across all modules
    '''
    def __init__(self):
        super().__init__()

        # Create the MDI area and use it as central widget
        self.mdiArea = QMdiArea()
        self.mdiArea.subWindowActivated.connect(self.updateMenus)
        self.mdiArea.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.mdiArea.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.setCentralWidget(self.mdiArea)

        # Create a signal mapper instance used to connect signals for
        # sub windows (MDI childs)
        self.windowMapper = QSignalMapper(self)
        self.windowMapper.mapped[QWidget].connect(self.setActiveSubWindow)

        # Read the application settings
        self.readSettings()

        # Create the UI elements of the main window
        self.createActions()
        self.createMainMenus()
        self.createMainToolBar()
        self.createMainStatusBar()
        self.updateMenus()

        self.setWindowTitle("NetMaster")

    def closeEvent(self, event):
        self.mdiArea.closeAllSubWindows()
        if self.mdiArea.currentSubWindow():
            event.ignore()
        else:
            self.writeSettings()
            event.accept()

    def about(self):
        QMessageBox.about(self, "About MDI",
                "The <b>MDI</b> example demonstrates how to write multiple "
                "document interface applications using Qt.")

    def updateMenus(self):
        hasMdiChild = (self.activeMdiChild() is not None)
        self.closeAct.setEnabled(hasMdiChild)
        self.closeAllAct.setEnabled(hasMdiChild)
        self.tileAct.setEnabled(hasMdiChild)
        self.cascadeAct.setEnabled(hasMdiChild)
        self.nextAct.setEnabled(hasMdiChild)
        self.previousAct.setEnabled(hasMdiChild)
        self.separatorAct.setVisible(hasMdiChild)

    def updateWindowMenu(self):
        '''
        Re-creates the "Window" menu respectively the items below that menu
        to support the window switching of the MDI childs and also commands
        for the the arrangement of the child windows
        '''
        # Clear all menu items in the Window menu
        self.windowMenu.clear()
        # Add menu items for general child window handling and arrangement
        self.windowMenu.addAction(self.closeAct)
        self.windowMenu.addAction(self.closeAllAct)
        self.windowMenu.addSeparator()
        self.windowMenu.addAction(self.tileAct)
        self.windowMenu.addAction(self.cascadeAct)
        self.windowMenu.addSeparator()
        self.windowMenu.addAction(self.nextAct)
        self.windowMenu.addAction(self.previousAct)
        self.windowMenu.addAction(self.separatorAct)

        # Get a list of all MDI child windows
        windows = self.mdiArea.subWindowList()
        # Show menu item separator only if there are MDI child windows
        self.separatorAct.setVisible(len(windows) != 0)

        # Iterate over alls MDI child windows
        for i, window in enumerate(windows):
            child = window.widget()

            # Generate the menu-item text for the MDI child windows
            text = "%d %s" % (i + 1, child.userFriendlyCurrentFile())
            # For the first 9 windows, we also generate a keyboard shortcut
            if i < 9:
                text = '&' + text

            # Add the menu items for the child window to the Window menu
            action = self.windowMenu.addAction(text)
            action.setCheckable(True)
            action.setChecked(child is self.activeMdiChild())
            action.triggered.connect(self.windowMapper.map)
            self.windowMapper.setMapping(action, window)

    def createActions(self):
        '''
        Creates the common actions for the main window including the File Exit,
        Window arrangement and About actions.
        '''
        # Create "Close" and "Exit" actions
        self.exitAct = QAction("E&xit", self, shortcut=QKeySequence.Quit, statusTip="Exit the application", triggered=QApplication.instance().closeAllWindows)
        self.closeAct = QAction("Cl&ose", self, statusTip="Close the active window", triggered=self.mdiArea.closeActiveSubWindow)
        self.closeAllAct = QAction("Close &All", self, statusTip="Close all the windows", triggered=self.mdiArea.closeAllSubWindows)

        # Create "Window" actions
        self.tileAct = QAction("&Tile", self, statusTip="Tile the windows", triggered=self.mdiArea.tileSubWindows)
        self.cascadeAct = QAction("&Cascade", self, statusTip="Cascade the windows", triggered=self.mdiArea.cascadeSubWindows)
        self.nextAct = QAction("Ne&xt", self, shortcut=QKeySequence.NextChild, statusTip="Move the focus to the next window", triggered=self.mdiArea.activateNextSubWindow)
        self.previousAct = QAction("Pre&vious", self, shortcut=QKeySequence.PreviousChild, statusTip="Move the focus to the previous window", triggered=self.mdiArea.activatePreviousSubWindow)

        self.separatorAct = QAction(self)
        self.separatorAct.setSeparator(True)

        # Create "About" actions
        self.aboutAct = QAction("&About", self, statusTip="Show the application's About box", triggered=self.about)
        self.aboutQtAct = QAction("About &Qt", self, statusTip="Show the Qt library's About box", triggered=QApplication.instance().aboutQt)

    def createMainMenus(self):
        '''
        Create the menus for the main menu
        '''
        # Create "File" menu
        self.fileMenu = self.menuBar().addMenu("&File")
        self.fileMenu.addAction(self.closeAct)
        self.fileMenu.addAction(self.closeAllAct)
        self.fileMenu.addSeparator()
        self.fileMenu.addAction(self.exitAct)

        # Create "Window" menu
        self.windowMenu = self.menuBar().addMenu("&Window")
        self.updateWindowMenu()
        self.windowMenu.aboutToShow.connect(self.updateWindowMenu)

        self.menuBar().addSeparator()

        # Create "Help" menu
        self.helpMenu = self.menuBar().addMenu("&Help")
        self.helpMenu.addAction(self.aboutAct)
        self.helpMenu.addAction(self.aboutQtAct)

    def createMainToolBar(self):
        '''
        Creates the main toolbar for the main window
        '''
        pass

    def createMainStatusBar(self):
        '''
        Creates the status bar for the main window
        '''
        self.statusBar().showMessage("Ready")

    def readSettings(self):
        settings = QSettings('Trolltech', 'MDI Example')
        pos = settings.value('pos', QPoint(200, 200))
        size = settings.value('size', QSize(400, 400))
        self.move(pos)
        self.resize(size)

    def writeSettings(self):
        settings = QSettings('Trolltech', 'MDI Example')
        settings.setValue('pos', self.pos())
        settings.setValue('size', self.size())

    def activeMdiChild(self):
        activeSubWindow = self.mdiArea.activeSubWindow()
        if activeSubWindow:
            return activeSubWindow.widget()
        return None

    def setActiveSubWindow(self, window):
        if window:
            self.mdiArea.setActiveSubWindow(window)

