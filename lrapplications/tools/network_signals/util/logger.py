import time
import datetime
import threading

class LoggerEntryType:
    LOG_INFO        = 0x01
    LOG_ERROR       = 0x02
    LOG_DEBUG       = 0x04
    LOG_ACTIVITY    = 0x08

class LoggerEntry:
    '''
    '''

    def __init__(self, msg = "No Message", logType = LoggerEntryType.LOG_INFO):
        '''
        '''
        self.LogTime = datetime.datetime.now()
        self.LogMsg = msg
        self.LogType = logType

    def _logTypeToString(self, logType):
        '''
        '''
        switcher = {
            LoggerEntryType.LOG_ACTIVITY : 'ACTIVITY',
            LoggerEntryType.LOG_DEBUG: 'DEBUG',
            LoggerEntryType.LOG_ERROR: 'ERROR',
            LoggerEntryType.LOG_INFO: 'INFO'
        }

        return switcher.get(logType, 'UNKNOWN')

    def _returnString(self):
        '''
        '''
        logTypeStr = self._logTypeToString(self.LogType)

        return "[{0:%Y-%m-%d %H:%M:%S.%f}] - {1} - {2}".format(self.LogTime, logTypeStr, self.LogMsg)

    def __repr__(self):
        '''
        '''
        return self._returnString()

    def __str__(self):
        '''
        '''
        return self._returnString()

    def __add__(self, other):
        '''
        '''
        return str(self) + other

    def __radd__(self, other):
        '''
        '''
        return other + str(self)

class LoggerBackend(object):
    '''
    '''

    def __init__(self):
        '''
        '''
        self._lock = threading.Lock()
        self._logLines = []

    def log(self, logMsg, logType = LoggerEntryType.LOG_INFO):
        '''
        '''
        logEntry = LoggerEntry(logMsg, logType)
        self._lock.acquire()
        self._logLines.append(logEntry)
        self._lock.release()

    def getLogLine(self, logLineIdx):
        '''
        '''
        logLine = "INVALID"

        if logLineIdx >= 0 and logLineIdx < len(self._logLines):
            self._lock.acquire()
            logLine = self._logLines[logLineIdx]
            self._lock.release()

        return logLine

    def getLastLogLine(self):
        '''
        '''
        logLine = "INVALID"
        self._lock.acquire()
        logLine = self._logLines[len(self._logLines) - 1]
        self._lock.release()

        return logLine

    def getLogLineCount(self):
        '''
        '''
        count = len(self._logLines)
        return count


class LoggerConsoleOutputThread(threading.Thread):

    def __init__(self, backend):
        '''
        '''
        threading.Thread.__init__(self)
        self._backend = backend
        self._currentLogLineIdx = 0

        self._wantAbort = False

    def stop(self):
        '''
        '''
        self._wantAbort = True

    def run(self):
        '''
        '''
        while self._wantAbort != True:
            logLineCount = self._backend.getLogLineCount()
            if logLineCount > self._currentLogLineIdx:
                logLine = self._backend.getLogLine(self._currentLogLineIdx)
                self._currentLogLineIdx = self._currentLogLineIdx + 1

                print("Console Logger: " + logLine)

            time.sleep(0.1)

class LoggerProducerThread(threading.Thread):

    def __init__(self, backend):
        '''
        '''
        threading.Thread.__init__(self)
        self._backend = backend
        self._wantAbort = False

    def stop(self):
        '''
        '''
        self._wantAbort = True

    def run(self):
        '''
        '''
        produced = 1

        while self._wantAbort != True:
            self._backend.log("Some Message [{0}] From Producer".format(produced), LoggerEntryType.LOG_ACTIVITY)
            produced = produced + 1
            time.sleep(0.01)


def testLogger():
    myLogger = LoggerBackend()

    logEntry = LoggerEntry()
    logEntry.LogMsg = "My First Message"
    logEntry.LogType = LoggerEntryType.LOG_DEBUG

    print("Log Entry: " + logEntry)

    logOutputThread = LoggerConsoleOutputThread(myLogger)
    logProducerThread = LoggerProducerThread(myLogger)

    logOutputThread.start()
    logProducerThread.start()

    time.sleep(2)

    logOutputThread.stop()
    logProducerThread.stop()

    logOutputThread.join()
    logProducerThread.join()

    print("Finished")

if __name__ == "__main__":
    testLogger()