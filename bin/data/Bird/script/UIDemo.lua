local BaseComponent = require "BaseComponent"
local app = require "lib"
local Transform = require "Transform"
local Utilities = require "Utilities"
local System = require "System"
local AnimationClip = require "AnimationClip"
local Texture = require "Texture"
local Input = require "Input"
local UI = require "UIMaster"
local ButtonWidget = require "ButtonWidget"
local Callbacks = require "callbacks"
local Vector2 = require "Vector2"

local Test1 = BaseComponent:new()

function Test1:new()
    local o = { }
    setmetatable(o, self)
    self.__index = self
    o.animation = nil
	
	
	o.vertex = {}
	o.index = {}
	o.sound = nil
	o.v = 1111
	
	o.buttonl = nil
	o.buttonr = nil
	o.scroller = nil
	o.text_pos1 = 600
	--400
	o.text_pos2 = 1300
	o.text_pos3 = 1300
	o.cur_page = nil
	o.page_direct = nil
	
	o.page_change_speed = 30
	o.finish1 = true
	o.finish2 = true
    return o
end

function Test1:draw(dt)
	
end

function Test1:game_exit()
	
end

return Test1