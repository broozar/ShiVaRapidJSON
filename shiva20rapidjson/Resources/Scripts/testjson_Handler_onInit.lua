--------------------------------------------------------------------------------
--  Handler.......... : onInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function testjson.onInit (  )
--------------------------------------------------------------------------------
	
    -- init: always required
    -- parameter number to reserve the #JSON_strings you will most likely be handling
    if not rjson.init ( 4 ) then 
        log.warning ( "RapidJSON init failed!" )
        return 
    end
    
    -- KEY QUERY SYNTAX --------------------------------------------------------
    -- 
    -- keys are CSV strings, each element is separated by a comma without spaces
    -- and every array index must be precedet by a question mark:
    -- 'arr,?3' queries the 4th element of the JSON array named "arr".
    -- see DEMO 2 for a more complex example.
    
    
    -- DEMO --------------------------------------------------------------------
    -- TEST --------------------------------------------------------------------
    -- DEMO --------------------------------------------------------------------
    
    
    -- demo strings
	local json1 = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    local json2 = " { \"hi\": \"hellow\", \"first\":  {\"next\":[{\"key\":\"important_value_1\"}  ] } } "
    local json3 = " { \"id\": 1, \"title\": \"What movie should we watch\", \"multi\": false, \"options\": [ \"Sucker punch\", \"Pirates of Carribean\", \"Prison logic\", \"Witchhunter\" ], \"votes\": [ 13072, 26807, 4868, 6425 ] } "
    
    -- load strings into plugin
    if not rjson.loadString ( "j", json1 ) then log.warning ( "Error loading json1" ) return end
    if not rjson.loadString ( "k", json2 ) then log.warning ( "Error loading json2" ) return end
    if not rjson.loadString ( "l", json3 ) then log.warning ( "Error loading json3" ) return end
    
    
    -- demo content json1
    log.warning ( "RJSON: DEMO 1 CHECKS --------------------" )
    -- key checks (existence)
    if rjson.hasKey ( "j", "hello" ) then       log.message ( "ay 1" )   else   log.message ( "nay 1" )     end -- true
    if rjson.hasKey ( "j", "h3llo" ) then       log.message ( "ay 2" )   else   log.message ( "nay 2" )     end -- false, also error log
    
    -- checks (existence and not_noll)
    if rjson.hasValue( "j", "hello" ) then     log.message ( "ay 3" ) else   log.message ( "nay 3" )   end -- true
    if rjson.hasValue( "j", "h3llo" ) then     log.message ( "ay 4" ) else   log.message ( "nay 4" )   end -- false, also error log
    if rjson.hasValue( "j", "n" ) then         log.message ( "ay 5" ) else   log.message ( "nay 5" )   end -- false, because NULL (but no error)
    if rjson.hasValue( "j", "hello,?3" ) then  log.message ( "ay 6" ) else   log.message ( "nay 6" )   end -- false, 'hello' is not an array, also error log
    
    -- bad identifier
    if rjson.hasValue( "m", "n" ) then         log.message ( "ay 7" ) else   log.message ( "nay 7" )   end -- false, because 'm' has not been loaded, also error log

    -- primitives
    log.warning ( "RJSON: DEMO 1 PRMITIVES --------------------" )
    log.message ( rjson.getValue ( "j", "hello" ) ) -- world (as string)
    log.message ( rjson.getValue ( "j", "t" ) )     -- true (as boolean)
    log.message ( rjson.getValue ( "j", "n" ) )     -- nil (as conversion from JSON null)
    log.message ( rjson.getValue ( "j", "i" ) )     -- 123 (as number from int)
    log.message ( rjson.getValue ( "j", "pi" ) )    -- 3.1416 (as number from float)
    log.message ( rjson.getValue ( "j", "a" ) )     -- prints "JSON_ARRAY" string
    log.message ( rjson.getValue ( "j", "a,?0" ) )  -- 1 (first element of "a" array)
    
    -- array size
    local a = rjson.getArraySize ( "j", "a" )       -- always a good idea to check against nil for errors
    if a ~= nil then log.message ( "Array size: " ..a ) end
    
    -- array out of bounds
    log.message ( rjson.getValue ( "j", "a,?4" ) )  -- nil, because out of bounds + error log
    
    
    -- demo content json2
    log.warning ( "RJSON: DEMO 2 --------------------" )
    -- prints important_value_1 as an example for a nested structure
    log.message ( rjson.getValue ( "k", "first,next,?0,key" ) ) 
    
    
    -- demo content json3
    log.warning ( "RJSON: DEMO 3 --------------------" )
    -- realworld strawpoll.me example: prints how many people voted for Pirates of the Carribbean
    log.message ( "Votes for " ..rjson.getValue ( "l", "options,?1" ) ..": " ..rjson.getValue ( "l", "votes,?1" ) ) 
	
    
    log.warning ( "RJSON: DEMO END ------------------" )
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
