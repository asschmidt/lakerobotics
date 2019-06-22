import xml.etree.ElementTree as ET

from networks import *
from signals import *
from messages import *
from nodes import *

from network_builder import *

from can.can_message_generator import *

from jinja2 import Environment, Template, FileSystemLoader

'''
'''
def loadNetworkData(fileName):
    # Create the XML Parser object
    tree = ET.parse(fileName)
    root = tree.getroot()
    
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
    networkBuilder = NetworkBuilder(networks, nodes, messages, signals)
    return networkBuilder


# Load the templates
env = Environment(loader=FileSystemLoader('templates/'), trim_blocks = True, lstrip_blocks = True)


# Load the Network data from XML
networkBuilder = loadNetworkData("j2p.xml")

# Create the CAN Message generator object
canMsgGen = CANMessageGenerator(networkBuilder, env)
canMsgGen.generateCANMessageCode(0x1FF)