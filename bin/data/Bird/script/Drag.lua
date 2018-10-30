local BaseComponent = require "BaseComponent"
local app = require "lib"
local Input = require "Input"
local Utilities = require "Utilities"
local System = require "System"
local Drag = BaseComponent:new()
local SceneLoader = require "SceneLoader"

function Drag:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	o.camera = nil

	return o
end

function Drag:init()

end

function Drag:game_init()
	self.camera = camera
	--app.sprite_set_position(self.host_obj.sprite_ptr,0,0)
	app.collider_set_density(self.host_obj.Collider.collider_ptr,0.001)
end
--buggy codestyle 
--this may make every instance of this component share a same value
local px = 0
local py = 0
function Drag:update(dt)
	if Input.get_sys_key("rmouse",0) then 
		self.host_obj.Collider:addForce(0,10000)
	end
	--for test
	local ox,oy = app.camera_get_world(self.camera.camera_ptr)
	local x,y;
	if Input.is_mose_move() then
	if not Input.get_sys_key("lmouse",0) then
	if Input.get_sys_key("lmouse",1) then 
		x,y = app.get_mouse_position()
		--translate to world
		app.sprite_translate(self.host_obj.sprite_ptr,(x-px),(py-y))
	end
	end
	end
	local xx,yy = app.sprite_get_position(self.host_obj.sprite_ptr);
	px,py = app.get_mouse_position()
	app.sprite_set_position(self.host_obj.sprite_ptr,130,yy)

	if not app.collider_is_collision_empty(self.host_obj.Collider.collider_ptr) then
		print("you lost!")	
		print("try again!")
		SceneLoader.unload_scene(g_running_scenes[1].scene_ptr)
		SceneLoader.load_scene("./resources/flappy/scene.xml")
			local ns = #g_running_scenes
	for i=1,ns do
		for j=1,#g_running_scenes[i].objects do
			g_running_scenes[i].objects[j]:game_init()
		end
	end
		--continue = false
	end
	

	
	local vx,vy = app.collider_get_speed(self.host_obj.Collider.collider_ptr)
	if vy>0 then
		self.host_obj.Transform:rotateTo(31.415/180)
	end
	if vy<0 then
		self.host_obj.Transform:rotateTo(-31.415/180)
	end
end

function Drag:game_exit()

end

function Drag:exit()

end

return Drag