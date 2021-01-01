
class Subscriber:
    '''
    Interface for a Subscriber object which provides the notify() method
    '''

    def notify(self, dataEntry):
        '''
        Methods which gets called by a subscriber manager
        '''
        raise NotImplementedError