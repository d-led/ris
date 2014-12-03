_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

local OS = os.get()
local settings = {
	links = {
		linux = { 'boost_system', 'boost_filesystem', 'boost_regex', 'dl', 'pthread' },
		windows = {  },
		macosx = { 'boost_system', 'boost_filesystem', 'boost_regex' }
	}
}

local function platform_specifics()
	make_cpp11()
	configuration 'macosx'
		includedirs {'/usr/local/include' }
		libdirs { '/usr/local/lib' }
	configuration 'windows'
		includedirs { os.getenv 'BOOST' }
		libdirs { path.join(os.getenv'BOOST',[[lib32-msvc-12.0]]) }
	configuration 'linux'
	configuration { '*' }
end

make_solution 'ris'

includedirs {
	'./Catch/single_include',
	'./picojson',
	'./picojson_serializer',
	'./bundle'
}

make_static_lib('bundle',{
	'./bundle/bundle.cpp',
	'./bundle/bundle.hpp'
})
platform_specifics()

-- make_console_app('bundle-sample',{
-- 	'./bundle/sample.cc'
-- })
-- platform_specifics()
-- run_target_after_build()
-- links {
-- 	'bundle'
-- }

make_console_app('ris-test', { './test/*.cpp' })
platform_specifics()
run_target_after_build()
links{settings.links[OS],'bundle'}

make_console_app('ris', {
 './ris_app/*.cpp',
 './ris_lib/*.*'
})
platform_specifics()
run_target_after_build()
links{settings.links[OS],'bundle'}

make_console_app('ris-acceptance-test', {
 './acceptance_test/*.cpp',
 './acceptance_test/*.h',
 './acceptance_test/*.json',
 './acceptance_test/*.lua',
})
platform_specifics()
links{settings.links[OS],'bundle'}

--- http://stackoverflow.com/a/4991602/847349 ---
function file_exists(name)
   local f=io.open(name,"r")
   if f~=nil then io.close(f) return true else return false end
end

function exec(command)
	local handle = io.popen(command)
	local result = handle:read("*a")
	print(result)
	handle:close()
	return result
end

function get_uname()
	local uname = exec 'uname'
	uname = uname or 'windows'
	uname = uname:lower():gsub("^%s*(.-)%s*$", "%1") --trimmed--
	return uname
end

newaction {
   trigger     = "template",
   description = "generate the default code template",
   execute     = function ()
   		local ok = false
		for _,os in ipairs { 'windows', 'macosx', 'linux' } do
			for __, build in ipairs { 'Debug', 'Release' } do
				for ___, extension in ipairs { '' , '.exe' } do
					local candidate = path.join(os, 'bin', build, 'ris' .. extension)
					if file_exists(candidate) then
						local command = candidate .. ' ris_lib/template.json'
						if OS=='windows' then command=command:gsub('/','\\') end
						print(command .. ' ...')
						exec(command)
						ok = true
					end
					if ok then return end
				end
			end
		end
		-- last try with global path
		exec('ris' .. ' ris_lib/template.json')
   end
}

newaction {
   trigger     = "pack",
   description = "produce a binary distribution",
   execute     = function ()
		local release_dir = 'distribution'
		os.mkdir(release_dir)
		os.copyfile('README.md',path.join(release_dir,'README.md'))
		local uname = get_uname()
   		if uname == 'macosx' or uname == 'darwin' then
			exec[[make -C BuildClang config=release]]
			os.copyfile('macosx/bin/Release/ris',path.join(release_dir,'ris.osx'))
		elseif uname == 'linux' then
			exec[[make -C Build config=release]]
			os.copyfile('linux/bin/Release/ris',path.join(release_dir,'ris'))
		elseif uname == 'windows' or uname:find('mingw') then
			exec [[msbuild Build\ris.sln /p:Configuration=Release]]
			os.copyfile([[windows\bin\Release\ris.exe]],path.join(release_dir,'ris.exe'))
		end
   end
}
