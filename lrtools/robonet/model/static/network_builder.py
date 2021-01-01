

class NetworkBuilder:
    '''
    Class which representes the whole network including all entities like
    nodes, messages and signals.
    '''

    def __init__(self, networkVersion, networkDict, nodeDict, messageDict, signalDict):
        '''
        Initializes the object with the provided object of networks, nodes, messages and
        signals
        '''
        self._networkVersion = networkVersion
        self._networkDict = networkDict
        self._nodeDict = nodeDict
        self._messageDict = messageDict
        self._signalDict = signalDict

    def getNode(self, nodeID):
        '''
        Returns the node object with the provided node ID. If the node was not found,
        None is returned
        '''
        try:
            return self._nodeDict[nodeID]
        except:
            return None

    def getNodeList(self):
        '''
        Returns the list of all nodes
        '''
        return self._nodeDict.values()

    def getNetworkVersion(self):
        '''
        Returns the network version
        '''
        return self._networkVersion

    def getNodes(self):
        '''
        Returns the nodes dictionary. The node ID is used as the key for the
        dictionary
        '''
        return self._nodeDict

    def getMessages(self):
        '''
        Returns the dictionary of all messages. The message ID is the key for the
        dictionary
        '''
        return self._messageDict

    def getSignals(self):
        '''
        Returns the dictionary of all signals. The signal ID is the key for the
        dictionary
        '''
        return self._signalDict