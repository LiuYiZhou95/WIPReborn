--[[
	This class used for makeing all the ui objects work
	NOTE:All the objects hava gc,check the reference.
--]]
local System = require "System"
local app = require "lib"
local ButtonWidget = require "ButtonWidget"
local PictureWidget = require "PictureWidget"
local StaticText = require "StaticText"
local SwitchWidget = require "SwitchWidget"
local TouchWidget = require "TouchWidget"
local ScrollerWidget  = require "ScrollerWidget"
local ScrollerWidget  = require "ScrollerWidget"
local BasePanel = require "BasePanel"

local UI = {
	--Store all the working ui objects
	objects = {},
	n = 0
}



--[[
	param:type - the type of ui object you want to create
	not in use
--]]
function UI.create_ui(type)
	local ret = nil
	if type=="Button" then
		ret = ButtonWidget:new()
	elseif type=="Picture" then
		ret = PictureWidget:new()
	elseif type=="Text" then
		ret = StaticText:new()
	elseif type=="Switch" then
		ret = SwitchWige:new()
	elseif type=="Touch" then
		ret = TouchWidget:new()
	elseif type=="Scroller" then
		ret = ScrollerWidget:new()
	elseif type=="BasePanel" then
		ret = BasePanel:new()
	end
	UI.addObject(ret)
end

--use object name to index the object
function UI.addObject(object)
	if UI.objects[object.name]==nil then
		UI.objects[object.name] = object
		UI.n = UI.n + 1
	else
		print("The UI object called:"..object.name.." is already exist!")
	end
end

function UI.removeObjectByName(name)
	if UI.objects[name]~=nil then
		UI.objects[name] = nil
	end
end

function UI.getObjectByName(name)
	return UI.objects[name]
end

function UI.clear()
	UI.objects = {}
end

function UI.update(dt)
	if UI.objects=={} then
		return
	end
	for key, value in pairs(UI.objects) do
		if value~=nil then
			if value.active==true then
				value:update()
			end
		end
	end  
end

return UI