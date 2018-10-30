local app = require "lib"

local Utilities = {}


function Utilities.is_nil( value ) return type(value)=='nil' end
function Utilities.is_boolean( value ) return type(value)=='boolean' end
function Utilities.is_number( value ) return type(value)=='number' end
function Utilities.is_string( value ) return type(value)=='string' end
function Utilities.is_table( value ) return type(value)=='table' end
function Utilities.is_function( value ) return type(value)=='function' end
function Utilities.is_thread( value ) return type(value)=='thread' end
function Utilities.is_userdata( value ) return type(value)=='userdata' end
	
return Utilities