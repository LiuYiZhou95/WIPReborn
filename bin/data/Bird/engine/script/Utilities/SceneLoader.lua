local xml = require "XMLParser"
local GameObject = require "GameObject"
--local Transform = requre "Transform"
local Animation = require "Animation"
local Collider = require "Collider"
local Mesh = require "Mesh"
local app = require "lib"
local System = require "System"
local Texture = require "Texture"
local UI = require "UIMaster"
local ButtonWidget = require "ButtonWidget"
local PictureWidget = require "PictureWidget"
local StaticText = require "StaticText"
local SwitchWidget = require "SwitchWidget"
local TouchWidget = require "TouchWidget"
local ScrollerWidget  = require "ScrollerWidget"
local BasePanel = require "BasePanel"

local SceneLoader = {}

function SceneLoader.get_wip_node(str)
	return xml.get_node_val(".wip.scene."..str)
end

function SceneLoader.get_go_total()
	return SceneLoader.get_wip_node("total")
end

function SceneLoader.get_go_type(n)
	return SceneLoader.get_wip_node("e"..tostring(n)..".type")
end
--param the n-th object
--n is a number
function SceneLoader.get_go_active(n)
	return SceneLoader.get_wip_node("e"..tostring(n)..".active")
end

function SceneLoader.get_go_name(n)
	return SceneLoader.get_wip_node("e"..tostring(n)..".name")
end

--n is a string
function SceneLoader.get_go_transform(n,element)
	return SceneLoader.get_wip_node("e"..n..".Transform."..element)
end

function SceneLoader.get_go_animation(n,element)
	return SceneLoader.get_wip_node("e"..n..".Animation."..element)
end

function SceneLoader.get_go_collider(n,element)
	return SceneLoader.get_wip_node("e"..n..".Collider."..element)
end

function SceneLoader.get_go_mesh(n,element)
	return SceneLoader.get_wip_node("e"..n..".Mesh."..element)
end

function SceneLoader.get_go_components(n,element)
	return SceneLoader.get_wip_node("e"..n..".components."..element)
end

function SceneLoader.get_go_sprite(n,element)
	return SceneLoader.get_wip_node("e"..n..".Sprite."..element)
end

--return lua Mesh Component
function SceneLoader.load_component_mesh(n)
	local mesh = Mesh:new()
	local cx = SceneLoader.get_go_mesh(n,"cx")
	local cy = SceneLoader.get_go_mesh(n,"cy")
	local w = SceneLoader.get_go_mesh(n,"w")
	local h = SceneLoader.get_go_mesh(n,"h")
	mesh:internal_init(w,h)
	--local mesh_ptr = app.mesh_create(w,h)
	mesh:set_anchor(cx,cy)
	return mesh
end

--first init return sprite_ptr
function SceneLoader.load_component_sprite(n)
	--local mesh = SceneLoader.load_component_mesh()
	local sprite_ptr = app.create_sprite(0,0)
	local s = "texture"
	local texture_path = SceneLoader.get_go_sprite(n,s)
	if texture_path ~= nil then
		local texture = Texture:new(texture_path)
		app.sprite_set_sataic_texture(sprite_ptr,texture.texture_ptr)
	else
		print("NOTE:An empty object!")
	end
	return sprite_ptr
end

function SceneLoader.load_component_transform(n,sprite_ptr)
	local ctransform = System.genertate_component_by_name("Transform")()
	local x = SceneLoader.get_go_transform(n,"x")
	local y = SceneLoader.get_go_transform(n,"y")
	app.sprite_set_position(sprite_ptr,x,y)
	local rad = SceneLoader.get_go_transform(n,"rad")
	app.sprite_rotate(sprite_ptr,rad)
	local sx = SceneLoader.get_go_transform(n,"sx")
	local sy = SceneLoader.get_go_transform(n,"sy")
	app.sprite_scale_to(sprite_ptr,sx,sy)
	local z = SceneLoader.get_go_transform(n,"z_order")
	app.sprite_set_zorder(sprite_ptr,z)
	return ctransform
end

function SceneLoader.load_component_animation(n)
	local animation = Animation:new()
	return animation
end

function SceneLoader.load_component_collider(n)
	local collider = Collider:new()
	return collider
end



function SceneLoader.load_component_custom(ns,go,components_name_array)
	for i=1,#components_name_array do
		local name = components_name_array[i]
		local c = System.genertate_component_by_name(name)()
		local data = {}
		local n = SceneLoader.get_go_components(ns,name..".n")
		for j=1,n do
			local na = SceneLoader.get_go_components(ns,name..".e"..tostring(j))
			data[na] = SceneLoader.get_go_components(ns,name.."."..na)
		end
		c:load_data(data)
		c:init()
		go:add_component(name,c)
	end
end



function SceneLoader.load_button(x,y,w,h,ns)
	
	--local ui = System.genertate_component_by_name("ButtonWidget")()
	local ui = ButtonWidget:new()
	local down = SceneLoader.get_wip_node("e"..ns..".down_path")
	local normal = SceneLoader.get_wip_node("e"..ns..".normal_path")
	local up = SceneLoader.get_wip_node("e"..ns..".up_path")
	
	ui:init(down,up,normal,nil)
	ui:setPosition(x,y)
	return ui
end

function SceneLoader.load_scroller(x,y,w,h,ns)
	
	--local ui = System.genertate_component_by_name("ScrollerWidget")()
	local ui = ScrollerWidget:new()
	
	local bar = SceneLoader.get_wip_node("e"..ns..".bar_path") 
	local con = SceneLoader.get_wip_node("e"..ns..".con_path")
	
	if bar==nil or con==nil then
		ui:init("","")
	else
		ui:init(bar,con)
	end
	ui:setPosition(x,y)
	
	return ui
	
end

function SceneLoader.load_picture(x,y,w,h,ns)
	local ui = PictureWidget:new()
	local path = SceneLoader.get_wip_node("e"..ns..".pic_path")
	ui:init(x,y,w,h,path)
	return ui
end

--!
function SceneLoader.load_switch()

end
--!
function SceneLoader.load_touch()

end
--!
function SceneLoader.load_basepanel()
	
end


function SceneLoader.load_scene(file)
		--g_game_objcts
	local scene_ptr = app.scene_create()
	local go_pak = {}
	xml.loadxml(file)
	local go_n = SceneLoader.get_go_total()
	for i=1,go_n do 
		local ns = tostring(i)
		if SceneLoader.get_go_type(i)=="object" then
			--n-th object creating
			
			local sprite_ptr = SceneLoader.load_component_sprite(ns)
			local cmesh = SceneLoader.load_component_mesh(ns)
			local ctransform = SceneLoader.load_component_transform(ns,sprite_ptr)
			local canimation = SceneLoader.load_component_animation(ns)
			local ccollider = SceneLoader.load_component_collider(ns)
		
			local go = GameObject:new()
			local name = SceneLoader.get_go_name(i)
		
			canimation:internal_init(sprite_ptr)
		
			go:init(sprite_ptr,name)
			go:set_active(SceneLoader.get_go_active(i))
			
			go:add_mesh(cmesh)
			go:add_animation(canimation)
			ccollider:internal_init(sprite_ptr)
			ccollider:setActive(SceneLoader.get_go_collider(ns,"active"))
			ccollider:resetType(SceneLoader.get_go_collider(ns,"type"))
			
			go:add_collider(ccollider)
		
			go:add_transform(ctransform)
		
		
		
			--load custom components
			local names = {}
			local cn = SceneLoader.get_go_components(ns,"n")
			for i=1,cn do
				local name = SceneLoader.get_go_components(ns,"e"..tostring(i))
				table.insert(names,name)
			end
			SceneLoader.load_component_custom(ns,go,names)
		
			app.scene_add_object(scene_ptr,go.sprite_ptr)
			table.insert(go_pak,go)
		
		
		elseif SceneLoader.get_go_type(i)=="ui" then
		
			local name = SceneLoader.get_wip_node("e"..ns..".name")
			local uitype = SceneLoader.get_wip_node("e"..ns..".ui")
			
			local x = SceneLoader.get_wip_node("e"..ns..".x")
			local y = SceneLoader.get_wip_node("e"..ns..".y")
			local w = SceneLoader.get_wip_node("e"..ns..".w")
			local h = SceneLoader.get_wip_node("e"..ns..".h")
			
			local uiret = nil
			
			if uitype=="PictureWidget" then
				uiret = SceneLoader.load_picture(x,y,w,h,ns)
			elseif uitype=="ButtonWidget" then
				uiret = SceneLoader.load_button(x,y,w,h,ns)
			elseif uitype=="ScrollerWidget" then
				uiret = SceneLoader.load_scroller(x,y,w,h,ns)
			end
			
			uiret.name = name
			
			app.scene_add_ui(scene_ptr,uiret.ptr)
			
			UI.addObject(uiret)
		end

	end
				local scenepak = {}
			scenepak.scene_ptr = scene_ptr
			scenepak.objects = go_pak
			table.insert(g_running_scenes,scenepak)
end

function SceneLoader.unload_scene(scene_ptr)
	app.scene_unload(scene_ptr)
end

return SceneLoader