#pragma once

#include "ris_resource_loader.h"

#include <string>
#include <algorithm>
#include <iostream>

#include <boost/filesystem/path.hpp>

namespace ris {

    template <typename TSource,typename TCompression,typename TTemplate>
    class generator {
        TSource&& source;
        TCompression&& compression;
        TTemplate&& generator_template;

        bool any_with_compression;

    public:
        generator(TSource&& s, TCompression&& c, TTemplate&& t) :
            source(s),
            compression(c),
            generator_template(std::forward<TTemplate>(t)),
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

            generator_template.stream("header_class",s);

            s
                << "public:\n"
            ;

            stream_resource_members(s);

            stream_keys_getter(s);

            
            generator_template.stream("header_key_value_getter",s);
            generator_template.stream("header_on_no_key",s);
            

            generator_template.stream("header_class_end",s);

            if (!resources.namespace_.empty())
                s << "}\n";
        }

        template <typename TStream>
        void generate_source(TStream& s) {
            auto& resources = source.resources();

            generator_template.stream("source_preamble",s);

            s
                << "#include \""
                << boost::filesystem::path(resources.header).filename().generic_string()
                << "\"\n"
            ;
            
            generator_template.stream("source_includes",s);

            if (!resources.namespace_.empty())
                s << "namespace " << resources.namespace_ << " {\n";

            for (auto& resource : resources.resources) {
                stream_resource(s, resource);
            }

            
            generator_template.stream("source_getters_begin",s);
            

            for (auto& resource : resources.resources) {
                s
                    << "        { \"" << resource.name << "\", Resource::" << member_name(resource) << " },\n"
                    ;
            }

            
            generator_template.stream("source_getters_end",s);
            

            if (!resources.namespace_.empty())
                s << "}\n";
        }

    private:
        template <typename TStream>
        void stream_head(TStream& s) {
            s 
                << "#pragma once\n"
            ;
            
            generator_template.stream("header_preamble",s);
            generator_template.stream("header_includes",s);
            
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
                    << "    static std::string " << member_name(resource) << "();\n";
            }
        }

        template <typename TStream>
        void stream_keys_getter(TStream& s) {
            
            generator_template.stream("header_key_getter_begin",s);
            
            for (auto& resource : source.resources().resources) {
                s
                    << "        \"" << resource.name << "\",\n";
            }
            
            
            generator_template.stream("header_key_getter_end",s);
        }

        template <typename TStream>
        void stream_resource(TStream& s, resource const& res) {
            s
                << "std::string Resource::" << member_name(res) << "() {\n"
                << "    static char const literal[] = "
            ;


            static const unsigned MAX_IN_ONE_LINE = 100;
            std::string data = resource_loader(res, source.base_path()).get();

            auto raw_size = data.size();

            if (compression.is_legal(res.compression)) {
                data = compression.pack(res.compression, data);
                auto new_size = data.size();
                std::cout << "[" << res.compression << "] "
                    << res.name << ": "
                    << new_size << "/" << raw_size
                    << " (" << ((double)new_size/raw_size*100.0) << "%)" << std::endl;
            }

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
                "    return std::string(literal, sizeof(literal)/sizeof(char));\n"
            ;

            s
                << return_statement
                << "}\n"
            ;
        }

        template <typename TResource>
        std::string member_name(TResource const& res) {
            if (!res.member_name.empty())
                return res.member_name;
            return res.name;
        }
    };

    template <typename TSource, typename TCompression, typename TTemplate>
    generator<TSource, TCompression, TTemplate> get_generator(TSource&& s,TCompression&& c,TTemplate&& t) {
        return generator<TSource,TCompression,TTemplate>(s,c,t);
    }
}
