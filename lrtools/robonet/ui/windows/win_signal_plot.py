import matplotlib
import random
matplotlib.use('QtAgg')

from PyQt6 import QtCore, QtGui, QtWidgets
from PyQt6.QtWidgets import QWidget

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg, NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure

from model.dynamic.model_subscriber import *

class SignalPlotSubscriber(Subscriber):
    def __init__(self, view):
        super().__init__()
        self.view = view

    def notify(self, dataEntry):
        signalID = dataEntry.getDataID()
        if signalID == self.view.signalID:
            self.view.updatePlot(dataEntry.getData())

class MplCanvas(FigureCanvasQTAgg):

    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)
        super(MplCanvas, self).__init__(fig)


class SignalPlotWindow(QWidget):

    def __init__(self, parent, signalID, networkBuilder, dynamicModel):
        super().__init__(parent)

        # Store the Signal-ID of the signal which is plot in this window
        self.signalID = signalID

        self.networkBuilder = networkBuilder
        self.dynamicModel = dynamicModel

        # Prepare a plotting-data array for 50 values
        n_data = 50
        self.xdata = list(range(n_data))
        self.ydata = [0 for i in range(n_data)]

        self.canvas = MplCanvas(self, width=5, height=4, dpi=100)

        # Create toolbar, passing canvas as first parament, parent (self, the MainWindow) as second.
        toolbar = NavigationToolbar(self.canvas, self)

        layout = QtWidgets.QVBoxLayout()
        layout.addWidget(toolbar)
        layout.addWidget(self.canvas)

        # Create a placeholder widget to hold our toolbar and canvas.
        self.setLayout(layout)

        self._plot_ref = None
        self.updatePlot(0)

        # Register this the subscriber for the dynamic model
        self.subscriber  = SignalPlotSubscriber(self)
        self.dynamicModel.registerSubscriber(self.subscriber)

        # Setup a timer to trigger the redraw by calling update_plot.
        #self.timer = QtCore.QTimer()
        #self.timer.setInterval(100)
        #self.timer.timeout.connect(self.update_plot)
        #self.timer.start()

    def updatePlot(self, newYVal):
        # Drop off the first y element, append a new one.
        self.ydata = self.ydata[1:] + [newYVal]

        # Note: we no longer need to clear the axis.
        if self._plot_ref is None:
            # First time we have no plot reference, so do a normal plot.
            # .plot returns a list of line <reference>s, as we're
            # only getting one we can take the first element.
            plot_refs = self.canvas.axes.plot(self.xdata, self.ydata, 'r')
            self._plot_ref = plot_refs[0]
        else:
            # We have a reference, we can use it to update the data for that line.
            self._plot_ref.set_ydata(self.ydata)

        # Trigger the canvas to update and redraw.
        self.canvas.axes.relim()
        self.canvas.axes.autoscale_view(True, True, True)
        #self.canvas.axes.autoscale()
        self.canvas.draw()

