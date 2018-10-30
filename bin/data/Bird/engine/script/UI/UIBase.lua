local UIBase = {}

function UIBase:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	o.active = true
	o.name = "NONAME"
	o.ptr = nil
	o.object = nil
	return o
end

return UIBase