from pyusbtin.usbtin import USBtin
from pyusbtin.canmessage import CANMessage
from time import sleep

def log_data(msg):
    print(msg)

usbtin = USBtin()
usbtin.connect("COM4")
print("Firmware: " + str(usbtin.get_firmware_version()))

usbtin.add_message_listener(log_data)
usbtin.open_can_channel(500000, USBtin.ACTIVE)

while(True):
    command = str(input())
    
    if command == "E11":
        print("Sending E11")
        usbtin.send(CANMessage(0x3FF, [0x01, 0x01, 0x01, 0x01]))
        #sleep(1)
    elif command == "E10":
        print("Sending E10")
        usbtin.send(CANMessage(0x3FF, [0x00, 0x01, 0x01, 0x01]))
    elif command == "EXIT":
        break 
    
usbtin.close_can_channel()
usbtin.disconnect()
