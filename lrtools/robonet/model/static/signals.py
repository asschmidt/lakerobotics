
class SignalType:
    '''
    Defines the data types of a signal
    '''
    SIGNAL_UNKNOWN  = 0 # Unknown signal data type
    SIGNAL_BOOL     = 1 # Boolean data type - True/False
    SIGNAL_INT      = 2 # Integer data type
    SIGNAL_FLOAT    = 3 # Floating data type

    @classmethod
    def parseSignalType(cls, signalTypeAttribValue):
        '''
        Parses the signal type attribute string and returns a corresponding signal type
        '''
        if signalTypeAttribValue.upper() == "BOOL":
            return SignalType.SIGNAL_BOOL
        elif signalTypeAttribValue.upper() == "INTEGER":
            return SignalType.SIGNAL_INT
        elif signalTypeAttribValue.upper() == "FLOAT":
            return SignalType.SIGNAL_FLOAT
        else:
            return SignalType.SIGNAL_UNKNOWN

class SignalEndianess:
    '''
    Defines the endianess of a signal
    '''
    ENDIAN_UNKNOWN  = 0 # Unknown endianess
    ENDIAN_LITTLE   = 1 # Little Endian LSB first
    ENDIAN_BIG      = 2 # Big Endian MSB first

    @classmethod
    def parseSignalEndianess(cls, signalEndianessAttribValue):
        '''
        Parses the signal endianess attribute string and returns a corresponding signal endianess
        '''
        if signalEndianessAttribValue.upper() == "LITTLE":
            return SignalEndianess.ENDIAN_LITTLE
        elif signalEndianessAttribValue.upper() == "BIG":
            return SignalEndianess.ENDIAN_BIG
        else:
            return SignalEndianess.ENDIAN_UNKNOWN

class SignalData:
    '''
    Class representing a signal
    '''

    def __init__(self):
        '''
        Initializes the signal data object with default values
        '''
        self.ID = "Undefined"
        self.Name = "Unknown"
        self.Size = 0
        self.Type = SignalType.SIGNAL_UNKNOWN
        self.Endianess = SignalEndianess.ENDIAN_UNKNOWN
        self.PhysicalUnit = "Unknown"

        self.GeneratorData = {}

    def __repr__(self):
        '''
        Returns the string representation of the signal data object
        '''
        return "Signal: " + self.ID

class SignalDataParser:
    '''
    Class for parsing the <Signal> elements under the root of the <Signals>
    '''

    def __init__(self, signalsRoot):
        '''
        Initializes the signal data parser with the provided signals root element
        '''
        self._signalsRoot = signalsRoot

    def parse(self):
        '''
        Parse the <Signal> elements under the root of <Signals> and returns a dictionary with
        all Signal objects
        '''
        signalDict = {}

        # Iterate over all <Signal> elemens under the root <Signals>
        for signalElement in self._signalsRoot:
            signal = SignalData()

            # Get the ID, Name and the name of the physical unit
            signal.ID = signalElement.get("ID")
            signal.Name = signalElement.get("Name")
            signal.PhysicalUnit = signalElement.get("PhysicalUnit")

            # Get the size of the signal in bit
            try:
                signal.Size = int(signalElement.get("Size"))
            except:
                signal.Size = 0

            # Parse the signal endianess
            signal.Endianess = SignalEndianess.parseSignalEndianess(signalElement.get("Endian"))
            # Parse the signal data type
            signal.Type = SignalType.parseSignalType(signalElement.get("Type"))

            # Add the signal to the dictionary with the Signal ID as key
            signalDict[signal.ID] = signal

        return signalDict