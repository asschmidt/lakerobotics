import xml.etree.ElementTree as ET
import threading
import time
import queue

from model.static.networks import *
from model.static.signals import *
from model.static.messages import *
from model.static.nodes import *
from model.static.network_builder import *
from model.dynamic.dynamic_datamodel import *
from model.dynamic.model_subscriber import *

from model.static.can.can_message_preprocessor import *
from network.can.can_data_connector import *
from network.can.can_data_subscriber import *
from network.can.can_thread import *
from network.can.can_message_builder import *
from network.can.can_data_definition import *
from network.can.can_data_extract import *
from network.can.can_usbtin_interface import *

#from ui.wx_ui_model_connector import *

from data_interpreter_ui import *

def sendSetSpeedFront(networkBuilder, canThread, value):
    signalValueDict = {'Wheel_Speed_F_L_Setpoint' : value,
                           'Wheel_Speed_F_R_Setpoint' : value}

    msgBuilder = CANMessageBuilder(networkBuilder)
    canMsg = msgBuilder.buildMessage("Wheel_Speed_Front_Setpoint", signalValueDict)
    canThread.transmitFrame(canMsg)

def sendSetSpeedMid(networkBuilder, canThread, value):
    signalValueDict = {'Wheel_Speed_M_L_Setpoint' : value,
                           'Wheel_Speed_M_R_Setpoint' : value}

    msgBuilder = CANMessageBuilder(networkBuilder)
    canMsg = msgBuilder.buildMessage("Wheel_Speed_Mid_Setpoint", signalValueDict)
    canThread.transmitFrame(canMsg)

def sendSetSpeedRear(networkBuilder, canThread, value):
    signalValueDict = {'Wheel_Speed_R_L_Setpoint' : value,
                           'Wheel_Speed_R_R_Setpoint' : value}

    msgBuilder = CANMessageBuilder(networkBuilder)
    canMsg = msgBuilder.buildMessage("Wheel_Speed_Rear_Setpoint", signalValueDict)
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
canInterface.setInterfaceParameter("/dev/ttyACM1", 500000)

dataConnect = CANDataConnector(dynamicModel)
canThread = CANInterfaceThread(canInterface, dataConnect)
#canThread = CANSimulationThread(dataConnect)
canThread.start()

#logFile = open('logrun_1.csv', "w")

waitTime = 0.01
targetSpeed = 30
rampValue = 10 / (1 / waitTime)
currentTargetSpeed = 20

sendSetSpeedFront(networkBuilder, canThread, 0)
sendSetSpeedMid(networkBuilder, canThread, 0)
sendSetSpeedRear(networkBuilder, canThread, 0)

while True:
    try:
        #currentTargetSpeed = currentTargetSpeed + rampValue

        #if (currentTargetSpeed >= 30.0):
        #    currentTargetSpeed = 30.0
        #    rampValue = rampValue * -1
        #elif (currentTargetSpeed < 0.0):
        #    currentTargetSpeed = 0.0
        #    rampValue = rampValue * -1

        #sendSetSpeedFront(networkBuilder, canThread, int(currentTargetSpeed))
        #sendSetSpeedMid(networkBuilder, canThread, int(currentTargetSpeed))
        sendSetSpeedRear(networkBuilder, canThread, int(currentTargetSpeed))

        logString = str(dynamicModel.getDataModelEntry("Power_Supply_Electronic_Voltage").getData())
        print(logString)

        #logFile.write(logString + "\n")

        #if currentTargetSpeed == 30.0 or currentTargetSpeed == 0.0:
        #    time.sleep(5)


        # Wait 1 Seconds
        # for x in range(0, 100):
        #     logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
        #     print(logString)
        #     logFile.write(logString + "\n")
        #     time.sleep(0.01)

        # sendSetSpeed(networkBuilder, canThread, 20)

        # # Wait 5 Seconds
        # for x in range(0, 500):
        #     logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
        #     print(logString)
        #     logFile.write(logString + "\n")
        #     time.sleep(0.01)

        # sendSetSpeed(networkBuilder, canThread, 50)

        # # Wait 5 Seconds
        # for x in range(0, 500):
        #     logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
        #     print(logString)
        #     logFile.write(logString + "\n")
        #     time.sleep(0.01)

        # sendSetSpeed(networkBuilder, canThread, 1)

        # # Wait 5 Seconds
        # for x in range(0, 500):
        #     logString = str(dynamicModel.getDataModelEntry("Wheel_Speed_F_L").getData())
        #     print(logString)
        #     logFile.write(logString + "\n")
        #     time.sleep(0.01)

        # sendSetSpeed(networkBuilder, canThread, 1)
        time.sleep(waitTime)

    except KeyboardInterrupt:
        sendSetSpeedFront(networkBuilder, canThread, 0)
        sendSetSpeedMid(networkBuilder, canThread, 0)
        sendSetSpeedRear(networkBuilder, canThread, 0)
        time.sleep(2)
        break

canThread.stop()
canThread.join()

#logFile.close()