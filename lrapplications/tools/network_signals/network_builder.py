'''
Created on 16.05.2019

@author: Andreas
'''

from networks import *
from nodes import *
from messages import *
from signals import *

'''
'''
class NetworkBuilder:
    '''
    '''
    def __init__(self, networkDict, nodeDict, messageDict, signalDict):
        self._networkDict = networkDict
        self._nodeDict = nodeDict
        self._messageDict = messageDict
        self._signalDict = signalDict
        
    '''
    '''
    def getNode(self, nodeID):
        try:
            return self._nodeDict[nodeID]
        except:
            return None
    
    '''
    '''
    def getNodes(self):
        return self._nodeDict.values()