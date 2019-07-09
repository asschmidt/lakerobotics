from pyusbtin.usbtin import USBtin
from pyusbtin.canmessage import CANMessage
from time import sleep

def log_data(msg):
    print(msg)

usbtin = USBtin()
usbtin.connect("COM4")
print("Firmware: " + str(usbtin.get_firmware_version()))

usbtin.add_message_listener(log_data)
usbtin.open_can_channel(125000, USBtin.ACTIVE)

while(True):
    print("tick")
    #usbtin.send(CANMessage(0x100, "\x11"))
    sleep(1)
