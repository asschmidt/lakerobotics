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

class CANGlobal:
    '''
    '''
    __instance = None

    def __init__(self):
        '''
        '''
        if CANGlobal.__instance != None:
            raise Exception("CAN Global is Singleton.")
        else:
            CANGlobal.__instance = self

        self._networkBuilder = None
        self._dynamicModel = None
        self._canInterface = None
        self._canThread = None

    @staticmethod
    def getInstance():
        '''
        '''
        if CANGlobal.__instance == None:
            CANGlobal()

        return CANGlobal.__instance

    def _initializeNetworkData(self, fileName):
        '''
        '''
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
        canMsgPreproc = CANMessagePreprocessor(self._networkBuilder)
        canMsgPreproc.prepareCANMessageDatabase()

        return self._networkBuilder

    def _initializeDynamicModel(self):
        '''
        '''
        # Create the dynamic model object
        self._dynamicModel = DynamicDataModel()

        # Initialize the dynamic model based on the loaded network data
        for msg in self._networkBuilder.getMessages().values():
            for sig in msg.Signals:
                dataDefRef = CANDataDefinition(msg, sig)
                dataEntry = DataModelEntry(sig.Signal.ID, dataDefRef)
                dataEntry.setExtractFunction(CANDataExtractFunctions.extractInteger)
                self._dynamicModel.addDataModelEntry(dataEntry)

    def _initializeCANInterface(self, comPort, canBaudrate):
        '''
        '''
        self._canInterface = CANUSBtinInterface()
        self._canInterface.setInterfaceParameter(comPort, canBaudrate)

    def _initializeCANThread(self):
        '''
        '''
        if self._canInterface != None:
            dataConnect = CANDataConnector(self._dynamicModel)
            self._canThread = CANInterfaceThread(self._canInterface, dataConnect)
            self._canThread.start()
        else:
            raise Exception("No CAN Interface initialized")

    def initializeCAN(self, networkFileName, comPort, canBaudrate):
        '''
        '''
        self._initializeNetworkData(networkFileName)
        self._initializeDynamicModel()
        self._initializeCANInterface(comPort, canBaudrate)
        self._initializeCANThread()

    def finalizeCAN(self):
        '''
        '''
        self._canThread.stop()
        self._canThread.join()

    def getDynamicModel(self):
        '''
        '''
        return self._dynamicModel