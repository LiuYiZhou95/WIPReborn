local BaseComponent = require "BaseComponent"
local Vector2 = require "Vector2"

local app = require "lib"

--this component is noly a set of tranform methods instead of a wrap of c++ object
local Transform = BaseComponent:new()

function Transform:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self
	
	
	return o
end

--[[
		Transform API
--]]
--return the first object use this name and the number of objects which uses this name
function Transform.findWithName(object_name)
	local ret = nil
	local n = 0
	for i=1,#g_running_scenes do
		for j=1,#g_running_scenes[i].objects do
			if g_running_scenes[i].objects[j].name==object_name then 
			
				if n==0 then
					ret = g_running_scenes[i].objects[j]
				end
				n = n + 1
			end
		end
	end
	return ret,n
end


function Transform.findWithID(id)
	local ret = nil
	for i=1,#g_running_scenes do
		for j=1,#g_running_scenes[i].objects do
			if g_running_scenes[i].objects[j].id==id then 
				ret = g_running_scenes[i].objects[j]
			end
		end
	end
	return ret
end

function Transform:getZOder()
	return app.sprite_get_zorder(self.host_obj.sprite_ptr)
end

function Transform:setZOder(z)
	app.sprite_set_zorder(self.host_obj.sprite_ptr,z)
end

function Transform:getAnchor()
	local x,y = app.sprite_get_anchor(self.host_obj.sprite_ptr)
	return Vector2:new(x,y)
end

function Transform:setAnchor(percent_x,percent_y)
	app.sprite_set_anchor(self.host_obj.sprite_ptr,percent_x,percent_y)
end

function Transform:getFoward()
	local rotation = app.sprite_get_rotation(self.host_obj.sprite_ptr)
	rotation = rotation + math.pi / 2
	return Vector2:new(math.cos(rotation),math.sin(rotation))
end

function Transform:rotate(rad)
	app.sprite_rotate(self.host_obj.sprite_ptr,rad)
end

function Transform:move(dx,dy)
	app.sprite_translate(self.host_obj.sprite_ptr,dx,dy)
end

function Transform:scale(sx,sy)
	app.sprite_scale(self.host_obj.sprite_ptr,sx,sy)
end

function Transform:moveVector(vector)
	app.sprite_translate(self.host_obj.sprite_ptr,vectoer.x,vector.y)
end

function Transform:scaleVector(vector)
	app.sprite_scale(self.host_obj.sprite_ptr,sxvectoer.x,vector.y)
end

function Transform:getPosition()
	local x,y = app.sprite_get_position(self.host_obj.sprite_ptr)
	return x,y
end

function Transform:setPosition(x,y)
	app.sprite_set_position(self.host_obj.sprite_ptr,x,y)
end

--param Transform
function Transform:lookAt(target)
	local pos = target:getPosition()
	local vs = Transform:getFoward()
	local vo = Vector2.getDiff(self:getPosition(),pos)
	local rad = Vector2.getAngle(vs,vo)
	self:rotate(-rad)
end

--param Vector2
function Transform:lookAtPos(targetPos)
	local vs = Transform:getFoward()
	local vo = Vector2.getDiff(self:getPosition(),targetPos)
	local rad = Vector2.getAngle(vs,vo)
	self:rotate(-rad)
end

--param axis Vector2
function Transform:rotateBy(rad,axis)
	local x,y = app.get_sprite_position(self.host_obj.sprite_ptr)
	x = x - axis.x
	y = y - axis.y
	x,y = Vector2.rotatePoint(x,y,rad)
	x = x + axis.x
	y = y + axis.y
	app.sprite_set_position(self.host_obj.sprite_ptr,x,y)
end

function Transform:moveToVector(v)
	app.sprite_set_position(self.host_obj.sprite_ptr,v.x,v.y)
end

function Transform:moveTo(x,y)
	app.sprite_set_position(self.host_obj.sprite_ptr,x,y)
end

function Transform:rotateTo(rad)
	app.sprite_rotate2(self.host_obj.sprite_ptr,rad)
end

function Transform:scaleToVector(v)
	
end

function Transform:scaleTo(sx,sy)
	
end

function Transform:rotateByTo(rad,axis)

end

--[[
		Interpolation methods
--]]
function Transform:moveToVectorInterp(v,time)
	
end

function Transform:moveToInterp(x,y,time)

end

function Transform:rotateToInterp(rad,time)

end

function Transform:scaleToInterpVector(v,time)
	
end

function Transform:scaleToInterp(sx,sy,time)
	
end

function Transform:rotateByToInterp(rad,axis,time)

end

--[[
		System
--]]
function Transform:init()
	
end

function Transform:game_init()
	
end

function Transform:update(dt)
	--update interpolation
end

function Transform:game_exit()
	
end

function Transform:exit()
	
end


return Transform