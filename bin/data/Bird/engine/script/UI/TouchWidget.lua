local app = require "lib"
local ButtonWidget = require "ButtonWidget"

--[[
this class has __gc
and
callback is called in lua due to callback state
callback state decid if to call the callback 
and 
maybe if to draw the button is decided in lua
--]]
local TouchWidget = ButtonWidget:new()

function TouchWidget:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

function TouchWidget:init(x,y,w,h,path_inmage)

end

function TouchWidget:setBackground(path_bg)
	
end

function TouchWidget:setFont(path_font)
	
end

function TouchWidget:addPanel(panel)

end

function TouchWidget:addWidget()
	
end

function TouchWidget:getWidgetByName(name)
	
end

function TouchWidget:update(dt)

end

function TouchWidget:setPosition(x,y)
	
end

--x,y may be nil in most cases
function TouchWidget:reshape(w,h,x,y)
	
end

return TouchWidget