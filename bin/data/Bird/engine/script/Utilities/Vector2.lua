local Vector2 =
{
	x = 0,
	y = 0
}

function Vector2:new(x,y)
	local o = {}
	setmetatable(o,self)
	self.__index = self 
	o.x = x
	o.y = y
	return o
end

function Vector2:out()
	print("("..self.x..","..self.y..")")
end

function Vector2:mod()
	return math.sqrt(self.x*self.x + self.y*self.y)
end

function Vector2.dotProduct(v1,v2)
	return v1.x*v2.x + v2.y*v1.y
end

function Vector2.getAngle(v1,v2)
	return Vector2.dotProduct(v1,v2)/(v1:mod()*v2:mod())
end

--v1 -> v2
function Vector2.getDiff(v1,v2)
	return Vector2:new(v2.x-v1.x,v2.y-v1.y)
end

function Vector2:rotate(rad)
	local xx = self.x 
	self.x = self.x*math.cos(rad) - self.y*math.sin(rad)
	self.y = xx*math.sin(rad) + self.y*math.cos(rad)
end

function Vector2.rotatePoint(x,y,rad)
	local xx = x 
	x = x*math.cos(rad) - y*math.sin(rad)
	y = xx*math.sin(rad) + y*math.cos(rad)
	return x,y
end

return Vector2