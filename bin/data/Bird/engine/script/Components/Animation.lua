local BaseComponent = require "BaseComponent"
local app = require "lib"

local Utilities = require "Utilities"
local System = require "System"
local Animation = BaseComponent:new()

function Animation:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	o.animation_ptr = nil
	return o
end

function Animation:internal_init(sprite_ptr)
	self.animation_ptr = app.animation_create(sprite_ptr)
end

function Animation:play(clip)
	app.animation_play(self.animation_ptr,clip.clip_ptr)
end

function Animation:init()

end

function Animation:game_init()

end

function Animation:update(dt)

end

function Animation:game_exit()

end

function Animation:exit()

end



return Animation