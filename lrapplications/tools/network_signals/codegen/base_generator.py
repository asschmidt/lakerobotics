'''
Created on 16.05.2019

@author: Andreas
'''

'''
Base class for a Message Generator. This generator includes methods to generate
C-Structures and access function out of messages
'''
class BaseMessageGenerator:
    '''
    '''
    def __init__(self, networkBuilder):
        self._networkBuilder = networkBuilder
        
    '''
    '''
    def generateCANMessageCode(self, nodeBlockSize):
        raise NotImplementedError
    
    '''
    '''
    def generateMessageStruct(self):
        raise NotImplementedError