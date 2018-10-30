local app = require "lib"
local AnimationClip = {}

function AnimationClip:new(name,atlas_path,texture)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	o.name = name
	o.texture = texture
	if texture~=nil then
		o.clip_ptr = app.clip_create(name,atlas_path,texture.texture_ptr)
	else
		o.clip_ptr = app.clip_create(name,atlas_path,nil)
	end
	
	return o
end

return AnimationClip
