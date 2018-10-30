--region NewFile_1.lua
--Author : DanyDeng
--Date   : 2015/2/26
--此文件由[BabeLua]插件自动生成



--endregion

local Genome = {}

function Genome:new(len)
    local o = {}
    o.bits = {}
    o.fitness = 0
    --math.randomseed(os.time())
    for i = 1,len do
        if math.random()>0.5 then
            table.insert(o.bits,1)
        else
            table.insert(o.bits,0)
        end
    end
    return o
end

return Genome