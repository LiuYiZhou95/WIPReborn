local BaseComponent = require "BaseComponent"
local app = require "lib"

local Utilities = require "Utilities"
local System = require "System"
local AudioListener = BaseComponent:new()

function AudioListener:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here

	return o
end

function AudioListener:load_data(data_array)
	--Add code to load data here.
end

function AudioListener:init()

end

function AudioListener:game_init()

end

function AudioListener:update(dt)

end

function AudioListener:game_exit()

end

function AudioListener:exit()

end



return AudioListener