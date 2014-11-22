_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

local OS = os.get()
local settings = {
	links = {
		linux = { 'boost_system', 'boost_filesystem', 'dl', 'pthread' },
		windows = {  },
		macosx = { 'boost_system', 'boost_filesystem' }
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
links {'bundle'}

make_console_app('ris', {
 './ris_app/*.cpp',
 './ris_lib/*.h'
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
run_target_after_build()
links{settings.links[OS],'bundle'}

