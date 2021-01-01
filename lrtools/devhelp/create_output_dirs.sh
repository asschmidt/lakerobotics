
# Goto application root directory
cd $LRAPPLICATION_ROOT_PATH

mkdir out
cd out

ARDUINO_DIR=arduino
STM32_DIR=stm32
RASP_DIR=rasp

# Create the different target directories
mkdir $ARDUINO_DIR
mkdir $STM32_DIR
mkdir $RASP_DIR

# Create the different build type directories
mkdir $ARDUINO_DIR/Debug
mkdir $ARDUINO_DIR/Release

mkdir $STM32_DIR/Debug
mkdir $STM32_DIR/Release

mkdir $RASP_DIR/Debug
mkdir $RASP_DIR/Release
