local BaseComponent = require "BaseComponent"
local app = require "lib"

local Utilities = require "Utilities"
local System = require "System"
local ParticleEmitter = BaseComponent:new()

function ParticleEmitter:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here

	return o
end

function ParticleEmitter:load_data(data_array)
	--Add code to load data here.
end

function ParticleEmitter:init()

end

function ParticleEmitter:game_init()

end

function ParticleEmitter:update(dt)

end

function ParticleEmitter:game_exit()

end

function ParticleEmitter:exit()

end



return ParticleEmitter