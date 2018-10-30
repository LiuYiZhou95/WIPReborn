local BaseComponent = require "BaseComponent"
local app = require "lib"

local Utilities = require "Utilities"
local System = require "System"
local Mesh = BaseComponent:new()

function Mesh:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	o.mesh_ptr = nil
	return o
end

function Mesh:internal_init(w,h)
	self.mesh_ptr = app.mesh_create(w,h)
end

function Mesh:get_anchor()
	return app.mesh_get_anchor(self.mesh_ptr)
end

function Mesh:set_anchor(percent_x,percent_y)
	app.mesh_set_anchor(self.mesh_ptr,percent_x,percent_y)
end

function Mesh:set_size(w,h)
	app.mesh_set_size(self.mesh_ptr,w,h)
end

function Mesh:get_size()
	return app.mesh_get_size(self.mesh_ptr)
end

function Mesh:init()

end

function Mesh:game_init()

end

function Mesh:update(dt)

end

function Mesh:game_exit()

end

function Mesh:exit()

end



return Mesh