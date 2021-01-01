from util.logger import LoggerEntryType, LoggerBackend, LoggerEntry, LoggerConsoleOutputThread

import util.logger_global_obj as logger_global_obj

def initializeDefaultLogger(consoleOutput = False):
    '''
    Initializes the global default logger instance including a default console
    output thread if the supplied consoleOutput parameter is set to True
    '''
    logger_global_obj.defaultLogger = LoggerBackend()
    if consoleOutput == True:
        logger_global_obj.defaultOutputThread = LoggerConsoleOutputThread(logger_global_obj.defaultLogger)
        logger_global_obj.defaultOutputThread.start()

def finalizeDefaultLogger():
    '''
    Stops the console output thread if it was created and waits till the thread stopped 
    '''
    if logger_global_obj.defaultOutputThread is not None:
        logger_global_obj.defaultOutputThread.stop()
        logger_global_obj.defaultOutputThread.join()

def defaultLog(logMsg, logType = LoggerEntryType.LOG_INFO):
    '''
    Adds a log entry into the default logger backend
    '''
    if logger_global_obj.defaultLogger is not None:
        logger_global_obj.defaultLogger.log(logMsg, logType)