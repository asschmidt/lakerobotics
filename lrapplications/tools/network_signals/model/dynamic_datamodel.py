'''
Classes for dynamic data model handling

@author: Andreas
'''

import datetime

class DataModelEntry:
    '''
    Represents an entry in the dynamic data model.

    This includes a reference to a kind of data definition description which defines how the data format is defined
    (used to extract the data from the raw data). Additionally a couple of timing values will be stored to have some
    values about "last data change" and the time difference between two data changes
    '''

    def __init__(self, dataID, dataDefRef = None):
        '''
        '''
        self._dataID = dataID
        self._dataDefRef = dataDefRef   # Reference to a data definition (e.g. CAN signal definition)

        self._data = None               # Actual data value (can be of different type like int, float etc)
        self._prevData = None           # Previous data
        self._dataChangedTimeStamp = 0  # Timestamp of last data change
        self._dataChangedTimeDelta = 0  # Delta value of milliseconds since last data change

        self._funcExtractData = None    # Function pointer to an extract function for extracting the data out of the raw object

    def getDataID(self):
        '''
        '''
        return self._dataID

    def getDataDefRef(self):
        '''
        '''
        return self._dataDefRef

    def setDataDefRef(self, dataDefRef):
        '''
        '''
        self._dataDefRef = dataDefRef

    def getData(self):
        '''
        '''
        return self._data

    def getPreviousData(self):
        '''
        '''
        return self._prevData

    def setData(self, data):
        '''
        '''
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

    def setExtractFunction(self, func):
        '''
        '''
        self._funcExtractData = func


class DynamicDataModel:
    '''
    Represents a dictionary including data entries as a combination of data, raw-data and data definition.

    The key for the data entries is a unique data ID
    '''

    def __init__(self):
        '''
        Initializes the instance for the dynamic data model.

        This includes the creation of empty data dictionaries for the data incl. data definition and also a
        list of registered subscribers to get notifications if data has changed
        '''
        self._dataDict = {}
        self._subscriber = []

    def addDataModelEntry(self, dataModelEntry):
        '''
        Adds a new data model entry (DataModelEntry derived) object to the data model.

        As key for the internal dictionary the "data id" is used. For that, the DataModelEntry class has to
        implement the getDataID() method. This method return true, if the insertion of the data model entry
        object was successfull. Otherwise it returns false
        '''
        insertResult = False

        try:
            self._dataDict[dataModelEntry.getDataID()] = dataModelEntry
            insertResult = True
        except:
            pass

        return insertResult

    def getDataModelEntry(self, dataID):
        '''
        Return a data model entry object based on the provided dataID.

        If the internal dictionary does not contain the provided dataID, None is returned
        '''
        try:
            return self._dataDict[dataID]
        except:
            return None

    def updateDataModelEntry(self, dataID, data):
        '''
        Updates an already added data entry object.

        This update is related to the "data" for the object and does not relate to the data
        entry object itself. Therefore a dataID and data is provided. If the data has changed,
        all regsitered subscribers are notified by this method

        Returns True, if the data of the dataID has changed compared to the last update.
        Otherwise it returns False
        '''

        updateResult = False
        dataEntry = self.getDataModelEntry(dataID)

        if dataEntry != None:
            dataChanged = dataEntry.setData(data)
            if dataChanged == True:
                self.notifySubscriber(dataEntry)

            updateResult = True

        return updateResult

    def getDataModelEntryIterator(self):
        '''
        '''
        for entry in self._dataDict.values():
            yield entry

    def registerSubscriber(self, sub):
        '''
        Registers a subscriber object in the internal subscriber list
        '''
        self._subscriber.append(sub)

    def unregisterSubscriber(self, sub):
        '''
        '''
        self._subscriber.remove(sub)

    def notifySubscriber(self, dataEntry):
        '''
        '''
        for sub in self._subscriber:
            if sub != None:
                sub.notify(dataEntry)
