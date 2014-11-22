ris
===

[![Build Status](https://travis-ci.org/d-led/ris.svg?branch=master)](https://travis-ci.org/d-led/ris)

**ris** strives to be a simple-to-use cross-platform resource compiler for c++11 projects

usage
-----

`ris <path_to>/<resources>.json`

where `<resources>.json` is the resource definition, i.e.

```json
{
    "namespace" : "test",
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

Two c++11 files containing the resources as string constants will be generated if everything is ok. These can be compiled along with your project and used to retrieve string resources. 

Strings are single-byte `char`s and are treated agnostically with respect to their meaning/encoding. 

Furthermore, `name` should be a valid c++ identifier, as it will be translated into the resource getter, i.e.:

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

compression with bundle
-----------------------

Resources can optionally be commpressed with [bundle](https://github.com/r-lyeh/bundle.git). The resulting resources should be linked with [bundle](https://github.com/r-lyeh/bundle.git) as well. Bundle is easy to build in its amalgamated form, containing multiple compression algorithms and a benchmarking infrastructure.

The compression algorithm enums as strings can be used in the resource definition, i.e.:

```json
{
    "name" : "itself_packed_lz4hc",
    "source_type" : "file",
    "source": "test.json",
    "compression" : "LZ4HC"
}
```

dependencies
------------

- [Boost](http://www.boost.org/), filesystem api
- [Premake4](https://bitbucket.org/premake/premake-dev/wiki/Home), meta-build
- [Catch](https://github.com/philsquared/Catch), testing
- [picojson](https://github.com/kazuho/picojson), json serialization
- [picojson_serializer](https://github.com/d-led/picojson_serializer) json serialization wrappers for fast prototyping
- [bundle](https://github.com/r-lyeh/bundle), compression

license
=======

- Copyright 2014, Dmitry Ledentsov
- [MIT License](http://www.opensource.org/licenses/mit-license.php)
- Generated code is not licensed
- Dependencies retain their respective licenses
