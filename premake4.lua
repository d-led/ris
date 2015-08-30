include 'premake'

local OS = os.get()
local settings = {
	links = {
		linux = { 'boost_system', 'boost_filesystem', 'boost_regex', 'dl', 'pthread' },
		windows = {  },
		macosx = { 'boost_system', 'boost_filesystem', 'boost_regex', 'c++' }
	}
}

local function platform_specifics()
	use_standard('c++11')
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

platforms 'native'

includedirs {
	'./deps/Catch/single_include',
	'./deps/picojson',
	'./deps/picojson_serializer',
	'./deps/bundle',
	'./deps/yaml-cpp/include'
}

make_static_lib('bundle',{
	'./deps/bundle/bundle.cpp',
	'./deps/bundle/bundle.hpp'
})
platform_specifics()

make_static_lib('yaml-cpp',{
	'./deps/yaml-cpp/src/**.*'
})
platform_specifics()

make_console_app('ris-test', { './test/*.cpp' })
platform_specifics()
run_target_after_build()
links{settings.links[OS],'bundle','yaml-cpp'}

make_console_app('ris', {
 './ris_app/*.cpp',
 './ris_lib/*.*'
})
platform_specifics()
run_target_after_build()
links{settings.links[OS],'bundle','yaml-cpp'}

make_console_app('ris-acceptance-test', {
 './acceptance_test/*.cpp',
 './acceptance_test/*.h',
 './acceptance_test/*.json',
 './acceptance_test/*.lua',
})
platform_specifics()
links{settings.links[OS],'bundle','yaml-cpp'}

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
	if os.get then
		return os.get()
	end
	
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
		for _,filename in ipairs {
			'README.md',
			'LICENSE'
		} do
			os.copyfile(filename,path.join(release_dir,filename))
		end
		local uname = get_uname()
   		if uname == 'macosx' or uname == 'darwin' then
			exec[[make -C Build/macosx/gmake config=release_native]]
			os.copyfile('bin/macosx/gmake/native/Release/ris',path.join(release_dir,'ris.osx'))
		elseif uname == 'linux' then
			exec[[make -C Build/linux/gmake config=release32]]
			os.copyfile('bin/linux/gmake/x32/Release/ris',path.join(release_dir,'ris'))
		elseif uname == 'windows' or uname:find('mingw') then
			exec [[msbuild Build\windows\vs2013\ris.sln /p:Configuration=Release]]
			os.copyfile('./bin/windows/vs2013/x32/Release/ris.exe',path.join(release_dir,'ris.exe'))
		end
   end
}
