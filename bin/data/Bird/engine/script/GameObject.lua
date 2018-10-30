local Camera = require "Camera"
local System = require "System"
local app = require "lib"


local GameObject = 
{
	
}

function GameObject:new(o)

	--print('GameObj')
	local o = o or {}
	--??????????????????
	setmetatable(o,self)
	self.__index = self
	o.active = true
	o.components = {}
	o.name = "NONAME"
	--we can use sprite_ptr for id
	o.sprite_ptr = nil
	o.id = nil
	o.Transform = nil
	o.Animation = nil
	o.Collider = nil
	o.Mesh = nil
	return o
end

function GameObject:init(sprite_ptr,name)
	if sprite_ptr~=nil then
		self:set_name(name)
		self.sprite_ptr = sprite_ptr
		self.id = sprite_ptr
	else
		error("Create a nil Object!")
	end
end
--[[
function GameObject:set_static_texture(texture_path)
	app.sprite_set_sataic_texture(texture_path)
end
--]]
function GameObject:set_active(val)
	self.active = val
end

function GameObject:set_name(name)
	self.name = name
end

function GameObject:add_component(name,component)
	component:bind_host(self)
	self.components[name] = component
	--this enable the form go.costum_component to call Component
	self[name] = component
end

function GameObject:get_component(name)
	--return self.components[name]
	local r = self[name]
	if r==nil then
		print("There is no component called "..name.."on "..self.name.." id:"..tostring(self.id))
	end
	return r
end

--fixed component add
function GameObject:add_mesh(mesh)
	self.Mesh = mesh
	mesh:bind_host(self)
	app.sprite_attach_mesh(self.sprite_ptr,mesh.mesh_ptr)
end

function GameObject:add_transform(ctransform)
	self.Transform = ctransform
	ctransform:bind_host(self)
end

function GameObject:add_animation(animation)
	self.Animation = animation
	animation:bind_host(self)
	if animation.animation_ptr~=nil then
		app.sprite_attach_animation(self.sprite_ptr,animation.animation_ptr)
	end
end

function GameObject:add_collider(collider)
	self.Collider = collider
	collider:bind_host(self)
	app.sprite_attach_collider(self.sprite_ptr,collider.collider_ptr)
end

function GameObject:update(dt)
	for key, value in pairs(self.components) do
		self[key]:update(dt)
	end
end

function GameObject:draw(dt)
    for key, value in pairs(self.components) do
		self[key]:draw(dt)
	end
end

function GameObject:game_init()
	for key, value in pairs(self.components) do
		self.components[key]:game_init()
	end
end

function GameObject:game_exit()
	for key, value in pairs(self.components) do
		self.components[key]:game_exit()
	end
end

function GameObject:exit()
	for key, value in pairs(self.components) do
		self.components[key]:exit()
	end
end

return GameObject
