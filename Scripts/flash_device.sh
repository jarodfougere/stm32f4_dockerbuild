#!/bin/bash
# script to flash a target device
which st-flash
if [ $? -ne 0 ]; then
    ./install_stlink.sh
fi

if [ -z "$1" ]; then
    echo "no file has been provided as ARGV[1]"
    exit 1
else
    if [ -z "$2" ]; then
        FILE=$1
    else
        echo "flash_device.sh only takes a single argument: the file to upload"
        exit 1
    fi
fi

basename=$(basename -- "$FILE")
extension="${FILE##*.}"
filename="${FILE%.*}"
echo "basename = $basename and extension = $extension and filename = $filename"

which arm-none-eabi-objcopy
if [ $? -ne 0 ] ; then 
    ./install_arm_none_eabi_toolchain.sh
fi

NUMBER_STLINKS=$((st-info --probe) 2> /dev/null | grep programmers | tr -s ' ' | awk '{print $2}')
if [ $NUMBER_STLINKS -gt 1 ] ; then
    echo "$NUMBER_STLINKS have been detected by st-info. Please unplug the other target devices before continuing" 
    exit 1
elif [ $NUMBER_STLINKS -eq 0 ]; then
    echo "$NUMBER_STLINKS have been detected by st-info. Please plug in the device before continuing."
    echo "If this issue persists, make sure that udev rules have been correctly configured and that the firmware on the stlink programmer is up to date"
    exit 1
fi

if [ "$extension" = "bin" ]; then
    echo "gotta put something here so bash doesn't complain" > /dev/null
elif [ "$extension" = "hex" ]; then
    arm-none-eabi-objcopy -O binary -I ihex $FILE $basename
elif [ "$extension" = "elf" ]; then
    arm-none-eabi-objcopy -O binary -I elf32-little $FILE $basename
else
    echo "$FILE is an invalid format (based on naming extensions) to flash the target device"
    exit -1
fi

st-flash --reset write $filename.bin 0x08000000

if [ "$?" -ne 0 ]; then
    echo "Error flashing device with $FILE"
fi

# cleanup
if [ -f "$basename" ]; then
    rm $basename
fi



