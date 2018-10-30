local app = require "lib"
local Vector2 = require "Vector2"
local GameObject = require "GameObject"

CameraObject = {}

function CameraObject:new(world_w,world_h)

	print('GameObj')
	local o = o or {}
	--??????????????????
	setmetatable(o,self)
	self.__index = self
	o.active = true
	o.name = ""
	--we can use sprite_ptr for id
	o.camera_ptr = app.camera_create(world_w,world_h)
	o.id = nil
	return o
end

function CameraObject:moveWorld(dx,dy)
	app.camera_move_world(self.camera_ptr,dx,dy)
end

function CameraObject:moveWorldTo(x,y)
	app.camera_move_world_to(self.camera_ptr,x,y)
end

function CameraObject:getWorldPosition()
	return app.camera_get_world_x(self.camera_ptr),app.camera_get_world_y(self.camera_ptr)
end

function CameraObject:getWorldSize()
	return app.camera_get_world_width(self.camera_ptr),app.camera_get_world_height(self.camera_ptr)
end

function CameraObject:moveScreen(dx,dy)
	app.camera_move_screen(self.camera_ptr,dx,dy)
end

function CameraObject:getScreenPosition()
	return app.camera_get_screen_x(self.camera_ptr),app.camera_get_screen_y(self.camera_ptr)
end

function CameraObject:getScreenSize()
	return app.camera_get_screen_width(self.camera_ptr),app.camera_get_screen_height(self.camera_ptr)
end

function CameraObject:moveScreenTo(x,y)
	app.camera_move_screen_to(self.camera_ptr,x,y)
end

function CameraObject:setScreenSize(w,h)
	app.camera_set_screen_size(self.camera_ptr,w,h)
end

function CameraObject:setWorldSize(w,h)
	app.camera_set_world_size(self.camera_ptr,w,h)
end

function CameraObject:copyFrom(other)
	app.camera_copy_from(self.camera_ptr,other.camera_ptr)
end

function CameraObject:set_active(val)
	app.camera_set_active(self.camera_ptr,val)
end

function CameraObject:active()
	return app.camera_get_active(self.camera_ptr)
end

--translate the position from world to camera
function CameraObject:world_to_camera(wx,wy)
	local cwx,cwy =  self:getWorldPosition()
	return wx-cwx,wy-cwy
end

function CameraObject:camera_to_world(cx,cy)
	local cwx,cwy = self:getWorldPosition()
	return cx+cwx,cy+cwy
end

function CameraObject:setName(name)
	self.name = name
end

return CameraObject