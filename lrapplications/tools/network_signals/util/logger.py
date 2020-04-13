

class LoggerEntryType:
    LOG_INFO = 0x01
    LOG_ERROR = 0x02
    LOG_DEBUG = 0x04
    LOG_ACTIVITY = 0x08

class LoggerEntry:
    '''
    '''

    def __init__(self, msg, logType):
        '''
        '''
        self.LogTime = None
        self.LogMsg = msg
        self.LogType = logType

    def __init__(self):
        '''
        '''
        self.__init__("No Message", LoggerEntryType.LOG_INFO)

class LoggerBackend(object):
    '''
    '''

    def __init__(self):
        '''
        '''
        self._logLines = []

    def log(self, logMsg, logType = LoggerEntryType.LOG_INFO):
        pass