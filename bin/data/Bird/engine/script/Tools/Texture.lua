local app = require "lib"
local Texture = {}

function Texture:new(path)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	o.texture_ptr = app.texture_create(path,-1,-1)
	return o
end

return Texture
