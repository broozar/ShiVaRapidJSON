# ShiVaRapidJSON
JSON parser for ShiVa using RapidJSON

## RapidJSON
This project uses RapidJSON, which you can get separately on
https://github.com/miloyip/rapidjson

# API (ShiVa)
    { "getArraySize", Callback_rjson_getArraySize, "nSizeOrNil", "sID, sKeyToArray", "checks if a key refers to an array and returns its size if so", 0 }, 
    { "init"      , Callback_rjson_init      , "bOK"   , "nReserve"  , "inits plugin and reserves nReserve JSON doc slots", 0 }, 
    { "loadString", Callback_rjson_loadString, "bOK"   , "sID, sJSON", "loads sJSON string and stores it under sID"       , 0 }, 
    { "hasValue"  , Callback_rjson_hasValue  , "bYes"  , "sID, sKey" , "checks if a value for sKey in sID exists"         , 0 }, 
    { "getValue"  , Callback_rjson_getValue  , "vValue", "sID, sKey" , "returns value for sKey in sID"                    , 0 }, 
    { "hasKey"    , Callback_rjson_hasKey    , "bYes"  , "sID, sKey" , "checks if sKey in sID exists"                     , 0 }    

# Usage
1. call rjson.init(some_number) to initialize
2. call rjson.loadstring (sID, sJSON) to load a string into the plugin to parse it
3. call .getValue, the .has\* functions, or .getArraySize to access values inside the JSON data

## sKey syntax
Keys are CSV strings, each element is separated by a comma without spaces and every array index must be precedet by a question mark:
'arr,?3' queries the 4th element of the JSON array named "arr".
See DEMO 2 for a more complex example.

## Remarks
- Don't call .has\* if you want to retrieve data. If a value does not exist, .getValue will not crash but instead return NIL. Use .has\* if your goal really is to just check for the existence of a key or value.
- Same goes for the array size check. If you wander out of the array bounds, you will receive NIL, but it will not crash.
- Check the demo inside the onInit() handler for more examples.
