from util.logger_global import defaultLog

from model.static.networks import NetworkDataBandwith, NetworkDataType


class NodeInterfaceData:
    '''
    Represents the network interface of a node. Including also dictionaries with all RX and TX
    messages related to this node respectivly interface
    '''

    def __init__(self):
        '''
        Initializes the NodeInterface data object with default values
        '''
        self.ID = "Unknown"                                 # Unique ID of the Node interface
        self.Name = "Unknown"
        self.NetworkID = "Unkown"                           # Used as a "node id" inside a specific network
        self.NetworkController = "Default"                  # Network Controller e.g. MCP2515, STM32F103 etc.
        self.NetworkType = NetworkDataType.UNKNOWN
        self.Bandwidth = NetworkDataBandwith.SPEED_UNKNOWN
        self.ConnectTo = None

        self.RxMessages = {}
        self.TxMessages = {}

class NodeInterfaceMessage:
    '''
    Represents a RX or TX message of the interface. Just a container class for the MessageData object
    '''
    def __init__(self):
        '''
        Initializes the NodeInterface Message object with default values
        '''
        self.Message = None
        self.Node = None

class ParameterType:
    '''
    Defines constants for different parameter types
    '''
    PARAM_UNKNOWN       = 0
    PARAM_BOOL          = 1
    PARAM_INT           = 2
    PARAM_FLOAT         = 3

    @classmethod
    def parseSignalType(self, paramTypeAttribValue):
        '''
        Parses the parameter type attribute string and returns a corresponding parameter type
        '''
        if paramTypeAttribValue.upper() == "BOOL":
            return ParameterType.PARAM_BOOL
        elif paramTypeAttribValue.upper() == "INTEGER":
            return ParameterType.PARAM_INT
        elif paramTypeAttribValue.upper() == "FLOAT":
            return ParameterType.PARAM_FLOAT
        else:
            return ParameterType.PARAM_UNKNOWN

class NodeParameterData:
    '''
    Represents a Parameter for a node
    '''

    def __init__(self):
        '''
        Initializes the node parameter object with default values
        '''
        self.ID = "Unkown"
        self.Name = "Unknown"
        self.Type = ParameterType.PARAM_UNKNOWN
        self.Size = 0
        self.MinValue = 0
        self.MaxValue = 0
        self.DefaultValue = 0

        self.Node = None
        self.GeneratorData = {}

class NodeData:
    '''
    Represents a Node in the network including a dictionary of all network interfaces of this node
    '''
    def __init__(self):
        '''
        Initializes the node data object with default values
        '''
        self.ID = "Unknown"
        self.Name = "Unknown"
        self.NodeController = "Default" # Microcontroller type used for the node
        self.Interfaces = {}
        self.Parameters = {}

        self.GeneratorData = {}

class NodeDataParser:
    '''
    The NodeDataParser needs a dictionary with the Network objects and also a dictionary of the Messages

    The Network objects are used to parse the "ConnectedTo" attribute which identifies the network to which a specific
    interface is connected.

    The message dictionary is used to get object references to the TX-Messages and RX-Messages of a specific
    network interface inside a node
    '''

    def __init__(self, networkDict, messageDict, nodeRoot):
        '''
        Initializes the node data parser with the provided network and message dictionary
        and also with the root element of the Nodes
        '''
        self._networkDict = networkDict
        self._messageDict = messageDict
        self._nodeRoot = nodeRoot

    def parse(self):
        '''
        Parses all <Node> elements under <Nodes> root element and returns a dictionary of all nodes
        '''
        nodeDict = {}

        # Iterate over the <Node> elements under <Nodes> root
        for nodeElement in self._nodeRoot:
            nodeData = NodeData()

            # Get the ID and the Name of the Node
            nodeData.ID = nodeElement.get("ID")
            nodeData.Name = nodeElement.get("Name")
            nodeData.NodeController = nodeElement.get("NodeController")

            # Find the <Interfaces> element inside the actual Node element
            interfacesRoot = nodeElement.find("Interfaces")

            # Iterate over the interfaces of the node
            for interfaceChild in interfacesRoot:
                # Check if the interface child element is a <Interface> element
                if interfaceChild.tag == "Interface":
                    nodeInterface = NodeInterfaceData()

                    # Get the Interface ID, Name and Network Controller
                    nodeInterface.ID = interfaceChild.get("ID")
                    nodeInterface.Name = interfaceChild.get("Name")
                    nodeInterface.NetworkController = interfaceChild.get("NetworkController")

                    try:
                        convertBase = 10
                        netID = interfaceChild.get("NetworkID")

                        if netID.startswith("0x") == True:
                            convertBase = 16

                        # Get the Network ID. This might be used (e.g. for CAN) to have an Node-ID for this interface
                        nodeInterface.NetworkID = int(netID, convertBase)
                    except:
                        nodeInterface.NetworkID = 0

                    # Parse the network type of the interface
                    nodeInterface.NetworkType = NetworkDataType.parseNetworkType(interfaceChild.get("Type"))
                    # Parse the bandwidth of the interface
                    nodeInterface.Bandwidth = NetworkDataBandwith.parseNetworkBandwidth(interfaceChild.get("Bandwidth"))

                    try:
                        # Try to find the corresponding Network object in the network dictionary to which this
                        # interface is connected to.
                        networkObj = self._networkDict[interfaceChild.get("ConnectedTo")]

                        # If the network was found, store a reference to the Network object
                        if networkObj != None:
                            nodeInterface.ConnectTo = networkObj
                    except:
                        print("Error while parsing Node " + nodeInterface.ID)

                    # Find the elements for <RxMessages> and <TxMessages>
                    rxMessageRoot = interfaceChild.find("RxMessages")
                    txMessageRoot = interfaceChild.find("TxMessages")

                    # If the <RxMessages> element was found
                    if rxMessageRoot != None:
                        # Iterate over all <RxMessage> elements
                        for rxMessageChild in rxMessageRoot:
                            # Check if it is the correct element
                            if rxMessageChild.tag == "RxMessage":
                                nodeRxMessage = NodeInterfaceMessage()

                                try:
                                    # Try to find the referenced message via its ID in the message dictionary
                                    nodeRxMessage.Message = self._messageDict[rxMessageChild.get("RefID")]
                                    nodeRxMessage.Node = nodeData

                                    # Add the message container object with the reference to the message object to the Rx
                                    # messages dictionary
                                    nodeInterface.RxMessages[nodeRxMessage.Message.ID] = nodeRxMessage
                                except:
                                    print("Error while parsing RxMessage for Interface " + nodeInterface.ID)

                    # If the <TxMessages> element was found
                    if txMessageRoot != None:
                        # Iterate over all <TxMessage> elements
                        for txMessageChild in txMessageRoot:
                            # Check if it is the correct element
                            if txMessageChild.tag == "TxMessage":
                                nodeTxMessage = NodeInterfaceMessage()

                                try:
                                    # Try to find the referenced message via its ID in the message dictionary
                                    nodeTxMessage.Message = self._messageDict[txMessageChild.get("RefID")]
                                    nodeTxMessage.Node = nodeData

                                    # Add the message container object with the reference to the message object to the Rx
                                    # messages dictionary
                                    nodeInterface.TxMessages[nodeTxMessage.Message.ID] = nodeTxMessage
                                except:
                                    print("Error while parsing TxMessage for Interface " + nodeInterface.ID)

                    # Add the interface to the dictionary of the node interfaces
                    # Finished <Interface> element
                    nodeData.Interfaces[nodeInterface.ID] = nodeInterface

            # Find the <Parameters> element inside the actual Node element
            parametersRoot = nodeElement.find("Parameters")

            if parametersRoot is None:
                parametersRoot = []

            # Iterate over the parameters of the node
            for parameterChild in parametersRoot:
                # Check if the parameter child element is a <Parameter> element
                if parameterChild.tag == "Parameter":
                    parameterData = NodeParameterData()

                    # Get the Interface ID, Name and Network Controller
                    parameterData.ID = parameterChild.get("ID")
                    parameterData.Name = parameterChild.get("Name")
                    parameterData.Type = ParameterType.parseSignalType(parameterChild.get("Type"))

                    try:
                        size = int(parameterChild.get("Size"))

                        if size is None:
                            size = 8
                    except:
                        size = 8

                    parameterData.Size = size

                    try:
                        minValue = parameterChild.get("MinValue")
                        maxValue = parameterChild.get("MaxValue")
                        defaultValue = parameterChild.get("DefaultValue")

                        parameterData.MinValue = int(minValue)
                        parameterData.MaxValue = int(maxValue)
                        parameterData.DefaultValue = int(defaultValue)
                    except:
                        defaultLog("Parameter {0} has invalud min/max/default value".format(parameterData.ID))
                        parameterData.MinValue = 0
                        parameterData.MaxValue = 0
                        parameterData.DefaultValue = 0

                    parameterData.Node = nodeData
                    nodeData.Parameters[parameterData.ID] = parameterData

            # Add the node object to the dictionary of the nodes
            # Finished <Node> element
            nodeDict[nodeData.ID] = nodeData

        return nodeDict