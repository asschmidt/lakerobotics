import xml.etree.ElementTree as ET

from jinja2 import Environment, Template, FileSystemLoader

from model.static.networks import *
from model.static.signals import *
from model.static.messages import *
from model.static.nodes import *
from model.static.network_builder import *

from model.static.can.can_message_preprocessor import *

from codegen.can.can_message_generator import *

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
    return networkBuilder


# Load the templates
env = Environment(loader=FileSystemLoader('codegen/templates/'), trim_blocks=True, lstrip_blocks=True)


# Load the Network data from XML
networkBuilder = loadNetworkData("j2p.xml")

# Create the CAN Message generator object
canMsgPreProc = CANMessagePreprocessor(networkBuilder)
canMsgPreProc.prepareCANMessageDatabase()

canMsgGen = CANMessageGenerator(networkBuilder, env)
canMsgGen.generateCode()