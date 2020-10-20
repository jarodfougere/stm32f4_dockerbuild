## WHAT THIS IS ##

## THIS IS A CROSS-PLATFORM BUILD SYSTEM FOR STM32F411 MICROCONTROLLER ##


## DEPENDENCIES ##

docker
python3

## Building ##

[With python3 executable added to PATH ]

python3 ./dockerbuild_py


# README #



# rimot-lowpower-sensorboard

# ENVIRONMENT #

CLONE THE REPOSITORY AND OPEN THE WORKSPACE FOLDER IN VSCODE. THE REST SHOULD BE AUTOMATED.
I HAVE BEEN CONTINUALLY WORKING ON AUTOMATING THE ENVIRONMENT.

CMSIS
https://github.com/ARM-software/CMSIS_5

* CPU Architecture options usage *

The project toolchain is intended for Cortex-M (and possibly R) bare metal development.
the following table shows how to invoke GCC/G++ with correct command line
options for various architectures. This is mostly here so I don't have to keep digging 
through all the compiler documentation for the various flags

--------------------------------------------------------------------
| ARM Core | Command Line Options                       | multilib |
|----------|--------------------------------------------|----------|
|Cortex-M0+| -mthumb -mcpu=cortex-m0plus                | armv6-m  |
|Cortex-M0 | -mthumb -mcpu=cortex-m0                    |          |
|Cortex-M1 | -mthumb -mcpu=cortex-m1                    |          |
|          |--------------------------------------------|          |
|          | -mthumb -march=armv6-m                     |          |
|----------|--------------------------------------------|----------|
|Cortex-M3 | -mthumb -mcpu=cortex-m3                    | armv7-m  |
|          |--------------------------------------------|          |
|          | -mthumb -march=armv7-m                     |          |
|----------|--------------------------------------------|----------|
|Cortex-M4 | -mthumb -mcpu=cortex-m4                    | armv7e-m |
|(No FP)   |--------------------------------------------|          |
|          | -mthumb -march=armv7e-m                    |          |
|----------|--------------------------------------------|----------|
|Cortex-M4 | -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp | armv7e-m |
|(Soft FP) | -mfpu=fpv4-sp-d16                          | /softfp  |
|          |--------------------------------------------|          |
|          | -mthumb -march=armv7e-m -mfloat-abi=softfp |          |
|          | -mfpu=fpv4-sp-d16                          |          |
|----------|--------------------------------------------|----------|
|Cortex-M4 | -mthumb -mcpu=cortex-m4 -mfloat-abi=hard   | armv7e-m |
|(Hard FP) | -mfpu=fpv4-sp-d16                          | /fpu     |
|          |--------------------------------------------|          |
|          | -mthumb -march=armv7e-m -mfloat-abi=hard   |          |
|          | -mfpu=fpv4-sp-d16                          |          |
|----------|--------------------------------------------|----------|


# Building #

Currently the project uses IAR embedded workbench with some custom vscode extensions for 
quality of life. Editing, compilation and automated testing can be done through vscode 
(.vscode folder contains all of the required configurations). Currently, using C-SPY 
with a JTAG/ SWD probe for hardware (rather than symbol-base) debugging requires 
using the IAR SYSTEMS EWARM IDE.

In the future, the plan is to transition to CMake + arm-none-eabi-gcc as the build system 
since it is open source and cross-platform (facilitiates linux developent)

## Formatter ##

The Coding standard to which the project source code is validated is BARR Embedded Incorporate'd 
C coding standard. The documentation folder contains the standard document in pdf format. The standard
is meant to be used as a GUIDELINE rather than a strict rule. Despite this, all C source files must
comply with the ISO C99 standard.

The project uses clang-format as its formatter. If you are using visual studio, you can install 
https://marketplace.visualstudio.com/items?itemName=xaver.clang-format as an extension and 
the settings.json file will automatically set up the formatting to occur on .c / .h file save.
Documentation for clang-format options (part of the LLVM project) can be found at
https://clang.llvm.org/docs/ClangFormatStyleOptions.html 

The LLVM binaries must also be installed on your system to use clang format. 
These can be downloaded as part of LLVM binutils at https://releases.llvm.org/download.html

Note that the "clang-format" executable must be added to your $PATH variable

# REQUEST AND RESPONSE STRUCTURE #


{"systick":{"model_name":"Opio RF Monitor","device_name":"Unnamed","device_id":"260055001551373239343533","uptime":{"value":"1650","units":"seconds"}}}
"rfdetect":{"device_id":"270054001551373239343533","VSWR":{"value":"1.2","units":" "},"FPWR":{"value":"40.2","units":"dBm"},"RPWR":{"value":"20.8","units":"dBm"},"FMAXPWR":{"value":"40.7","units":"dBm"},"RMAXPWR":{"value":"21.2","units":"dBm"},"FMINPWR":{"value":"39.6","units":"dBm"},"RMINPWR":{"value":"20.3","units":"dBm"},"DUTY":{"value":"1.00","units":" "}}}

//activate RF sensor 1/2
{"RF_CONFIG": {"id" : 1, "active":1, "transmitter_id": "##STRING##"}}
{"RF_CONFIG": {"id" : 2, "active":1, "transmitter_id": "##STRING##"}}

//deactivate RF sensor 1/2
{"RF_CONFIG": {"id" : 1, "active":0, "transmitter_id": "##STRING##"}}
{"RF_CONFIG": {"id" : 2, "active":0, "transmitter_id": "##STRING##"}}


# COMMANDS FROM OUTPOST TO DEVICE #

This section outlines the command structure for payloads going from the outpost to the low power sensor card.
All commands are in JSON format.
The command structure is identical to that of the existing sensors (ie: GPIO commands are the same as commands to the GPIO controller). This is done to minimize the changes required in outpost software.

## GPIO COMMANDS ##

### system commands ###

{"system":"info"}

This command requests the system info from the device. The response will contain fields describing:
    * hardware version
    * firmware version
    * pin info interval
    * systick interval


{"system" : "reset_main"}

This command causes a software reset:
    - more technically, the nested vector interrupt controller (NVIC) issues a cortex reset, all PLL and register values are set to their defaults by hardware, 
      and the PC  is set to the reset vector in the exception table. Entry code is not executed (so stack and heap remain initialized.)

{"system" : "reset_boot"} 

    - This command sets the bootloader jump flag and performs an NVIC cortex reset, causing a mainline entry that then jumps to the embedded bootloader.

### read commands ###

The commands read general application parameters

{"read":"hb_interval"}

{"read":"fwVersion"}

{"read":"hwVersion"}

{"read":"pin_info_interval"}

### write commands ###

These commands update general application parameters.

{"write":{"pin_info_interval":5}}

{"write":{"pin_info_interval":60}}

{"write":{"config":"true"}}

### GPIO PIN CONFIG COMMANDS ###

This subsection outlines the command structure for configuring GPIO interface pins (digital inputs, digital outputs, or battery monitoring).

Setting the configuration of a pin does not update the interface or existing device until the GPIO_PIN_UPDATE command is received.

JSON structure:
{
    "GPIO_PIN_CONFIG"  :
    {
        "id"         : unsigned integer > 0 // the pin "number" of the interface
        "type"       : unsigned integer > 0 // the interface type 0/1/2 for inputs/relays/battery
        "active"     : 0 / 1                // active vs inactive
        "trigger"    : 0 / 1                // digital high vs low for digital inputs
        "state"      : 0 / 1                // open / closed default position for relays
        "debounce"   : signed integer       (-1 | 0 - 32bit max) 
        "priority"   : (not yet implemented)
        "redHigh"    : unsigned integer     //threshhold in millivolts
        "yellowHigh" : unsigned integer     //threshhold in millivolts
        "yellowLow"  : unsigned integer     //threshhold in millivolts
        "redLow"     : unsigned integer     //threshhold in millivolts
    }
}

Examples GPIO_PIN_CONFIG commands are provided in the following subsections.

#### GPIO_PIN_CONFIG EXAMPLE : ACTIVATE INPUTS AS ACTIVE HIGH ####

{"GPIO_PIN_CONFIG":{"id":1, "type":0, "label":0, "active":1, "trigger":1, "debounce":100 }}

{"GPIO_PIN_CONFIG":{"id":2, "type":0, "label":0, "active":1, "trigger":1, "debounce":20 }}

{"GPIO_PIN_CONFIG":{"id":3, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":4, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":5, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":6, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":7, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":8, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

#### GPIO_PIN_CONFIG EXAMPLE : ACTIVATE INPUTS AS ACTIVE LOW ####

{"GPIO_PIN_CONFIG":{"id":1, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":2, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":3, "type":0, "label":0, "active":1, "trigger":0, "debounce":100 }}

{"GPIO_PIN_CONFIG":{"id":4, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":5, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":6, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":7, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":8, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}

#### GPIO_PIN_CONFIG EXAMPLE : DEACTIVATE INPUTS ####

{"GPIO_PIN_CONFIG":{"id":1, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":2, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":3, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":4, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":5, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":6, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":7, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

{"GPIO_PIN_CONFIG":{"id":8, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}

#### GPIO_PIN_CONFIG EXAMPLE : ACTIVATE OUTPUTS WITH DEFAULT STATE == CONTACT CLOSED ####

{ "GPIO_PIN_CONFIG": { "id": 1, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": -1 } }

{ "GPIO_PIN_CONFIG": { "id": 2, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": 40 } }

{ "GPIO_PIN_CONFIG": { "id": 3, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": 60 } }

{ "GPIO_PIN_CONFIG": { "id": 4, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": 80 } }

#### GPIO_PIN_CONFIG EXAMPLE : ACTIVATE OUTPUTS WITH DEFAULT STATE == CONTACT OPEN ####

{ "GPIO_PIN_CONFIG": { "id": 1, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 100 } }

{ "GPIO_PIN_CONFIG": { "id": 2, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 20 } }

{ "GPIO_PIN_CONFIG": { "id": 3, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 20 } }

{ "GPIO_PIN_CONFIG": { "id": 4, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 20 } }

#### GPIO_PIN_CONFIG EXAMPLE : DEACTIVATE OUTPUTS (CONTACT STATE WILL RETURN TO OPEN) ####

{ "GPIO_PIN_CONFIG": { "id": 1, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }

{ "GPIO_PIN_CONFIG": { "id": 2, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }

{ "GPIO_PIN_CONFIG": { "id": 3, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }

{ "GPIO_PIN_CONFIG": { "id": 4, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }

#### GPIO_PIN_CONFIG EXAMPLE : ACTIVATE BATTERY ####

{ "GPIO_PIN_CONFIG": { "id": 1, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{ "GPIO_PIN_CONFIG": { "id": 2, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{ "GPIO_PIN_CONFIG": { "id": 3, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{ "GPIO_PIN_CONFIG": { "id": 4, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

#### GPIO_PIN_CONFIG EXAMPLE : DEACTIVATE BATTERY ####

{ "GPIO_PIN_CONFIG": { "id": 1, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{ "GPIO_PIN_CONFIG": { "id": 2, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{ "GPIO_PIN_CONFIG": { "id": 3, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{ "GPIO_PIN_CONFIG": { "id": 4, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}


### GPIO PIN UPDATE ###

Apply all changes to the device state via GPIO_PIN_CONFIG commands since the last time GPIO_PIN_UPDATE command was received. The applied configuration is then stored in non-volatile memory.

JSON structure:
{
    "GPIO_PIN_UPDATE" : true
}

{"GPIO_PIN_UPDATE":"true"}

{"GPIO_PIN_UPDATE":true}

### GPIO FUNCTIONALITY REQUEST (DEVICE INFO) ###

{"GPIO_DEVICE_INFO"}

### OUTPOST ID REGISTRATION ###

Register an outpost ID with the device (ie: assign the device to an outpost).
An outpost ID can only be assigned to the device upon boot up. If the outpost ID matches the ID stored in the device, the pin configurations will be loaded from non-volatile memory and applied. If the ID does not match the previously assigned ID, the stored configuration will be reset. 

This command is only processed the first time it is received after a device boot (ie: outpost ID cannot be reassigned while the device is running). This command will be ignored if an outpost ID has already been registered after the device booted. Whenever this command is processed, the registered outpost ID is stored in non-volatile memory. 

The outpost ID must be a nul-terminated string literal consisting of 6 characters with ASCII encoding.

{"outpostID" : "020104"}

{"outpostID" : "020103"}

### GPIO PIN COMMANDS ###

These commands instruct the GPIO interface pins to take action based on their configuration.

#### TRIGGER RELAYS ####

Switch a relay from its user-configured default state to its triggered state. If the relay has a configured hold time, the triggered state will be held for the hold time before returning to the default state. If the output pin is configured in toggle mode (pin is configured with hold time of -1), then the relay will remain in the triggered  state until the pin is reconfigured or a GPIO_PIN_COMMAND is sent with trigger field equal to 0 (cancelling the ongoing pin command)

{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 1, "type" : "1"}}

{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 2, "type" : 1 }}

{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 3, "type" : 1 }}

{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 4, "type" : 1 }}

#### CANCEL TRIGGERING OF RELAYS (RETURNS RELAY CONTACT FROM TRIGGERED STATE TO DEFAULT STATE) ####

Cancel an ongoing pin command for a given digital output pin: returning the relay contact from its triggered state to the user-configured default state. If there is no ongoing pin command, this command will be ignored. 

{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 1, "type" : 1 }}

{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 2, "type" : 1 }}

{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 3, "type" : 1 }}

{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 4, "type" : 1 }}



## RF COMMANDS ##




## MoTH Commands ##



    






