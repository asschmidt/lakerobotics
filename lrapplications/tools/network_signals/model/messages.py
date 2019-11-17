
from model.networks import NetworkDataType
from model.signals import SignalData

'''
Class to hold a signal reference inside a message
'''
class MessageSignalRef:
    def __init__(self):
        self.Signal = None
        self.Position = 0

'''
Class to represent a message including an array with all the signal references
'''
class MessageData:
    '''
    '''
    def __init__(self):
        self.ID = "Unknown"
        self.Name = "Unknown"
        self.NetworkType = NetworkDataType.UNKNOWN
        self.Signals = []

        self.GeneratorData = {}

    '''
    '''
    def getGeneratorData(self, dataKey):
        genData = None

        try:
            genData = self.GeneratorData[dataKey]
        except:
            pass

        return genData

    '''
    '''
    def findSignalReferenceByID(self, signalID):
        for signalRef in self.Signals:
            if signalRef.Signal.ID == signalID:
                return signalRef

        return None
        
'''
Class representing the XML parser to parse message elements from a XML document
The parser needs the messages root element "<Messages>" as input
'''
class MessageDataParser:
    '''
    '''
    def __init__(self, networkDict, signalDict, messagesRoot):
        self._networkDict = networkDict
        self._signalDict = signalDict
        
        self._messagesRoot = messagesRoot
    
    '''
    Parse all <Message> elements under <Messages> root and returns a dictionary with all message
    objects
    ''' 
    def parse(self):
        messageDict = {}
        
        # Iterate over the message elements of the <Messages> root element
        for messageElement in self._messagesRoot:
            message = MessageData()
        
            # Get the ID and the name of the message
            message.ID = messageElement.get("ID")
            message.Name = messageElement.get("Name")
            
            # Find the <Signals> child element inside the message element 
            signalsRoot = messageElement.find("Signals")
            
            # Iterate over all signal references inside the message
            for signalChild in signalsRoot:
                if signalChild.tag == "Signal":
                                        
                    # Get the signal reference ID
                    signalRefID = signalChild.get("RefID")
                    # Get the position of the signal inside the message
                    signalPosition = signalChild.get("Position")
                    
                    try:
                        # Create the signal reference object
                        signalRef = MessageSignalRef()
                        # Assign the position
                        signalRef.Position = int(signalPosition)
                        # Find the signal in the signal dictionary. If the signal is not found
                        # an error message is printed
                        signalRef.Signal = self._signalDict[signalRefID]
                        
                        # Add the signal to the signal list of the message
                        message.Signals.append(signalRef)
                    except:
                        print("Error while parsing Signal " + signalRefID)
            
            # Sort the signals according their position
            message.Signals.sort(key = MessageDataParser.__sortSignalPosition)
            # Add the message to the dictionary
            messageDict[message.ID] = message
            
        return messageDict  
        
    '''
    Helper method to sort the signal array according the signal position
    '''
    @classmethod
    def __sortSignalPosition(self, signalObject):      
        return signalObject.Position