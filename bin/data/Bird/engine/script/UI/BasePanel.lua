local app = require "lib"
local UIBase = require "UIBase"

--[[
this class has __gc
and
callback is called in lua due to callback state
callback state decid if to call the callback 
and 
maybe if to draw the button is decided in lua
--]]
local BasePanel = UIBase:new()

function BasePanel:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

function BasePanel:init(x,y,w,h,path_inmage)

end

function BasePanel:setBackground(path_bg)
	
end

function BasePanel:setFont(path_font)
	
end

function BasePanel:addPanel(panel)

end

function BasePanel:addWidget()
	
end

function BasePanel:update(dt)

end

function BasePanel:setPosition(x,y)
	
end

--x,y may be nil in most cases
function BasePanel:reshape(w,h,x,y)
	
end

return BasePanel