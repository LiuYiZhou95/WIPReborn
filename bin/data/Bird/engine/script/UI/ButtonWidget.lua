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
local ButtonWidget = UIBase:new()

function ButtonWidget:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	o.callback = nil
	return o
end

function ButtonWidget:init(path_down,path_move,path_normal,callback)
	self.ptr = app.button_create()
	app.button_init_button(self.ptr,path_down,path_move,path_normal,nil)
	
end

function ButtonWidget:update_button(x,y)
	app.button_update_button(self.ptr,x,y)
end

function ButtonWidget:setCallback(callback)
	self.callback = callback
end

function ButtonWidget:setCallObject(object)
	self.object = object
end

function ButtonWidget:update(dt)
	app.button_update(self.ptr,dt)
	local s = app.button_get_callback_state(self.ptr)
	if s==true then
		if self.callback~=nil then
			self.callback(self,self.object)
		end
		app.button_set_callback_state(self.ptr,false)
	end
end

function ButtonWidget:forceCallback()
	if self.callback~=nil then
		self.callback(self,self.object)
	end
end

function ButtonWidget:setPosition(x,y)
	app.button_set_position(self.ptr,x,y)
end

function ButtonWidget:setSize(w,h)
	app.button_set_size(self.ptr,w,h)
end

return ButtonWidget