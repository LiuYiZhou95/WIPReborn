local BaseComponent = require "BaseComponent"
local app = require "lib"
local Input = require "Input"
local Utilities = require "Utilities"
local System = require "System"
local Drag = BaseComponent:new()

function Drag:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here

	return o
end

function Drag:init()

end

function Drag:game_init()

end

function Drag:update(dt)



end

function Drag:game_exit()

end

function Drag:exit()

end



return Drag