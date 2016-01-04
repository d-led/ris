ris
===

[![Build Status](https://travis-ci.org/d-led/ris.svg?branch=master)](https://travis-ci.org/d-led/ris)

[**ris**](https://github.com/d-led/ris) strives to be a simple-to-use cross-platform resource compiler for c++ projects.

**ris** allows embedding (potentially compressed) blobs of data into executables, which can be queried at runtime

usage
-----

an example project: [self_contained_lua_example](https://github.com/d-led/self_contained_lua_example)

`ris <path_to>/<resources>.[json/yml/yaml]`

where `<resources>.json` is the resource definition, i.e [test.json](acceptance_test/test.json).

```json
{
    "namespace" : "test",
    "class" : "Resource",
    "header" : "acceptance_test/resource.h",
    "source" : "acceptance_test/resource.cpp",
    "resources" : [
        {
            "name" : "string_test",
            "source_type" : "string",
            "source" : "plain text"
        },
        {
            "name" : "binary_file_test",
            "source_type" : "file",
            "source" : "test.bin"
        }
    ]
}
```

### YAML support ###

The definition can also be written in a more multi-line friendly [YAML](http://yaml.org/) format (via [yaml-cpp](https://github.com/jbeder/yaml-cpp)). I.e. see [acceptance_test/test.yml](acceptance_test/test.yml). YAML format is deliberately held structurally compatible with JSON and not idiomatical YAML.

### output ###

Two c++11 files ([.h](acceptance_test/resource.h) and [.cpp](acceptance_test/resource.h)) containing the resources as string constants will be generated if everything is ok. These can be compiled along with your project and used to retrieve string resources. 

Strings are single-byte `char`s and are treated agnostically with respect to their meaning/encoding. 

### getters ###

`name` should be a valid c++ identifier, as it will be translated into the resource getter, i.e.:

```cpp
std::string res = test::Resource::string_test();
```
or
```cpp
std::string res = test::Resource::Get("string_test");
```

key query
---------

Resource keys in the compiled resource can be enumerated passing a callable to `GetKeys`:

```cpp
std::vector<std::string> keys;
test::Resource::GetKeys([&keys](char const* key){
    keys.emplace_back(key);
});
```

custom member names
-------------------

Sometimes it may be beneficial to give resources names that wouldn't be valid C++ identifiers, such as paths. These resources can be given custom member names with an optional parameter as in:

```json
{
 "member_name" : "custom_member_name",
 "name" : "custom.member/name",
  ...
}
```

If it's not present, the `name` parameter will be used for members.

compression with bundle
-----------------------

Resources can optionally be compressed with [bundle](https://github.com/r-lyeh/bundle.git). The resulting resources should be linked with [bundle](https://github.com/r-lyeh/bundle.git) as well. Bundle is easy to build in its amalgamated form, containing multiple compression algorithms and a benchmarking infrastructure.

The compression algorithm enums as strings can be used in the resource definition, i.e.:

```json
{
    "name" : "itself_packed_lz4",
    "source_type" : "file",
    "source": "test.json",
    "compression" : "LZ4F"
}
```

building
--------

if the present build files do not suit your platform:
- check [premake4.lua](premake4.lua) if the dependencies are ok
- `premake/premake4[.*] <build_system>`
- check out [premake4 documentation](http://industriousone.com/premake-quick-start) if in doubt
- if the default code generator template should be regenerated: `premake/premake4 template`
- build using the build system of choice

customization
-------------

`ris` uses text resources generated and bootstrapped by its own early version. The code generator is customizable via code generator template overrides. The default template can be seen in [`template.json`](ris_lib/template.json), and the generated header in [`template.h`](ris_lib/template.h). The generation sequence can be seen in [`ris.cpp`](ris_app/ris.cpp).

To override the template, define a template file based on [`template.json`](ris_lib/template.json). If values are omitted, they will be taken from the default template. Thus, if I were to make a version of `ris` that would throw on a missing template resource string, I would generate `template.*` from [`template_throwing.json`](ris_lib/template_throwing.json):

```
ris ris_lib/template.json ris_lib/template_throwing.json
```

c++03
-----

A `C++03` override template is provided: [template_cpp03.json](ris_lib/template_cpp03.json) with a linear search instead of an `unordered_map` for the key/value API. Use it for example like

```
ris my_template.json template_cpp03.json
```

now and then
------------

- The [acceptance test](acceptance_test) is a round-trip test, compiled and linked with the resources generated by `ris`. The preservation of string data is of interest there.
- The strings are copied in the default template. An optional copy-reduced API is possible via a custom template.
- Resource names are not validated. The C++ compiler will ultimately validate them.

why c++
-------

Such code generator as `ris` could most probably be developed more rapidly using any other programming language with a huge framework and a ton of libraries behind them. My personal preference for certain kinds of small projects lies in the area of self-contained single-binary/single-file executables or libraries, such as [Lua](http://www.lua.org). Lua is the primary motivation for this project, as it is itself a compact library for building flexible and extensible prototypes and tools. `ris` can act as a bootstrapping component to embed resources for building specialized shell-scripting replacements, i.e. for massive scripted file operations.

dependencies
------------

The generated code is self-contained and uses the standard library only, unless compression ([bundle](https://github.com/r-lyeh/bundle)) is used, or the template is customized with another dependency.

To rebuild `ris` from scratch, the following dependencies are needed:

- [Boost](http://www.boost.org/), filesystem api
- [Premake4](https://bitbucket.org/premake/premake-dev/wiki/Home), meta-build
- [Catch](https://github.com/philsquared/Catch), testing
- [picojson](https://github.com/kazuho/picojson), json serialization
- [picojson_serializer](https://github.com/d-led/picojson_serializer) json serialization wrappers for fast prototyping
- [yaml-cpp](https://github.com/jbeder/yaml-cpp) YAML parsing
- [bundle](https://github.com/r-lyeh/bundle), compression
 
alternatives
------------

 - [incbin](https://github.com/graphitemaster/incbin)

license
=======

- Copyright 2014, Dmitry Ledentsov
- [MIT License](LICENSE)
- Generated code is not licensed
- Dependencies retain their respective licenses
