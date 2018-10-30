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


function left(this,object)
	if object.finish1 and object.finish2 then
		object.finish1 = false
		object.finish2 = false
		object.page_direct = 0
	end
end

function right(this,object)
	if object.finish1 and object.finish2 then
		object.finish1 = false
		object.finish2 = false
		object.page_direct = 1
	end
end

function Test1:game_init()

	self.sound = app.sound_create("resources/xyl.ogg","stream")
	app.sound_stream_play(self.sound,true)
	
	self.buttonl = UI.getObjectByName("button_l")
	self.buttonr = UI.getObjectByName("button_r")
	self.buttonl:setCallObject(self)
	self.buttonr:setCallObject(self)
	self.buttonl:setCallback(left)
	self.buttonr:setCallback(right)
	self.scroller = UI.getObjectByName("scroller_v")
	self.scroller:setCurrentVal(100)
	
	--page:0,1,2
	self.cur_page = 0
	--0 for left,1 for right
	self.page_direct = -1
end

function Test1:update(dt)
	
	if self.cur_page==0 then
		if self.page_direct==0 then
			self.finish1 = true
			self.finish2 = true
		elseif self.page_direct==1 then
			if self.text_pos1>=-200 then
				self.text_pos1 = self.text_pos1 - self.page_change_speed
			else
				if not self.finish1 then
					self.finish1 = true
				end
			end
			if self.text_pos2>=400 then
				self.text_pos2 = self.text_pos2 - self.page_change_speed
			else
				if not self.finish2 then
					self.finish2 = true
				end	
			end
			if self.finish1 and self.finish2 then
				if self.text_pos2<400 then
					self.text_pos2 = 400
				end
				self.cur_page = 1
				self.page_direct = -1
			end
		end
	elseif self.cur_page==1 then
		if self.page_direct==0 then
			if self.text_pos1<=600 then
				self.text_pos1 = self.text_pos1 + self.page_change_speed
			else
				if not self.finish1 then
					self.finish1 = true
				end	
			end
			if self.text_pos2<=1300 then
				self.text_pos2 = self.text_pos2 + self.page_change_speed
			else
				if not self.finish2 then
					self.finish2 = true
				end	
			end
			if self.finish1 and self.finish2 then
				if self.text_pos1>600 then
					self.text_pos1 = 600
				end
				self.cur_page = 0
				self.page_direct = -1
			end
		elseif self.page_direct==1 then
			if self.text_pos2>=-800 then
				self.text_pos2 = self.text_pos2 - self.page_change_speed
			else
				if not self.finish1 then
					self.finish1 = true
				end	
			end
			if self.text_pos3>=450 then
				self.text_pos3 = self.text_pos3 - self.page_change_speed
			else
				if not self.finish2 then
					self.finish2 = true
				end	
			end
			if self.finish1 and self.finish2 then
				if self.text_pos3<450 then
					self.text_pos3 = 450
				end
				self.cur_page = 2
				self.page_direct = -1
			end
		end
	elseif self.cur_page==2 then
		if self.page_direct==0 then
			if self.text_pos2<=400 then
				self.text_pos2 = self.text_pos2 + self.page_change_speed
			else
				if not self.finish1 then
					self.finish1 = true
				end	
			end
			if self.text_pos3<=1300 then
				self.text_pos3 = self.text_pos3 + self.page_change_speed
			else
				if not self.finish2 then
					self.finish2 = true
				end	
			end
			if self.finish1 and self.finish2 then
				if self.text_pos2>400 then
					self.text_pos2 = 400
				end
				self.cur_page = 1
				self.page_direct = -1
			end
		elseif self.page_direct==1 then
			self.finish1 = true
			self.finish2 = true
			
		end
	end
	app.text_draw("Wellcome!",self.text_pos1,300);
	app.text_draw("So let's have a quick look at what we can do!",self.text_pos2,300);
	app.text_draw("Now you can change the volume below if you want.\nThe 3rd function!",self.text_pos3,300);
	app.text_flush()
	
	local v = self.scroller:getCurrentVal()
	app.sound_stream_turn(self.sound,v)
end

function Test1:draw(dt)
	
end

function Test1:game_exit()
	
end

return Test1