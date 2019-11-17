

'''
Definition for different network types
'''
class NetworkDataType:
    UNKNOWN     = 0
    CAN         = 1
    ETHERNET    = 2
    RS485       = 3
    WLAN        = 5
    RF433       = 6
    SERIAL      = 7
    
    '''
    Parse the attribute value string and returns the corresponding networkdatatype
    '''
    @classmethod
    def parseNetworkType(self, netTypeAttribValue):
        if netTypeAttribValue.upper() == "CAN":
            return NetworkDataType.CAN
        elif netTypeAttribValue.upper() == "ETHERNET":
            return NetworkDataType.ETHERNET
        elif netTypeAttribValue.upper() == "RS485":
            return NetworkDataType.RS485
        elif netTypeAttribValue.upper() == "RF433":
            return NetworkDataType.RF433
        elif netTypeAttribValue.upper() == "WLAN":
            return NetworkDataType.WLAN
        elif netTypeAttribValue.upper() == "SERIAL":
            return NetworkDataType.SERIAL
        else:
            return NetworkDataType.UNKNOWN

'''
Definitions for network bandwiths 
Specified in kbps
'''
class NetworkDataBandwith:
    SPEED_UNKNOWN   = 0
    SPEED_100kbps   = 100
    SPEED_250kbps   = 250
    SPEED_500kbps   = 500
    SPEED_10Mbps    = 10000
    SPEED_100Mbps   = 100000
    
    '''
    Parse the bandwith attribute string and returns a corresponding networkbandwith
    '''
    @classmethod
    def parseNetworkBandwidth(self, netBandwidthAttribValue): 
        if netBandwidthAttribValue == None:
            return NetworkDataBandwith.SPEED_UNKNOWN
                           
        if netBandwidthAttribValue.upper() == "100KBPS":
            return NetworkDataBandwith.SPEED_100kbps
        elif netBandwidthAttribValue.upper() == "250KBPS":
            return NetworkDataBandwith.SPEED_250kbps
        elif netBandwidthAttribValue.upper() == "500KBPS":
            return NetworkDataBandwith.SPEED_500kbps
        elif netBandwidthAttribValue.upper() == "10MBPS":
            return NetworkDataBandwith.SPEED_10Mbps
        elif netBandwidthAttribValue.upper() == "100MBPS":
            return NetworkDataBandwith.SPEED_100Mbps
        else:
            return NetworkDataBandwith.SPEED_UNKNOWN

'''
Class to hold the definition of a "Network"
'''
class NetworkData:
    def __init__(self):
        self.ID = "ID"
        self.Name = "No Network Name"
        self.Type = NetworkDataType.UNKNOWN
        self.Bandwith = NetworkDataBandwith.SPEED_UNKNOWN
        
    def __repr__(self):
        return "Network: " + self.Name + " Type: " + str(self.Type) + " (" + str(self.Bandwith) + ")"
    
'''
Class to parse the XML data of the network definitions and create a internal representation
of the network data.
'''
class NetworkDataParser:
    def __init__(self, networkRoot):
        self._networkRoot = networkRoot
                    
    '''
    Parses the <Network> elements under the <Networks> root and returns a dictionary with all
    Network objects
    '''
    def parse(self):
        networkDict = {}
        
        # Iterate over all <Network> elements from the <Networks> root element
        for networkElement in self._networkRoot:
            data = NetworkData()
            
            # Get the ID and the name
            data.ID = networkElement.get("ID")
            data.Name = networkElement.get("Name")
            # Parse the network type
            data.Type = NetworkDataType.parseNetworkType(networkElement.get("Type"))
            # Parse the network bandwidth
            data.Bandwith = NetworkDataBandwith.parseNetworkBandwidth(networkElement.get("Bandwidth"))
            
            networkDict[data.ID] = data
        
        return networkDict