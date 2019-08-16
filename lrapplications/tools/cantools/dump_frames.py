from pyusbtin.usbtin import USBtin
from pyusbtin.canmessage import CANMessage
from time import sleep

def log_data(msg):
    print(msg)

usbtin = USBtin()
usbtin.connect("COM3")
print("Firmware: " + str(usbtin.get_firmware_version()))

usbtin.add_message_listener(log_data)
usbtin.open_can_channel(125000, USBtin.ACTIVE)

sendCount = 0

while(sendCount <= 3000):
    print("tick")
    usbtin.send(CANMessage(0x3FF, [0x01, 0x00, 0x00, 0x00]))
    sleep(5)
    
    usbtin.send(CANMessage(0x3FF, [0x01, 0x00, 0x00, 0x01]))
    sleep(5)
    
    usbtin.send(CANMessage(0x3FF, [0x01, 0x00, 0x01, 0x01]))
    sleep(5)
    
    usbtin.send(CANMessage(0x3FF, [0x01, 0x01, 0x01, 0x01]))
    sleep(5)
    
    sendCount = sendCount + 1 
    
usbtin.close_can_channel()
usbtin.disconnect()
