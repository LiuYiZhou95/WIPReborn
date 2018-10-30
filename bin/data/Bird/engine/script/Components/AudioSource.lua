local BaseComponent = require "BaseComponent"
local app = require "lib"

local Input = require "Input"
local Utilities = require "Utilities"
local System = require "System"
local AudioSource = BaseComponent:new()

function AudioSource:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	
	return o
end

function AudioSource:load_data(data_array)
	--Add code to load data here.
end

function AudioSource:init()
		
end

function AudioSource:game_init()
	app.collider_set_density(self.host_obj.Collider.collider_ptr,20)
	
end



function AudioSource:update(dt)
	
	
end

function AudioSource:game_exit()

end

function AudioSource:exit()

end



return AudioSource