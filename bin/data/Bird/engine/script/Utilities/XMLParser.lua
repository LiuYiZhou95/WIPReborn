local SLAXML = require 'slaxml'
local Utilities = require 'Utilities'

local xml = {}
local error_n = 0
xml.node_stack = {}
xml.atrr_stack = {}
xml.data_list = {}

local function clear_stack()
	xml.node_stack = {}
	xml.atrr_stack = {}
end

local function clear_all_list()
	--[[
	xml.int_list.clear()
	xml.float_list.clear()
	xml.table_list.clear()
	xml.thread_list.clear()
	xml.string_list.clear()
	xml.function_list.clear()
	xml.userdata_list.clear()
	--]]
	xml.data_list = {}
end


local function startE(name,nsURI,nsPrefix)
	--[[
	print('starter')
	print(name)
	print('end')
	--]]
	--push
	local starter = {}
	local atrrs = {}
	starter.name = name
	starter.atrrs = atrrs
	table.insert(xml.node_stack,starter)
	
end

local function get_attribute(name,value,nsURI,nsPrefix)
	--push
	--table.insert(xml.stack,name)
	--local attr = {}
	--attr[name] = value
	local starter = xml.node_stack[#xml.node_stack]
	--table.insert(starter.atrrs,attr)
	starter.atrrs[name] = value
	
	--table.insert(xml.atrr_stack,#xml.atrr_stack,attr)
	--[[
	local prefix = ""
	for i=1, #(xml.node_stack) do  
		print(xml.node_stack[i])
		prefix = prefix..xml.node_stack[i]
	end 
	--]]
	--prefix
	--[[
	print('element')
	print(name)
	print(value)
	print('end')
	--]]
end

local function closeE(name,nsURI)
	--[[
	print('closer')
	print(name)
	print('end')
	print()
	print()
	--]]
	--pop
	table.remove(xml.node_stack)
end

local function get_text(text)
	
	local prefix = ""
	local val = nil
	--local 
	for i=1, #(xml.node_stack) do  
		--print(xml.node_stack[i].name)
		local type = xml.node_stack[i].atrrs["type"]
			
		if type=='n' then --number
			type = 'number'
		--elseif xml.node_stack[i].atrrs[j]=='i' then
			val = tonumber(text)
		elseif type=='' then --nil
			type = 'nil'
			val = nil
		elseif type=='s' then --string
			type = 'string'
		--elseif xml.node_stack[i].atrrs[j]=='t' then
			val = text
		elseif type=='f' then --function
			type = 'float'
			val = tonumber(text)
		--elseif xml.node_stack[i].atrrs[j]=='t' then
	
		elseif type=='b' then --bool
			type = 'boolean'
			if text=='false' then
				val = nil
			else
				val = 1
			end
		elseif type==nil then--no type atrr
			error_n = error_n + 1
			--print("Note: the node has no type information.lost")
		else
			type = 'unknow'
			val = nil
		end
		
		prefix = prefix..'.'..xml.node_stack[i].name
		
	end 
	xml.data_list[prefix] = val
	--prefix
	--[[
	print('text')
	print(text)
	print('end')
	--]]
	
end

local function get_comment(content)
	--[[
	print('comment')
	print(content)
	print('end')
	--]]
end

local function processI(target,content)
	
end


local parser = SLAXML:parser{
	startElement = startE,
	attribute = get_attribute,
	closeElement = closeE,
	text = get_text,
	comment = get_comment,
	pi = processI,
	}

function xml.get_node_val(node_str)
	return xml.data_list[node_str]
end

function xml.get_node_val_with_file(file_name,node_str)
	xml.loadxml(file_name)
	return xml.get_node_val(node_str)
end

function xml.loadxml(file_name)
	local f =  io.open(file_name)
	if f==nil then
		print("Read file wrong!"..file_name)
		return
	end
	clear_stack()
	clear_all_list()
	local myxml = f:read('*all')
	parser:parse(myxml,{stripWhitespace=true})
	if error_n~=0 then
		print("Note: "..tostring(error_n).." nodes has no type information.lost..")
	end
	
	--xml.data_list = {}
	--xml.node_stack = {}
	--xml.node_stack = {}
end


--[[
xml.int_list = {}
xml.float_list = {}
xml.string_list = {}
xml.table_list = {}
xml.function_list = {}
xml.thread_list = {}
xml.userdata_list = {}
--]]


return xml