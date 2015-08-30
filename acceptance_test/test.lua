#!/usr/bin/env lua
local e = ... or 'macosx/bin/Debug/ris'

function read_all_binary(src)
	local f = io.open(src, 'rb')
	local content = f:read '*a'
	f:close()
	return content
end

function copy_file(src, dst)
	local function write_all_binary(dst,what)
		local f = io.open(dst, 'w')
		f:write(what)
		f:close()
	end

	write_all_binary(dst, read_all_binary(src))
end

-- first json --
os.execute(e .. ' acceptance_test/test.json ris_lib/template.json')
copy_file('acceptance_test/resource.cpp', 'acceptance_test/resource.tmp')
-- then yaml --
os.execute(e .. ' acceptance_test/test.json ris_lib/template.yml')

-- check if same contents --
assert( read_all_binary('acceptance_test/resource.tmp'):gsub('\r','') == read_all_binary('acceptance_test/resource.cpp'):gsub('\r','') )
os.remove 'acceptance_test/resource.tmp'
