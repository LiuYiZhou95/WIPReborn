

local BaseComponent = 
{
	
}

function BaseComponent:new(o)

	print('Base')
	local o = o or {}
	--对于表，只是传递地址拷贝
	setmetatable(o,self)
	self.__index = self
	o.host_obj = nil
	return o
end

function BaseComponent:load_data(data_array)
	--Add code to load data here.
end

--called when added to GameObject by GameObject
function BaseComponent:bind_host(host_obj)
	self.host_obj = host_obj
end

function BaseComponent:get_host()
	return self.host_obj
end

function BaseComponent:init()
	--print('[BaseComponent]:System init...')
end

function BaseComponent:game_init()
	--print('[BaseComponent]:Game init...')
end

function BaseComponent:update(dt)
	--print('[BaseComponent]:update...')
end

function BaseComponent:draw(dt)
   --print('[BaseComponent]:debug_draw')
end

function BaseComponent:game_exit()
	--print('[BaseComponent]:Game exit...')
end

function BaseComponent:exit()
	--print('[BaseComponent]:System exit...')
end

function BaseComponent:Base()
	--print('BaseComponent...')
end

return BaseComponent

