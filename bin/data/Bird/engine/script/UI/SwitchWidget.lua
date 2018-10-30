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
local SwitchWidget = UIBase:new()

function SwitchWidget:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	o.callback = nil
	return o
end

function SwitchWidget:init(path_check,path_uncheck,callback)
	self.ptr = app.switch_create()
	app.switch_init_button(self.ptr,path_check,path_uncheck,path_uncheck,nil)
end

function SwitchWidget:update(dt)
	app.switch_update(self.ptr,dt)
	local s = app.switch_get_callback_state(self.ptr)
	if s==true then
		if self.callback~=nil then
			self.callback(self,self.object)
		end
		app.switch_set_callback_state(self.ptr,false)
	end
end

function SwitchWidget:forceCallback()
	if self.callback~=nil then
		self.callback(self,self.object)
	end
end

function SwitchWidget:update_button(x,y)
	app.switch_update_button(self.ptr,x,y)
end

function SwitchWidget:setCallback(callback)
	self.callback = callback
end

function SwitchWidget:setCallObject(object)
	self.object = object
end

function SwitchWidget:setPosition(x,y)
	app.switch_set_position(self.ptr,x,y)
end

--x,y may be nil in most cases
function SwitchWidget:reshape(w,h,x,y)
	
end

function SwitchWidget:setSwitchState(val)
	app.switch_set_switch_state(self.ptr,val)
end

function SwitchWidget:getSwitchState()
	return app.switch_get_switch_state(self.ptr)
end

return SwitchWidget