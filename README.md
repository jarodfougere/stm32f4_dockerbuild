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

CMAKE EXECUTABLE MUST BE ADDED TO $PATH.

YOU MUST EDIT TOOLCHAIN_PREFIX TO BE THE LOCATION OF WHERE THE GNU ARM TOOLCHAIN IS INSTALLED

## Windows ##

cmake -E remove -f Pipeline/CMakeCache.txt; cmake -S CMake -B Pipeline -G "MinGW Makefiles" -D PROCESSOR_MPN:string=stm32f411xe -D TOOLCHAIN_PREFIX:string="C:/Program\ Files\ (x86)/GNU\ Tools\ Arm\ Embedded/9\ 2019-q4-major/bin" ;cmake --build Pipeline

## Unix ##

cmake -E remove -f Pipeline/CMakeCache.txt; cmake -S CMake -B Pipeline -G "Unix Makefiles" -D PROCESSOR_MPN:string=stm32f411xe -D TOOLCHAIN_PREFIX:string="C:/Program\ Files\ (x86)/GNU\ Tools\ Arm\ Embedded/9\ 2019-q4-major/bin" ;cmake --build Pipeline

# REQUEST AND RESPONSE STRUCTURE #


{"systick":{"model_name":"Opio RF Monitor","device_name":"Unnamed","device_id":"260055001551373239343533","uptime":{"value":"1650","units":"seconds"}}}
"rfdetect":{"device_id":"270054001551373239343533","VSWR":{"value":"1.2","units":" "},"FPWR":{"value":"40.2","units":"dBm"},"RPWR":{"value":"20.8","units":"dBm"},"FMAXPWR":{"value":"40.7","units":"dBm"},"RMAXPWR":{"value":"21.2","units":"dBm"},"FMINPWR":{"value":"39.6","units":"dBm"},"RMINPWR":{"value":"20.3","units":"dBm"},"DUTY":{"value":"1.00","units":" "}}}

//activate RF sensor 1/2
{"RF_CONFIG": {"id" : 1, "active":1, "transmitter_id": "##STRING##"}}
{"RF_CONFIG": {"id" : 2, "active":1, "transmitter_id": "##STRING##"}}

//deactivate RF sensor 1/2
{"RF_CONFIG": {"id" : 1, "active":0, "transmitter_id": "##STRING##"}}
{"RF_CONFIG": {"id" : 2, "active":0, "transmitter_id": "##STRING##"}}

## GPIO EXAMPLE PAYLOADS ##
{"system":"info"}
{"system":"reset_main"}
{"system":"reset_boot"}

//ENTER / EXIT LOW POWER MODE
{"system": {"mode":0}}
{"system": {"mode":1}}


//read commands
{"read":"hb_interval"}
{"read":"fwVersion"}
{"read":"hwVersion"}
{"read":"pin_info_interval"}

//write commands
{"write":{"pin_info_interval":5}}
{"write":{"pin_info_interval":60}}
{"write":{"config":true}}

//TURN ACTIVATE INPUTS 1-> 8 active high 
{"GPIO_PIN_CONFIG":{"id":1, "type":0, "label":0, "active":1, "trigger":1, "debounce":100 }}
{"GPIO_PIN_CONFIG":{"id":2, "type":0, "label":0, "active":1, "trigger":1, "debounce":20 }}
{"GPIO_PIN_CONFIG":{"id":3, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":4, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":5, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":6, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":7, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":8, "type":0, "label":0, "active":1, "trigger":1, "debounce":10 }}

//TURN ACTIVATE INPUTS 1-> 8 active low
{"GPIO_PIN_CONFIG":{"id":1, "type":0, "label":0, "active":1, "trigger":0, "debounce":40 }}
{"GPIO_PIN_CONFIG":{"id":2, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":3, "type":0, "label":0, "active":1, "trigger":0, "debounce":100 }}
{"GPIO_PIN_CONFIG":{"id":4, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":5, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":6, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":7, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":8, "type":0, "label":0, "active":1, "trigger":0, "debounce":10 }}


//deactivate inputs 1-8
{"GPIO_PIN_CONFIG":{"id":1, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":2, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":3, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":4, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":5, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":6, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":7, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}
{"GPIO_PIN_CONFIG":{"id":8, "type":0, "label":0, "active":0, "trigger":1, "debounce":10 }}


//activate oututs 1-4 (closed)
{ "GPIO_PIN_CONFIG": { "id": 1, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": -1 } }
{ "GPIO_PIN_CONFIG": { "id": 2, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": 40 } }
{ "GPIO_PIN_CONFIG": { "id": 3, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": 60 } }
{ "GPIO_PIN_CONFIG": { "id": 4, "type": 1, "label": 1, "active": 1, "trigger": 1, "debounce": 80 } }


//activate oututs 1-4 (open)
{ "GPIO_PIN_CONFIG": { "id": 1, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 100 } }
{ "GPIO_PIN_CONFIG": { "id": 2, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 20 } }
{ "GPIO_PIN_CONFIG": { "id": 3, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 20 } }
{ "GPIO_PIN_CONFIG": { "id": 4, "type": 1, "label": 1, "active": 1, "trigger": 0, "debounce": 20 } }


//deactivate outputs 1-4
{ "GPIO_PIN_CONFIG": { "id": 1, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }
{ "GPIO_PIN_CONFIG": { "id": 2, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }
{ "GPIO_PIN_CONFIG": { "id": 3, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }
{ "GPIO_PIN_CONFIG": { "id": 4, "type": 1, "label": 1, "active": 0, "trigger": 0, "debounce": 20 } }


//activate battery
{ "GPIO_PIN_CONFIG": { "id": 1, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}
{ "GPIO_PIN_CONFIG": { "id": 2, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}
{ "GPIO_PIN_CONFIG": { "id": 3, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}
{ "GPIO_PIN_CONFIG": { "id": 4, "type": 2, "label": 1, "active": 1, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

//deactivate battery
{ "GPIO_PIN_CONFIG": { "id": 1, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}
{ "GPIO_PIN_CONFIG": { "id": 2, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}
{ "GPIO_PIN_CONFIG": { "id": 3, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}
{ "GPIO_PIN_CONFIG": { "id": 4, "type": 2, "label": 1, "active": 0, "debounce":10, "battType":1, "redHigh":15000, "redLow":8000, "yellowHigh":13500, "yellowLow":10000}}

{"GPIO_PIN_UPDATE":true}

{"GPIO_DEVICE_INFO"}
{"outpostID" : "020104"}
{"outpostID" : "020103"}

//TRIGGER THE RELAYS
{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 1, "type" : "1"}}
{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 2, "type" : 1 }}
{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 3, "type" : 1 }}
{"GPIO_PIN_CMD" : {"trigger" : 1, "id": 4, "type" : 1 }}

//CANCEL THE TRIGGER OF THE RELAYS
{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 1, "type" : 1 }}
{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 2, "type" : 1 }}
{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 3, "type" : 1 }}
{"GPIO_PIN_CMD" : {"trigger" : 0, "id": 4, "type" : 1 }}



## INCOMING DATA ##


GPIO_PIN_CONFIGURATION:


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
    
description:
    sets the configuration of a given gpio "pin". This does not update the gpio interface.
    When


GPIO DEVICE UPDATE:

JSON structure:
{
    "GPIO_PIN_UPDATE" : true
}

description: updates the edge device GPIO configuration based on the GPIO_PIN_CONFIG commands previously sent.
             the edge device updates its GPIO interfaces and stores configuration in its non-volatile memory.




REQUEST DATA:
JSON structure:
{
    "SEND_DATA" : true
}

description: prompts the sensor to immediately transmit all cached payloads that would normally have been transmitted at the next synchronous interval


DEVICE CONFIGURATION:

JSON 