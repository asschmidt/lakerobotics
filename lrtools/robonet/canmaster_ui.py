from util.logger_global import *

from ui.frames.main_frame import *


if __name__ == "__main__":
    # Initialize the Logger System
    initializeDefaultLogger(consoleOutput=True)

    # Create the UI object
    app = wx.App(0)
    ui = MainFrame()

    app.MainLoop()

    ## Stop the Console Logger Output
    finalizeDefaultLogger()
