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
from model.can.can_message_builder import *

from model.ui.wx_ui_model_connector import *

from data_interpreter_ui import *

def sendSetSpeed(networkBuilder, canThread, value):
    signalValueDict = {'Wheel_Speed_F_L_Setpoint' : value,
                           'Wheel_Speed_F_R_Setpoint' : value}

    msgBuilder = CANMessageBuilder(networkBuilder)
    canMsg = msgBuilder.buildMessage("Wheel_Speed_Front_Setpoint", signalValueDict)
    canThread.transmitFrame(canMsg)

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


# Load the Network data from XML
networkBuilder = loadNetworkData("j2p.xml")

# Create the dynamic model object
dynamicModel = DynamicDataModel()
# Initialize the dynamic model based on the loaded network data
for msg in networkBuilder.getMessages().values():
    for sig in msg.Signals:
        dataDefRef = CANDataDefinition(msg, sig)
        dataEntry = DataModelEntry(sig.Signal.ID, dataDefRef)
        dataEntry.setExtractFunction(CANDataExtractFunctions.extractInteger)
        dynamicModel.addDataModelEntry(dataEntry)

canInterface = CANUSBtinInterface()
canInterface.setInterfaceParameter("COM4", 500000)

dataConnect = CANDataConnector(dynamicModel)
canThread = CANInterfaceThread(canInterface, dataConnect)
#canThread = CANSimulationThread(dataConnect)
canThread.start()

logFile = open('logrun1.csv', "w")

while True:
    try:
        sendSetSpeed(networkBuilder, canThread, 0)

        # Wait 1 Seconds
        for x in range(0, 100):
            logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
            print(logString)
            logFile.write(logString + "\n")
            time.sleep(0.01)

        sendSetSpeed(networkBuilder, canThread, 20)

        # Wait 5 Seconds
        for x in range(0, 500):
            logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
            print(logString)
            logFile.write(logString + "\n")
            time.sleep(0.01)

        sendSetSpeed(networkBuilder, canThread, 50)

        # Wait 5 Seconds
        for x in range(0, 500):
            logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
            print(logString)
            logFile.write(logString + "\n")
            time.sleep(0.01)

        sendSetSpeed(networkBuilder, canThread, 1)

        # Wait 5 Seconds
        for x in range(0, 500):
            logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
            print(logString)
            logFile.write(logString + "\n")
            time.sleep(0.01)

        sendSetSpeed(networkBuilder, canThread, 1)
        time.sleep(4)

    except KeyboardInterrupt:
        break

canThread.stop()
canThread.join()

logFile.close()