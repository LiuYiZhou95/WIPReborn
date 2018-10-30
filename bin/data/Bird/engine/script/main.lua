--require "init"
local UI = require "UIMaster"
local app = require "lib"
local GameObject = require "GameObject"
local Camera = require "Camera"
local Input = require "Input"
local System = require "System"
local SLAXML = require 'slaxml'
local xml = require 'XMLParser'
local Transform = require 'Transform'
local SceneLoader = require "SceneLoader"
local CameraObject = require "CameraObject"
local Config = require "config"


function init()
	local ret = Config.config()
	if ret==false then
		return ret
	end
	local ns = #g_running_scenes
	for i=1,ns do
		for j=1,#g_running_scenes[i].objects do
			g_running_scenes[i].objects[j]:game_init()
		end
	end
	return ret
end

function main_logic()
	local dt = app.system_get_dt()
	
	if continue then
		local ns = #g_running_scenes
		for i=1,ns do
			for j=1,#g_running_scenes[i].objects do
				g_running_scenes[i].objects[j]:update(dt)
			end
		end
	end
	
	UI.update(dt)
	
end

function debug_draw()
    local dt = app.system_get_dt()
    local ns = #g_running_scenes
	for i=1,ns do
		for j=1,#g_running_scenes[i].objects do
			g_running_scenes[i].objects[j]:draw(dt)
		end
	end
end


function main ()
	app.init()
	continue = init()
	if continue then
		app.run()
	end
	
end

--this function is not in use in c++ or lua
--so never called
function finalization()
	local ns = #g_running_scenes
	for i=1,ns do
		for j=1,#g_running_scenes[i].objects do
			g_running_scenes[i].objects[j]:game_exit()
			g_running_scenes[i].objects[j]:exit()
		end
	end
end



