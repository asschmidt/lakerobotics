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

from data_interpreter_ui import *


'''
'''
def loadNetworkData(fileName):
    # Create the XML Parser object
    tree = ET.parse(fileName)
    root = tree.getroot()

    networkVersion = root.get("Version")

    # Create the parser for the <Network> elements
    networkParser = NetworkDataParser(root.find("Networks"))
    # Create the parser for the <Signal> elements
    signalParser = SignalDataParser(root.find("Signals"))

    # Parse networks and signals
    networks = networkParser.parse()
    signals = signalParser.parse()

    # Create the parser for the <Message> elements
    messageParser = MessageDataParser(networks, signals, root.find("Messages"))
    # Parse the messages
    messages = messageParser.parse()

    # Create the parser for the <Node> elements
    nodeParser = NodeDataParser(networks, messages, root.find("Nodes"))
    # Parse the node elements
    nodes = nodeParser.parse()

    # Create a NetworkBuilder object and return it
    networkBuilder = NetworkBuilder(networkVersion, networks, nodes, messages, signals)

    # Perform the CAN-ID calculations
    canMsgPreproc = CANMessagePreprocessor(networkBuilder)
    canMsgPreproc.prepareCANMessageDatabase()

    return networkBuilder

def loadMeasurementData(fileName, networkBuilder):
    # Create the XML Parser object
    tree = ET.parse(fileName)
    root = tree.getroot()

    # Create the parser for the <Measurement> elements
    measurementParser = MeasurementDataParser(root, networkBuilder)
    measurements = measurementParser.parse()

    return measurements

# Load the Network data from XML
networkBuilder = loadNetworkData("j2p.xml")
measurements = loadMeasurementData("measurement1.xml", networkBuilder)

# Create the dynamic model object
dynamicModel = DynamicDataModel()
# Initialize the dynamic model based on the loaded network data
for msg in networkBuilder.getMessages().values():
    for sig in msg.Signals:
        dataDefRef = CANDataDefinition(msg, sig)
        dataEntry = DataModelEntry(sig.Signal.ID, dataDefRef)
        dataEntry.setExtractFunction(CANDataExtractFunctions.extractInteger)
        dynamicModel.addDataModelEntry(dataEntry)


# Create the UI object
app = wx.App(0)
ui = DataInterpreterFrame(None)
ui.initUI(list(measurements.values())[0])
uiConnector = WxUIModelConnector(ui)

# Create and regsiter a CAN subscriber for the dynamic model
canSubscriber = CANDataUISubscriber(uiConnector, measurements)
dynamicModel.registerSubscriber(canSubscriber)

#for dataEntry in dynamicModel.getDataModelEntryIterator():
#    canID = dataEntry.getDataDefRef().getMessage().getGeneratorData('CAN_ID_HEX')
#    print("Data-ID: " + str(dataEntry.getDataID()) + "\tCAN: " + str(canID))

#rawData = [0xAB, 0x02, 0xCD, 0x01, 0x00, 0x00, 0x00, 0x00]
#dynamicModel.updateDataModelEntry("Power_Supply_Electronic_Voltage", rawData)
#dynamicModel.updateDataModelEntry("Power_Supply_Electronic_Current", rawData)

#print("Data-Value Power_Supply_Electronic_Voltage: " + str(hex(dynamicModel.getDataModelEntry("Power_Supply_Electronic_Voltage").getData())))
#print("Data-Value Power_Supply_Electronic_Current: " + str(hex(dynamicModel.getDataModelEntry("Power_Supply_Electronic_Current").getData())))

#msg = CANMessage(0x201, [0xED, 0x04, 0xFE, 0x05])
canInterface = CANUSBtinInterface()
canInterface.setInterfaceParameter("COM4", 500000)

dataConnect = CANDataConnector(dynamicModel)
canThread = CANInterfaceThread(canInterface, dataConnect)
#canThread = CANSimulationThread(dataConnect)
canThread.start()

#print("Data-Value Power_Supply_Electronic_Voltage: " + str(hex(dynamicModel.getDataModelEntry("Power_Supply_Electronic_Voltage").getData())))
#print("Data-Value Power_Supply_Electronic_Current: " + str(hex(dynamicModel.getDataModelEntry("Power_Supply_Electronic_Current").getData())))

ui.Show()
app.MainLoop()

canThread.stop()
canThread.join()