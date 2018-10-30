local BaseComponent = require "BaseComponent"
local app = require "lib"
local Transform = require "Transform"
local Utilities = require "Utilities"
local System = require "System"
local Vector2 = require "Vector2"
local FlappyMaster = BaseComponent:new()

function FlappyMaster:new()
	local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	o.gsz = nil
	o.gsy = nil
	o.gxz = nil
	o.gxy = nil
	o.speed = 100
	o.bird = nil
	o.score = 0
	
	return o
end

function FlappyMaster:game_init()
	self.gsz = self.host_obj.Transform.findWithName("gsz")
	self.gsy = self.host_obj.Transform.findWithName("gsy")
	self.gxz = self.host_obj.Transform.findWithName("gxz")
	self.gxy = self.host_obj.Transform.findWithName("gxy")
	
	self.bird = self.host_obj.Transform.findWithName("bird")
	
	w,h = camera:getWorldSize()
	
	self.gsz.Transform:setPosition(130,h-30)
	self.gsy.Transform:setPosition(280,h-30)
	self.gxz.Transform:setPosition(130,50)
	self.gxy.Transform:setPosition(280,50)
	continue = false
end

function FlappyMaster:update(dt)
	
	math.randomseed(os.time())
	self.gsz.Transform:move(-dt*self.speed,0)
	self.gsy.Transform:move(-dt*self.speed,0)
	self.gxz.Transform:move(-dt*self.speed,0)
	self.gxy.Transform:move(-dt*self.speed,0)
	local x1,y1 = self.gsz.Transform:getPosition()
	local x2,y2 = self.gsy.Transform:getPosition()
	local ra = math.random(-100,100)
	local rb = math.random(-100,100)
	if x1<=-25 then
		self.gsz.Transform:setPosition(280,h-30-ra)
		self.gxz.Transform:setPosition(280,50-ra)
		self.score = self.score + 1
		--print(tostring(self.score))
	elseif x2<=-25 then
		self.gsy.Transform:setPosition(280,h-30-rb)
		self.gxy.Transform:setPosition(280,50-rb)
		self.score = self.score + 1
		--print(tostring(self.score))
	end
	app.text_draw("Score:"..tostring(self.score),180,-20);
	app.text_flush()
end

function FlappyMaster:game_exit()

end



return FlappyMaster