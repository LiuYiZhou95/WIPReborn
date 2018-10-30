local app = require "lib"
local UIBase = require "UIBase"

--[[
this class has __gc
and
callback is called in lua due to callback state
callback state decid if to call the callback 
and 
maybe if to draw the button is decided in lua
--]]
local ScrollerWidget = UIBase:new()

function ScrollerWidget:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

function ScrollerWidget:init(path_bar,path_controller)
	self.ptr = app.scroller_create()
	app.scroller_init(self.ptr,path_bar,path_controller)
	app.scroller_set_current_val(self.ptr,0)
end

function ScrollerWidget:update_button(x,y)
	app.scroller_update_button(self.ptr,x,y)
end

function ScrollerWidget:update(dt)
	app.scroller_update(self.ptr,dt)
end

function ScrollerWidget:setCurrentVal(val)
	app.scroller_set_current_val(self.ptr,val)
end

function ScrollerWidget:getCurrentVal()
	return app.scroller_get_current_val(self.ptr)
end

function ScrollerWidget:setControll(val)
	app.scroller_set_controll(self.ptr,val)
end

function ScrollerWidget:setPosition(x,y)
	app.scroller_set_position(self.ptr,x,y)
end

--x,y may be nil in most cases
function ScrollerWidget:reshape(w,h,x,y)
	print("Scroller can't reshape!")
end

return ScrollerWidget