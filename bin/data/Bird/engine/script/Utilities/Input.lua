local lib = require "lib"

local Input = {}

--[[
	get_key(key_string,key_state)
	get_sys_key(key_string,key_state)
	
	--key_string:
	"f1""f2""f3""f4""f5""f6""f7""f8""f9""f10""f11""f12"
	"esc""backspace""enter""rshift""lshift""lctrl""rctrl"
	"lalt""ralt""tab""up""down""left""right""space"
	"lmouse""rmouse""mmouse""scrollerup""scrollerdown"
	"a" "b" "c"	"d""e""f""g""h""i""j""k""l""m""n""o""p"
	"q""r""s""t""u""v""w""x""y""z"
	--key_state:
	0 for pressed,1 for pressing,2 for released
	--return:
	bool
--]]

function Input.get_sys_key(key_string,key_state)
	return lib.get_sys_key(key_string,key_state)
end

function Input.get_key(key_string,key_state)
	return lib.get_key(key_string,key_state)
end

function Input.is_mose_move()
	return lib.is_mouse_move()
end

return Input
