#pragma once

#include "ris_resources.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

#include <boost/filesystem.hpp>

namespace ris {
    class yaml_resources {
        resource_collection collection;
        std::string root_path;

    public:
        typedef std::unordered_map<std::string, resource> lookup_t;

        yaml_resources(std::string const& yaml_path) {
            read_from_file(yaml_path);
            root_path = boost::filesystem::path(yaml_path).parent_path().generic_string();
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

    private:
        template< typename TargetType >
        void optional_get(TargetType& target, std::string const& key, YAML::Node& node) {
            if (node[key].IsScalar())
                target = node[key].as<TargetType>();
        }

        void read_from_file(std::string const& yaml_path) {
            try {
                auto root_node = YAML::LoadFile(yaml_path);

                optional_get(collection.namespace_, "namespace", root_node);
                optional_get(collection.header, "header", root_node);
                optional_get(collection.source, "source", root_node);
                optional_get(collection.class_, "class", root_node);

                for (auto res : root_node["resources"]) {
                    ris::resource r = {};
                    optional_get(r.name, "name", res);
                    optional_get(r.member_name, "member_name", res);
                    optional_get(r.source_type, "source_type", res);
                    optional_get(r.source, "source", res);
                    optional_get(r.compression, "compression", res);
                    collection.resources.emplace_back(r);
                }
            }
            catch (std::exception& e) {
                throw std::runtime_error(std::string("YAML parsing error in ") + yaml_path + ": " + e.what());
            }
        }
    };
}
