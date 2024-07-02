import sys

from PyQt6.QtWidgets import QApplication, QMainWindow

from util.logger_global import *

from ui.mainwindow import MainWindow


if __name__ == "__main__":
    # Initialize the Logger System
    initializeDefaultLogger(consoleOutput=True)

    # Create the UI object
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    app.exec()

    ## Stop the Console Logger Output
    finalizeDefaultLogger()
