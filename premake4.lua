_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'ris'

includedirs {
	'./Catch/single_include',
	'./picojson',
	'./picojson_serializer/'
}

make_console_app('ris-test', { './test/*.cpp' })
make_cpp11()
run_target_after_build()

make_console_app('ris', { './ris_app/*.cpp' })
make_cpp11()
run_target_after_build()

