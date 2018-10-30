local Rect = require "Rect"
local Vector2 = require "Vector2"
local BaseComponent = require "BaseComponent"
local app = require "lib"

local Camera = BaseComponent:new()

local function _create_internal_rect(rect)
	return app.create_internal_rect(rect.lt.x,rect.lt.y,rect.rb.x-rect.lt.x,rect.rb.y-rect.lt.y)
end

local function _delete_internal_rect(rect_ptr)
	app.delete_internal_rect(rect_ptr)
end

local function _resize_internal_rect(rect_ptr,rect)
	app.resize_internal_rect(rect_ptr,rect.lt.x,rect.lt.y,rect.rb.x-rect.lt.x,rect.rb.y-rect.lt.y)
end

function Camera:new1()
	local o = {}
	setmetatable(o,self)
	self.__index = self 
	print('Create a Camera\n')

	
	o.rect = Rect:new()
	o.rect_ptr = _create_internal_rect(o.rect)
	return o
end

function Camera:get_rect()
	self.rect:out()
end

function Camera:set_rect(x,y,w,h)
	self.rect:set_with_size(x,y,w,h)
	_resize_internal_rect(self.rect_ptr,self.rect)
end

function Camera:delete()
	_delete_internal_rect(self.rect_ptr)
	self.rect = nil
	self.rect_ptr = nil
end

--the only __gc implementation is in c++
function __gc()
	--self:delete()
end

function Camera:Base()
	print('Camera instead of Base...')
end

function Camera:init()
	
end

function Camera:game_init()
	
end

function Camera:update(dt)
	
end

function Camera:game_exit()
	
end

function Camera:exit()
	
end

return Camera

