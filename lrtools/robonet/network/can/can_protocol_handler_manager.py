
from util.logger import LoggerEntryType
from util.logger_global import defaultLog

class CANProtocolHandlerManager:
    '''
    Class to handle multiple CAN protocol handler
    '''

    def __init__(self, networkBuilder):
        '''
        Initializes a CAN Protocol Handler object
        '''
        self._networkBuilder = networkBuilder
        self._protocolHandler = []

    def registerProtocolHandler(self, protocolHandler):
        '''
        Registers a protocol handler object in the internal protocol
        handler list
        '''
        defaultLog("Registering Protocol-Handler: " + str(protocolHandler))
        self._protocolHandler.append(protocolHandler)

    def unregisterProtocolHandler(self, protocolHandler):
        '''
        Removes a protocol handler object from the internal protocol
        handler list
        '''
        self._protocolHandler.remove(protocolHandler)

    def handleCANMessage(self, canConnector, canMessage):
        '''
        Handler function which is called by the CAN Data Connector object
        if a CAN Message is received. Inside this handler function, the
        CAN Protocol Handler Manager search for a CAN Handler object in the internal
        list which can handle the CAN message
        '''
        messageHandled = False

        for handler in self._protocolHandler:
            # Check if the handler object is responsible for the CAN Message
            shouldHandle = handler.shouldHandleCANMessage(canConnector, canMessage)
            if shouldHandle == True:
                # If yes, handle the message and exit the loop
                handler.handleCANMessage(canConnector, canMessage)
                messageHandled = True
                break

        if messageHandled == False:
            # Print some log information that there was no handler
            #defaultLog("No CAN Protocol Handler for Message {0}".format(hex(canMessage.mid)))
            pass