#pragma once

#include <picojson_vector_serializer.h>
#include <picojson.h>
#include <vector>
#include <unordered_map>
#include <boost/filesystem.hpp>

namespace ris {

    struct resource {
        std::string name;
        std::string member_name; //optional
        std::string source_type;
        std::string source;
        std::string compression;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("name", name);
            ar & picojson::convert::member("member_name", member_name);
            ar & picojson::convert::member("source_type", source_type);
            ar & picojson::convert::member("source", source);
            ar & picojson::convert::member("compression", compression);
        }
    };

    struct resource_collection {
        std::string namespace_;
        std::string header;
        std::string source;
        std::string class_;
        std::vector<resource> resources;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("namespace", namespace_);
            ar & picojson::convert::member("resources", resources);
            ar & picojson::convert::member("header", header);
            ar & picojson::convert::member("source", source);
            ar & picojson::convert::member("class", class_);
        }
    };

    template <typename TResourceLoader>
    class queryable_resources {
        resource_collection collection;
        std::string root_path;

    public:
        typedef std::unordered_map<std::string, resource> lookup_t;

        queryable_resources(std::string const& source_path) {
            TResourceLoader::read_from_file(source_path, collection);
            root_path = boost::filesystem::path(source_path).parent_path().generic_string();
        }

        resource_collection const& resources() const {
            return collection;
        }

        lookup_t to_lookup() const {
            lookup_t lookup;
            for (auto& res : collection.resources) {
                lookup[res.name] = res;
            }
            return lookup;
        }

        std::string base_path() const {
            return root_path;
        }

        std::string header() const {
            return collection.header;
        }

        std::string source() const {
            return collection.source;
        }

        std::string namespace_() const {
            return collection.namespace_;
        }

        std::string class_() const {
            return collection.class_;
        }
    };
}
