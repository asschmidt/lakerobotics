import xml.etree.ElementTree as ET
import threading
import time
import queue

from model.networks import *
from model.signals import *
from model.messages import *
from model.nodes import *
from model.network_builder import *
from model.dynamic_datamodel import *
from model.measurement_model import *
from model.model_subscriber import *

from model.can.can_message_preprocessor import *
from model.can.can_datamodel import *
from model.can.can_data_connector import *
from model.can.can_data_subscriber import *
from model.can.can_thread import *
from model.ui.wx_ui_model_connector import *

from ui.main_frame import *

# Create the UI object
app = wx.App(0)
ui = MainFrame()

app.MainLoop()