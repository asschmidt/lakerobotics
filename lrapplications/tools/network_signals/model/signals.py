
'''
Defines the data types of a signal
'''
class SignalType:
    SIGNAL_UNKNOWN  = 0 # Unknown signal data type
    SIGNAL_BOOL     = 1 # Boolean data type - True/False
    SIGNAL_INT      = 2 # Integer data type
    SIGNAL_FLOAT    = 3 # Floating data type

    '''
    Parses the signal type attribute string and returns a corresponding signal type
    '''
    @classmethod
    def parseSignalType(self, signalTypeAttribValue):
        if signalTypeAttribValue.upper() == "BOOL":
            return SignalType.SIGNAL_BOOL
        elif signalTypeAttribValue.upper() == "INTEGER":
            return SignalType.SIGNAL_INT
        elif signalTypeAttribValue.upper() == "FLOAT":
            return SignalType.SIGNAL_FLOAT
        else:
            return SignalType.SIGNAL_UNKNOWN

'''
Defines the endianess of a signal
'''
class SignalEndianess:
    ENDIAN_UNKNOWN  = 0 # Unknown endianess
    ENDIAN_LITTLE   = 1 # Little Endian LSB first
    ENDIAN_BIG      = 2 # Big Endian MSB first

    '''
    Parses the signal endianess attribute string and returns a corresponding signal endianess
    '''
    @classmethod
    def parseSignalEndianess(self, signalEndianessAttribValue):
        if signalEndianessAttribValue.upper() == "LITTLE":
            return SignalEndianess.ENDIAN_LITTLE
        elif signalEndianessAttribValue.upper() == "BIG":
            return SignalEndianess.ENDIAN_BIG
        else:
            return SignalEndianess.ENDIAN_UNKNOWN

'''
Class representing a signal
'''
class SignalData:
    def __init__(self):
        self.ID = "Undefined"
        self.Name = "Unknown"
        self.Size = 0
        self.Type = SignalType.SIGNAL_UNKNOWN
        self.Endianess = SignalEndianess.ENDIAN_UNKNOWN
        self.PhysicalUnit = "Unknown"

    def __repr__(self):
        return "Signal: " + self.ID

'''
Class for parsing the <Signal> elements under the root of the <Signals>
'''
class SignalDataParser:
    '''
    '''
    def __init__(self, signalsRoot):
        self._signalsRoot = signalsRoot

    '''
    Parse the <Signal> elements under the root of <Signals> and returns a dictionary with
    all Signal objects
    '''
    def parse(self):
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