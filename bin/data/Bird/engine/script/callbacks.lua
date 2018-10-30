local UI = require "UIMaster"
local System = require "System"

local Callbacks = {}

function Callbacks.buttoncall1(this)
	print(this.name)
end

return Callbacks