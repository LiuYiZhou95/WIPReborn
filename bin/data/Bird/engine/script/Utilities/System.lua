--[[
		System functions
--]]
local app = require "lib"
local utilities = require "Utilities"
local xml = require "XMLParser"
--local GameObject = require "GameObject"



local System = 
{
	ids = {},
	cur_id_size = 0,
	--most object number
	max = 1000
}

function System.init()
	for i = 1,System.max do
		table.insert(System.ids,i)
		System.cur_id_size = System.cur_id_size + 1
	end
end

function System.put(str)
	print(tostring(str))

end

function push_scene(scene)
	table.insert(g_cache_scenes,scene)
end

function System.push_current_scene()
	local scene = g_running_scenes[#g_running_scenes]
	table.insert(g_cache_scenes,scene)
end

function System.pop_scene()
	local scene = g_cache_scenes[#g_cache_scenes]
	table.insert(g_running_scenes,scene)
	table.remove(g_cache_scenes)
end

function System.remove_current_scene()
	app.scene_unload(g_running_scenes[1].scene_ptr)
	g_running_scenes = {}
	UI.clear()
end

function System.pop_the_scene(scene_ptr)
	--[[
	local scene = nil
	local n = -1
	for i=1,#g_cache_scenes do
		for j=1,#g_cache_scenes[i].objects do 
			if g_cache_scenes[i].objects[j].scene_ptr==scene_ptr then 
				scene = g_cache_scenes[i].objects[j]
				n = i
				break
			end
		end
	end
	if scene ~= nil then
		push_scene(scene)
		table.remove(g_cache_scenes,n)
	end	
		--]]
end

function System.clear_scene_cache()
	--[[
	local i = #g_cache_scenes 
	while i>0 do
		local j = #g_cache_scenes[i].objects
		while j>0 do 
			app.delete_sprite(g_cache_scenes[i].objects[j].sprite_ptr)
			g_cache_scenes[i].objects[j] = nil
			j = j - 1
		end
		app.scene_delete(g_cache_scenes[i].scene_ptr)
		g_cache_scenes[i].objects = nil
		g_cache_scenes[i] = nil
		--or table.remove ?
		i = i - 1
	end
	--]]
end




function System.genertate_component_by_name(component_name)
	s = "local _ = require \""..component_name.."\";return _:new()"
	return loadstring(s)
end

--生成id
function System.generate_id(obj)
--[[
	local ret = -1
	if System.cur_id_size>0 then
		ret = System.ids[System.cur_id_size]
		System.cur_id_size = System.cur_id_size - 1
		table.remove(System.ids)
	else
		print("ERROR:NO ID TO GENERATE!")
		ret = nil
	end
	
	return ret
--]]
	return app.generate_id(obj)
end

--回收id
function System.recycle_id(id)
--[[
	if utilities.is_number(id) and id>0 and id<=System.max then
		table.insert(System.ids,id)
		System.cur_id_size = System.cur_id_size + 1
		if System.cur_id_size>System.max then
			print("ERROR:ID BECOMES MORE!")
		end
	else
		return
	end
--]]

end

return System