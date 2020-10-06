#!/bin/bash
# script to flash a target device
FILE=$1
st-flash erase
st-flash --reset write $FILE 0x08000000

