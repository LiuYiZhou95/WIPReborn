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
local PictureWidget = UIBase:new()

function PictureWidget:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

function PictureWidget:init(x,y,w,h,path_image)
	self.ptr = app.picture_create(x,y,w,h)
	app.picture_static_init(self.ptr,path_image)
end

function PictureWidget:update(dt)
	app.picture_update(self.ptr,dt)
end

function PictureWidget:resetPicture(path_picture)
	app.picture_reset_picture(self.ptr,path_picture)
end

function PictureWidget:setPosition(x,y)
	app.picture_set_position(self.ptr,x,y)
end

--x,y may be nil in most cases
function PictureWidget:reshape(w,h,x,y)
	app.picture_reshape(self.ptr,w,h,x,y)
end

return PictureWidget