import xml.etree.ElementTree as ET

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
    localNetworkBuilder = NetworkBuilder(networkVersion, networks, nodes, messages, signals)

    # Perform the CAN-ID calculations
    canMsgPreproc = CANMessagePreprocessor(localNetworkBuilder)
    canMsgPreproc.prepareCANMessageDatabase()

    return localNetworkBuilder


# Load the Network data from XML
networkBuilder = loadNetworkData("j2p.xml")

# Create the dynamic model object
dynamicModel = DynamicDataModel()

print("Nodes in Robot")
print("================================")

for node in networkBuilder.getNodeList():
    print("Node {}".format(node.Name))

# Initialize the dynamic model based on the loaded network data
# for msg in networkBuilder.getMessages().values():
#     for sig in msg.Signals:
#         dataDefRef = CANDataDefinition(msg, sig)
#         dataEntry = DataModelEntry(sig.Signal.ID, dataDefRef)
#         dataEntry.setExtractFunction(CANDataExtractFunctions.extractInteger)
#         dynamicModel.addDataModelEntry(dataEntry)
