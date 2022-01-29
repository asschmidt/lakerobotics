import sys

from PyQt5.QtWidgets import (QAction, QApplication, QFileDialog, QMainWindow, QMdiArea, QMessageBox, QTextEdit, QWidget)

from ui.mainwindow import MainWindow

if __name__ == '__main__':
    # Create the main Application Object and process commandline arguments
    app = QApplication(sys.argv)

    # Create MainWindow and show it (starts the main-loop)
    mainWin = MainWindow()
    mainWin.show()

    # Return the exit code of the application to the OS
    sys.exit(app.exec_())
