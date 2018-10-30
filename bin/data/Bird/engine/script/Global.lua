--[[
		These table cache scene like this:
		scene = 
		{
			scene_ptr,
			objects = {}
		}
--]]

--[[
--cache scene by user
--functions:
	push_scene(scene):push the specified scene to g_cache_scene
	push_current_scene():push the last scene in the g_running_scene to g_cache_scene
	pop_scene():push the last scene in the g_cache_scene to g_running_scene
	pop_the_scene(scene_ptr):push the specified scene int the g_cache_scene to g_running_scene
	
--]]
g_cache_scenes = {}
g_running_scenes = {}
--just for test
g_game_objects = {}
