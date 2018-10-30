local Vector2 = require("Vector2")

local Rect = 
{

}

function Rect:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self 
	o.lt = Vector2:new(0,0)
	o.lb = Vector2:new(0,0)
	o.rb = Vector2:new(0,0)
	o.rt = Vector2:new(0,0)
	return o
end

--left top for x,y
function Rect:set_with_size(x,y,w,h)
	self.lt.x = x
	self.lt.y = y
	self.lb.x = x
	self.lb.y = y+h
	self.rb.x = x+w
	self.rb.y = y+h
	self.rt.x = x+w
	self.rt.y = y
end

function Rect:out()
	print()
	self.lt:out()
	self.lb:out()
	self.rb:out()
	self.rt:out()
	print()
end

function Rect:clear()
	self = nil
end

return Rect