'''
Global object (Singleton) to access the CAN related objects and functions
'''
import xml.etree.ElementTree as ET
import threading
import time
import queue

from util.logger import LoggerEntryType
from util.logger_global import defaultLog

from model.static.networks import NetworkDataParser
from model.static.signals import SignalDataParser
from model.static.messages import MessageDataParser
from model.static.nodes import NodeDataParser
from model.static.network_builder import NetworkBuilder
from model.static.can.can_message_preprocessor import CANMessagePreprocessor
from model.static.parameter.parameter_preprocessor import ParameterPreprocessor

from model.dynamic.dynamic_datamodel import DataModelEntry, DynamicDataModel
from model.dynamic.model_subscriber import Subscriber
from model.dynamic.node_parameter_model import NodeParameterModelData, NodeParameterDynamicModel

from network.can.can_data_definition import CANDataDefinition
from network.can.can_data_extract import CANDataExtractFunctions
from network.can.can_data_connector import CANDataConnector
from network.can.can_data_subscriber import CANDataUISubscriber
from network.can.can_thread import CANInterfaceThread
from network.can.can_usbtin_interface import CANUSBtinInterface
from network.can.can_virtual_interface import CANVirtualInterface
from network.can.can_protocol_handler_manager import CANProtocolHandlerManager
from network.can.can_parameter_protocol_handler import CANParameterProtocolHandler

class CANGlobal:
    '''
    Singleton to encapsulate the CAN objects and their handling
    '''
    __instance = None

    def __init__(self):
        '''
        Private constructor to initialize the Singleton instance
        '''
        if CANGlobal.__instance != None:
            raise Exception("CAN Global is Singleton.")
        else:
            CANGlobal.__instance = self

        self._networkBuilder = None
        self._dynamicModel = None
        self._canInterface = None
        self._canConnector = None
        self._canThread = None
        self._protocolHandlerManager = None

    @staticmethod
    def getInstance():
        '''
        Returns the Singleton instance
        '''
        if CANGlobal.__instance == None:
            CANGlobal()

        return CANGlobal.__instance

    def _initializeNetworkData(self, fileName):
        '''
        Loads the network data out of the provided XML file.

        This date includes the Signals, Messages, Nodes and Networks for the complete CAN system
        '''

        defaultLog("Parsing Network database {0}".format(fileName))

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
        self._networkBuilder = NetworkBuilder(networkVersion, networks, nodes, messages, signals)

        # Perform the CAN-ID calculations
        defaultLog("Performing CAN Message Preprocessing on {0} messages".format(len(self._networkBuilder.getMessages())))

        canMsgPreproc = CANMessagePreprocessor(self._networkBuilder)
        canMsgPreproc.prepareCANMessageDatabase()

        defaultLog("Performing Parameter Preprocessing")
        paramMsgPreProc = ParameterPreprocessor(self._networkBuilder)
        paramMsgPreProc.prepareParameterDatabase()

        return self._networkBuilder

    def _initializeDynamicModel(self):
        '''
        Initializeses the dynamic data model used to handle the CAN signals and messages
        '''

        defaultLog("Initializing Dynamic Data Model")
        # Create the dynamic model object
        self._dynamicModel = DynamicDataModel()

        # Initialize the dynamic model based on the loaded network data
        for msg in self._networkBuilder.getMessages().values():
            for sig in msg.Signals:
                dataDefRef = CANDataDefinition(msg, sig)
                dataEntry = DataModelEntry(sig.Signal.ID, dataDefRef)
                dataEntry.setExtractFunction(CANDataExtractFunctions.extractInteger)
                self._dynamicModel.addDataModelEntry(dataEntry)

        defaultLog("Initializing Dynamic Parameter Model")
        # Create the dynamic parameter model
        self._parameterModel = NodeParameterDynamicModel()

        # Initialize the Parameter model with all parameters from all nodes
        for node in self._networkBuilder.getNodeList():
            # Get the main Network ID of the Node
            nodeNetworkID = node.getMainNetworkID()
            # If there is a valid main network ID we add the parameter for this 
            # network ID to the dynamic data model
            if nodeNetworkID is not None:
                # Iterate over all parameter of the node
                for param in node.Parameters.values():
                    defaultLog("Adding parameter {0} for node {1} to parameter model".format(param.ID, node.ID))
                    paramModelData = NodeParameterModelData(node, param)
                    self._parameterModel.addParameterModelEntry(nodeNetworkID, paramModelData)

    def _initializeCANInterface(self, comPort, canBaudrate):
        '''
        Initializes the CAN interface used to connect to a CAN bus
        '''
        defaultLog("Initializing CAN Intergface on {0} with speed {1}".format(comPort, canBaudrate))

        if comPort == 'Virtual':
            self._canInterface = CANVirtualInterface()
        else:
            # Create an instance of the CAN USBtin interface. Later this should be configurable
            self._canInterface = CANUSBtinInterface()
            self._canInterface.setInterfaceParameter(comPort, canBaudrate)

    def _initializeCANThread(self):
        '''
        Initializes and start the CAN thread which handles the RX and TX of CAN messages
        '''

        defaultLog("Initializing CAN Thread")

        # Check whether the CAN interface is already initialized
        if self._canInterface != None:
            defaultLog("Creating CAN Data Connector")
            # Create the CAN data connector and bind it to the dynamic model instance
            self._canConnector = CANDataConnector(self._dynamicModel)
            defaultLog("Creating CAN Thread")
            # Create the thread and connect it with the interface and the data connector
            self._canThread = CANInterfaceThread(self._canInterface, self._canConnector)
            defaultLog("Starting CAN Thread")
            # Start the thread
            self._canThread.start()
        else:
            raise Exception("No CAN Interface initialized")

    def _initializeCANProtocolHandler(self):
        '''
        Initializes the CAN Protocol Handler Manager
        '''
        defaultLog("Initializing CAN Protocol Handler")

        self._protocolHandlerManager = CANProtocolHandlerManager(self._networkBuilder)
        self._protocolHandlerManager.registerProtocolHandler(CANParameterProtocolHandler(self._networkBuilder, self._canConnector, self._parameterModel))

        # Connect the Protocol Handler Manager with the CAN Connector
        self._canConnector.registerProtocolHandlerManager(self._protocolHandlerManager)

    def initializeCAN(self, networkFileName, comPort, canBaudrate):
        '''
        Initializes the complete CAN system incl. the XML data, Dynamic Model, CAN Interface and CAN Thread
        '''
        self._initializeNetworkData(networkFileName)
        self._initializeDynamicModel()
        self._initializeCANInterface(comPort, canBaudrate)
        self._initializeCANThread()
        self._initializeCANProtocolHandler()

    def finalizeCAN(self):
        '''
        Stops the CAN thread and waits for the thread to finish

        Remark: There is no timeout for waiting to finish the CAN thread. If this blocks, the system might hang
        '''
        print("Stopping CAN Thread")
        self._canThread.stop()
        self._canThread.join()

    def getDynamicModel(self):
        '''
        Returns the internal instance of the dynamic data model
        '''
        return self._dynamicModel

    def getNetworkBuilder(self):
        '''
        Returns the internal instance of the network builder
        '''
        return self._networkBuilder

    def getCANThread(self):
        '''
        Returns the internal instance of the CAN thread
        '''
        return self._canThread

    def isCANInitialize(self):
        '''
        Returns True, if the CAN thread is running and the CAN interface is connected
        '''
        canThreadOK = self._canThread != None and self._canThread.is_alive()
        canInterfaceOK = self._canThread != None and self._canInterface.isOpen()

        return  canThreadOK and canInterfaceOK