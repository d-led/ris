#pragma once

#include "ris_resources.h"
#include "ris_resource_loader.h"
#include "template.h"

#include <string>
#include <algorithm>

#include <boost/filesystem/path.hpp>

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
                << Resource::header_class()
                << "public:\n"
            ;

            stream_resource_members(s);

            stream_keys_getter(s);

            s
                << Resource::header_key_value_getter()
                << Resource::header_on_no_key()
                ;

            s << Resource::header_class_end();

            if (!resources.namespace_.empty())
                s << "}\n";
        }

        template <typename TStream>
        void generate_source(TStream& s) {
            auto& resources = source.resources();

            s
                << Resource::source_preamble()
                << "#include \""
                << boost::filesystem::path(resources.header).filename().generic_string()
                << "\"\n"
                << Resource::source_includes()
                ;

            if (!resources.namespace_.empty())
                s << "namespace " << resources.namespace_ << " {\n";

            for (auto& resource : resources.resources) {
                stream_resource(s, resource);
            }

            s
                << Resource::source_getters_begin()
            ;

            for (auto& resource : resources.resources) {
                s
                    << "        { \"" << resource.name << "\", Resource::" << resource.name << " },\n"
                    ;
            }

            s
                << Resource::source_getters_end()
            ;

            if (!resources.namespace_.empty())
                s << "}\n";
        }

    private:
        template <typename TStream>
        void stream_head(TStream& s) {
            s 
                << "#pragma once\n"
                << Resource::header_preamble()
                << Resource::header_includes()
            ;

            if (any_with_compression) {
                s
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
                << Resource::header_key_getter_begin()
            ;
            
            for (auto& resource : source.resources().resources) {
                s
                    << "        \"" << resource.name << "\",\n";
            }
            
            s
                << Resource::header_key_getter_end()
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

                s << static_cast<short>(c) << ", ";

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
