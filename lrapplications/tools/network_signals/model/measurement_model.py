'''
Created on 05.11.2019

@author: Andreas
'''

'''
'''
class MeasurementSignalDataDirection:
    RX = 1
    TX = 2


'''
'''
class MeasurementData:
    '''
    '''
    def __init__(self):
        self.Name = "Unknown"
        self.Signals = {}

'''
'''
class MeasurementSignalData:

    '''
    '''
    def __init__(self):
        self.SignalID = "Unkown"
        self.SignalRef = None
        self.Direction = MeasurementSignalDataDirection.RX

'''
'''
class MeasurementDataParser:
    '''
    '''
    def __init__(self, measurementRoot, networkBuilder):
        self._measurementRoot = measurementRoot
        self._networkBuilder = networkBuilder

    def parse(self):
        measurementDict = {}

        # Iterate over all <Measurement> elements under the root <MeasurementDefinitions>
        for measurementElement in self._measurementRoot:
            measurementObj = MeasurementData()
            measurementObj.Name = measurementElement.get("Name")

            signalsElement = measurementElement.find("Signals")
            signalParser = MeasurementSignalDataParser(signalsElement, self._networkBuilder.getSignals())
            signalDict = signalParser.parse()

            measurementObj.Signals = signalDict

            measurementDict[measurementObj.Name] = measurementObj


        return measurementDict

'''
Class for parsing the <Signal> elements under the root of the <Measurement>
'''
class MeasurementSignalDataParser:
    '''
    '''
    def __init__(self, signalsRoot, signalsDict):
        self._signalsRoot = signalsRoot
        self._signalsRefDict = signalsDict

    '''
    Parse the <Signal> elements under the root of <Measurement> and returns a dictionary with
    all Signal objects
    '''
    def parse(self):
        signalDict = {}

        # Iterate over all <Signal> elemens under the root <Measurement>
        for signalElement in self._signalsRoot:
            signal = MeasurementSignalData()

            # Get the ID of the signal
            signal.SignalID = signalElement.get("RefID")

            try:
                signalObj = self._signalsRefDict[signal.SignalID]
                signal.SignalRef = signalObj
            except:
                print("Signal " + signal.SignalID + " not found in the dictionary")

            # Get the signal direction
            signalDirectionStr = signalElement.get("Direction")
            if signalDirectionStr == "Rx":
                signal.Direcion = MeasurementSignalDataDirection.RX
            elif signalDirectionStr == "Tx":
                signal.Direction = MeasurementSignalDataDirection.TX
            else:
                signal.Direction = MeasurementSignalDataDirection.RX

            # Add the signal to the dictionary with the Signal ID as key
            signalDict[signal.SignalID] = signal

        return signalDict