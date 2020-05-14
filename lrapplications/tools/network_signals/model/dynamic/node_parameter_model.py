

class NodeParameterModelState:
    '''
    Class which provides constants for a state of a parameter model data
    '''
    VALUE_STATUS_UNKNOWN    = 0x01
    VALUE_REQUESTED         = 0x02
    VALUE_RECEIVED          = 0x04

class NodeParameterModelData:
    '''
    Class which hold the dynamic data of one parameter for a node and also
    a reference to the parameter definition
    '''

    def __init__(self, node, parameterDef):
        '''
        Initializes the NodeParameterModelData object
        '''
        self._node = node
        self._parameterDef = parameterDef
        self._actualValue = None
        self._locallyChanged = False
        self._status = NodeParameterModelState.VALUE_STATUS_UNKNOWN

    def getNode(self):
        '''
        Returns the associated node objects
        '''
        return self._node

    def getParameterDefinition(self):
        '''
        Returns the parameter definition object
        '''
        return self._parameterDef

    def getValueStatus(self):
        '''
        Returns the value status of the parameter
        '''
        return self._status

    def setValueStatus(self, status):
        '''
        Sets the value status of the parameter
        '''
        self._status = status

    def getDefaultValue(self):
        '''
        Returns the default value of the parameter
        '''
        if self._parameterDef is not None:
            return self._parameterDef.DefaultValue
        else:
            return None

    def getParameterUnit(self):
        '''
        Returns the unit string of the paramter
        '''
        if self._parameterDef is not None:
            return self._parameterDef.Unit
        else:
            return "Unknown Unit"

    def getActualValue(self):
        '''
        Returns the actual value of the parameter
        '''
        return self._actualValue

    def setActualValue(self, value):
        '''
        Sets the actual value and if the value if different from the current
        value of "actualValue", it also sets the locallyChanged flag
        '''
        self._locallyChanged = self._actualValue != value
        self._actualValue = value

    def hasLocallyChanged(self):
        '''
        Returns True if the parameter has changed but was not transferred to
        the node
        '''
        return self._locallyChanged


class NodeParameterDynamicModel:
    '''
    Class which holds a dynamic model of the parameter of a node
    '''

    def __init__(self):
        '''
        Initializes the dynamic parameter model object
        '''
        self._nodeParameterMap = {}
        self._subscriber = []

    def registerSubscriber(self, sub):
        '''
        Registers a subscriber object in the internal subscriber list
        '''
        self._subscriber.append(sub)

    def unregisterSubscriber(self, sub):
        '''
        Unregisters a subscriber object from the internal subscriber list
        '''
        self._subscriber.remove(sub)

    def notifySubscriber(self, dataEntry):
        '''
        Iterates through the list of all registered subscribers and calls their
        notify() method with the data entry as argument
        '''
        for sub in self._subscriber:
            if sub != None:
                sub.notify(dataEntry)

    def addParameterModelEntry(self, nodeNetworkID, paramModelData):
        '''
        Adds the provided parameter Model data to the internal dictionary
        for the provided node network ID
        '''
        if nodeNetworkID in self._nodeParameterMap:
            parameterDict = self._nodeParameterMap[nodeNetworkID]
        else:
            parameterDict = {}

        # Add the parameter to the parameter dictionary of the node
        parameterDict[paramModelData.getParameterDefinition().ID] = paramModelData
        self._nodeParameterMap[nodeNetworkID] = parameterDict

    def getParameterIDForParameterNo(self, nodeNetworkID, paramNo):
        '''
        Returns the parameter ID for the specific parameter number
        '''
        for param in self.getParameterListForNode(nodeNetworkID):
            paramDef = param.getParameterDefinition()
            if paramDef.GeneratorData['PARAM_NO'] == paramNo:
                return paramDef.ID

        return None

    def getParameterModelEntry(self, nodeNetworkID, paramID):
        '''
        Returns the parameter model entry object for the provided networkID and param ID
        '''
        if nodeNetworkID in self._nodeParameterMap:
            try:
                return self._nodeParameterMap[nodeNetworkID][paramID]
            except:
                return None
        else:
            return None

    def getNodeNetworkIDList(self):
        '''
        Returns a list of all node network IDs in the parameter model
        '''
        return self._nodeParameterMap.keys()

    def hasNodeNetworkID(self, nodeNetworkID):
        '''
        Returns true if the provided node network ID is in the internal list
        '''
        return (nodeNetworkID in self._nodeParameterMap)

    def getParameterListForNode(self, nodeNetworkID):
        '''
        Returns the list of parameter for the provided node network ID. If the node network
        ID is not found, None is returned
        '''
        if nodeNetworkID in self._nodeParameterMap:
            return self._nodeParameterMap[nodeNetworkID].values()
        else:
            return None

    def setParameterActualValue(self, nodeNetworkID, parameterNo, actualValue):
        '''
        Sets the parameters actual value for the provided node network ID and the
        parameter number
        '''
        parameterID = self.getParameterIDForParameterNo(nodeNetworkID, parameterNo)
        paramModelEntry = self.getParameterModelEntry(nodeNetworkID, parameterID)
        if paramModelEntry is not None:
            paramModelEntry.setActualValue(actualValue)
            self.notifySubscriber(paramModelEntry)