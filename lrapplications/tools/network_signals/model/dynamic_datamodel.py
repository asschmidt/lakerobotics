'''
Created on 05.11.2019

@author: Andreas
'''

import datetime

'''
Represents an entry in the dynamic data model.
This includes a reference to a kind of data definition description which defines how the data format is defined 
(used to extract the data from the raw data). Additionally a couple of timing values will be stored to have some
values about "last data change" and the time difference between two data changes
'''
class DataModelEntry:
    '''
    '''
    def __init__(self, dataID, dataDefRef = None):
        self._dataID = dataID
        self._dataDefRef = dataDefRef   # Reference to a data definition (e.g. CAN signal definition)

        self._data = None               # Actual data value (can be of different type like int, float etc)
        self._prevData = None           # Previous data
        self._dataChangedTimeStamp = 0  # Timestamp of last data change
        self._dataChangedTimeDelta = 0  # Delta value of milliseconds since last data change

        self._funcExtractData = None    # Function pointer to an extract function for extracting the data out of the raw object

    '''
    '''
    def getDataID(self):
        return self._dataID

    '''
    '''
    def getDataDefRef(self):
        return self._dataDefRef

    '''
    '''
    def setDataDefRef(self, dataDefRef):
        self._dataDefRef = dataDefRef

    '''
    '''
    def getData(self):        
        return self._data

    '''
    '''
    def getPreviousData(self):
        return self._prevData

    '''
    '''
    def setData(self, data):
        # timestamp calculation for this data entry
        newTime = datetime.datetime.now()
        if self._dataChangedTimeStamp != 0:
            self._dataChangedTimeDelta = newTime - self._dataChangedTimeStamp
        self._dataChangedTimeStamp = newTime
        
        # If there is an extract function available, use that to extract the data
        self._prevData = self._data
        if self._funcExtractData != None:
            self._data = self._funcExtractData(self._dataDefRef, data)
        else:
            self._data = data

        # Check if the data has changed (we can use this to send notifications for changed data)
        newData = False
        if self._prevData != self._data:
            newData = True
        
        return newData

    '''
    '''
    def setExtractFunction(self, func):
        self._funcExtractData = func


'''
Represents a dictionary including data entries as a combination of data, raw-data and data definition. The key
for the data entries is a unique data ID
'''
class DynamicDataModel:
    '''
    '''
    def __init__(self):
        self._dataDict = {}
        self._subscriber = []

    '''
    '''
    def addDataModelEntry(self, dataModelEntry):
        insertResult = False

        try:
            self._dataDict[dataModelEntry.getDataID()] = dataModelEntry
            insertResult = True
        except:
            pass

        return insertResult

    '''
    '''
    def getDataModelEntry(self, dataID):
        try:
            return self._dataDict[dataID]
        except:
            return None

    '''
    '''
    def updateDataModelEntry(self, dataID, data):
        updateResult = False
        dataEntry = self.getDataModelEntry(dataID)

        if dataEntry != None:
            dataChanged = dataEntry.setData(data)            
            if dataChanged == True:
                self.notifySubscriber(dataEntry)

            updateResult = True

        return updateResult

    '''
    '''
    def getDataModelEntryIterator(self):
        for entry in self._dataDict.values():
            yield entry

    '''
    '''
    def registerSubscriber(self, sub):
        self._subscriber.append(sub)

    '''
    '''
    def unregisterSubscriber(self, sub):
        self._subscriber.remove(sub)

    '''
    '''
    def notifySubscriber(self, dataEntry):
        for sub in self._subscriber:
            if sub != None:
                sub.notify(dataEntry)
    