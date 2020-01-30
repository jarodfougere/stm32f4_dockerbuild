# rimot-lowpower-sensorboard

# Change different from Carl



# RF EXAMPLE PAYLOADS #
{"systick":{"model_name":"Opio RF Monitor","device_name":"Unnamed","device_id":"260055001551373239343533","uptime":{"value":"1650","units":"seconds"}}}
"rfdetect":{"device_id":"270054001551373239343533","VSWR":{"value":"1.2","units":" "},"FPWR":{"value":"40.2","units":"dBm"},"RPWR":{"value":"20.8","units":"dBm"},"FMAXPWR":{"value":"40.7","units":"dBm"},"RMAXPWR":{"value":"21.2","units":"dBm"},"FMINPWR":{"value":"39.6","units":"dBm"},"RMINPWR":{"value":"20.3","units":"dBm"},"DUTY":{"value":"1.00","units":" "}}}


# GPIO EXAMPLE PAYLOADS #
{"system":"info"}

//read commands
{"read":"hb_interval"}
{"read":"fwVersion"}
{"read":"hwVersion"}
{"read":"pin_info_interval"}
{"read":"dcIn"}
{"read":"relays"}
{"read":"batteries"}


//write commands
{"write":{"pin_info_interval":5}}
{"write":{"pin_info_interval":60}}
{"write":{"config":"true"}}

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

{"GPIO_PIN_UPDATE":"true"}
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



# MOTH EXAMPLE PAYLOADS #