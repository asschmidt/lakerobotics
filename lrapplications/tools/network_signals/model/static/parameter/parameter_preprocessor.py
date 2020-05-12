
from model.additional_model_data import MessageGeneratorData, ParameterGeneratorData

'''
'''
class ParameterPreprocessor:
    '''
    Class which represents a Parameter preprocessor object to pre-process
    Parameters
    '''

    def __init__(self, networkBuilder):
        '''
        Initializes the Parameter preprocessor with the provided networkBuilder object
        '''
        self._networkBuilder = networkBuilder

    def _calculateParameterIDs(self):
        '''
        Calculates the Parameter IDs for all Parameters based on a sequential numbering scheme
        '''
        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node != None:
                actualParamNumber = 1

                # Iterate over all Tx Messages of a Interface
                for parameter in node.Parameters.values():
                    parameter.GeneratorData[ParameterGeneratorData.PARAM_ID] = actualParamNumber
                    actualParamNumber = actualParamNumber + 1


    def _buildParameterList(self):
        '''
        Returns a list of all Parameters
        '''
        parameterList = []

        # Iterate over all Nodes
        for node in self._networkBuilder.getNodeList():
            if node != None:
                # Iterate over all Parameters of a node
                for parameter in node.Parameters.values():
                    # Add it to the list
                    parameterList.append(parameter)

        return parameterList


    def _printParameterList(self, parameterList):
        '''
        Helper method to print all Parameters on the console. The list of parameters is
        provided with the parameterList argument
        '''
        print("Parameters")
        print("==================================")
        for param in parameterList:
            paramString = "Parameter {0:36} from Node {1:20} with Parameter-ID: {2:5}".format(param.ID, param.Node.ID, param.GeneratorData[ParameterGeneratorData.PARAM_ID])
            print(paramString)

        print("")

    def prepareParameterDatabase(self):
        '''
        Calculates the Parameters IDs and prints the list of parameter
        '''
        # Calculate the Parameter IDs
        self._calculateParameterIDs()

        paramList = self._buildParameterList()
        self._printParameterList(paramList)