'''
Created on 16.05.2019

@author: Andreas
'''

from model.networks import *
from model.nodes import *
from model.messages import *
from model.signals import *

class NetworkBuilder:
    '''
    '''

    def __init__(self, networkVersion, networkDict, nodeDict, messageDict, signalDict):
        '''
        '''
        self._networkVersion = networkVersion
        self._networkDict = networkDict
        self._nodeDict = nodeDict
        self._messageDict = messageDict
        self._signalDict = signalDict

    def getNode(self, nodeID):
        '''
        '''
        try:
            return self._nodeDict[nodeID]
        except:
            return None

    def getNodes(self):
        '''
        '''
        return self._nodeDict.values()

    def getNetworkVersion(self):
        '''
        '''
        return self._networkVersion

    def getMessages(self):
        '''
        '''
        return self._messageDict

    def getSignals(self):
        '''
        '''
        return self._signalDict