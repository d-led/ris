#pragma once

#include "ris_resources.h"
#include "ris_resource_loader.h"

#include <string>
#include <algorithm>

namespace ris {

    template <typename TSource,typename TCompression>
    class generator {
        TSource&& source;
        TCompression&& compression;

        bool any_with_compression;

    public:
        generator(TSource&& s, TCompression&& c) :
            source(s),
            compression(c),
            any_with_compression(std::any_of(std::begin(source.resources().resources),
                                         std::end(source.resources().resources),
                                         [this](resource const& res) {
            return compression.is_legal(res.compression);
        }))
        {}

    public:
        template <typename TStream>
        void generate_header(TStream& s) {
            auto& resources = source.resources();

            stream_head(s);

            if (!resources.namespace_.empty())
                s << "namespace " << resources.namespace_ << " {\n";

            s
                << "class Resource /*final*/ {\n"
                << "public:\n"
                << "    typedef std::string(*ResourceGetter)();\n"
                << "public:\n"
                ;

            stream_resource_members(s);

            stream_keys_getter(s);

            s
                << "public: // key/value api\n"
                << "    static std::string Get(std::string const& key);\n"
                << "public:\n"
                << "    static std::string OnNoKey() {\n"
                << "        // could be configured to throw\n"
                << "        return \"\";\n"
                << "    }\n"
                << "};\n"
                ;

            if (!resources.namespace_.empty())
                s << "}\n";
        }

        template <typename TStream>
        void generate_source(TStream& s) {
            auto& resources = source.resources();

            s

                << "#include \"resource.h\"\n"
                << "#include <unordered_map>\n"
                ;

            if (!resources.namespace_.empty())
                s << "namespace " << resources.namespace_ << " {\n";

            for (auto& resource : resources.resources) {
                stream_resource(s, resource);
            }

            s
                << "std::string Resource::Get(std::string const& key) {\n"
                << "    static std::unordered_map<std::string,ResourceGetter> getters = {\n"
                ;

            for (auto& resource : resources.resources) {
                s
                    << "        { \"" << resource.name << "\", Resource::" << resource.name << " },\n"
                    ;
            }

            s
                << "    };\n"
                << "    auto getter = getters.find(key);\n"
                << "    if (getter == getters.end())\n"
                << "         return OnNoKey();\n"
                << "    return getter->second();\n"
                << "}\n"
                ;

            if (!resources.namespace_.empty())
                s << "}\n";
        }

    private:
        template <typename TStream>
        void stream_head(TStream& s) {
            s
                << "#pragma once\n"
                << "#include <string>\n"
            ;

            if (any_with_compression) {
                s
                    << "#include <cstring>\n"
                    << "#include <bundle.hpp>\n"
                ;
            }
        }

        template <typename TStream>
        void stream_resource_members(TStream& s) {
            for (auto& resource : source.resources().resources) {
                s
                    << "    static std::string " << resource.name << "();\n";
            }
        }

        template <typename TStream>
        void stream_keys_getter(TStream& s) {
            s
                << "public: // key/value api\n"
                << "template <typename TInserter>\n"
                << "static void GetKeys(TInserter inserter) {\n"
                << "    static const char* keys[] = {\n"
            ;
            
            for (auto& resource : source.resources().resources) {
                s
                    << "        \"" << resource.name << "\",\n";
            }
            
            s
                << "    };\n"
                << "    for (auto key : keys) {\n"
                << "        inserter(key);\n"
                << "    }\n"
                << "}\n"
            ;
        }

        template <typename TStream>
        void stream_resource(TStream& s, resource const& res) {
            s
                << "std::string Resource::" << res.name << "() {\n"
                << "    static char const literal[] = "
            ;


            static const unsigned MAX_IN_ONE_LINE = 100;
            std::string data = resource_loader(res, source.base_path()).get();

            if (compression.is_legal(res.compression))
                data = compression.pack(res.compression, data);

            s << " {";
            int count = 0;

            for (char c : data) {
                if (count > MAX_IN_ONE_LINE) {
                    count = 0;
                }

                if (count == 0) {
                    s << "\n        ";
                }

                s << static_cast<unsigned short>(c) << ", ";

                count++;
            }

            s << "\n    };\n";

            std::string return_statement =
                compression.is_legal(res.compression)
                ?
                "    return bundle::unpack(std::string(literal, sizeof(literal)/sizeof(char)));\n"
                :
                "    return {literal, sizeof(literal)/sizeof(char)};\n"
            ;

            s
                << return_statement
                << "}\n"
            ;
        }
    };

    template <typename TSource, typename TCompression>
    generator<TSource, TCompression> get_generator(TSource&& s,TCompression&& c) {
        return generator<TSource,TCompression>(s,c);
    }
}
