local BaseComponent = require "BaseComponent"
local app = require "lib"
local Vector2 = require "Vector2"
local Utilities = require "Utilities"
local System = require "System"
local Collider = BaseComponent:new()

function Collider:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	o.collider_ptr = nil
	return o
end

function Collider:init()
	
end

function Collider:setActive(b)
	app.collider_set_active(self.collider_ptr,b)
end

function Collider:addForce(x,y)
	app.collider_add_force(self.collider_ptr,x,y)
end

function Collider:addForceV(vector)
	app.collider_add_force(self.collider_ptr,vector.x,vector.y)
end

--"STATIC_RIGIDBODY""RIGIDBODY""GHOST""NO_PHYSICS"
function Collider:resetType(type)
	
	if type=="STATIC_RIGIDBODY" then
		app.collider_reset_body_type(self.collider_ptr,2)
	elseif type=="RIGIDBODY" then
		app.collider_reset_body_type(self.collider_ptr,1)
	elseif type=="GHOST" then
		app.collider_reset_body_type(self.collider_ptr,4)
	elseif type=="NO_PHYSICS" then
		app.collider_reset_body_type(self.collider_ptr,3)
	end
	
end

function Collider:internal_init(sprite_ptr)
	self.collider_ptr = app.collider_create(sprite_ptr)
end

function Collider:game_init()
	
end

function Collider:update(dt)

end

function Collider:game_exit()

end

function Collider:exit()

end



return Collider