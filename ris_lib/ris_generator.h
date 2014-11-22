#pragma once

#include "ris_resources.h"

#include <fstream>
#include <string>
#include <stdexcept>

#include <boost/filesystem.hpp>

namespace ris {

    template <typename TSource>
    class generator {
        TSource&& source;

    public:
        generator(TSource&& s) :source(s){}

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
                s
                    << "std::string Resource::" << resource.name << "() {\n"
                    << "    static char const literal[] = "
                    ;

                stream_resource(s, resource);

                s
                    << "    return std::string(literal, sizeof(literal)/sizeof(char));\n"
                    << "}\n"
                    ;
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
            static const unsigned MAX_IN_ONE_LINE = 100;
            std::string data = get_resource_data(res);
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
        }

        std::string get_resource_data(resource const& res) {
            if (res.source_type == "string")
                return res.source;
            else if (res.source_type == "file")
                return read_file_contents_binary(res.source);

            throw std::runtime_error(std::string("unknown source type: ") + res.source_type);
        }

        std::string read_file_contents_binary(std::string const& filename) {
            std::string full_filename = (boost::filesystem::path(source.base_path())
                / filename).generic_string();

            std::ifstream file(full_filename, std::ios::binary);
            if (!file)
                throw std::runtime_error(std::string("cannot open " + full_filename));

            return std::string(std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>());
        }
    };

    template <typename TSource>
    generator<TSource> get_generator(TSource&& s) {
        return generator<TSource>(s);
    }
}
