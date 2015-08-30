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
    struct yaml_resources : queryable_resources<yaml_resources> {
        yaml_resources(std::string const& yaml_path) : queryable_resources<yaml_resources>(yaml_path){}

        static void read_from_file(std::string const& yaml_path, resource_collection& collection) {
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
    private:
        template< typename TargetType >
        static void optional_get(TargetType& target, std::string const& key, YAML::Node& node) {
            if (node[key].IsScalar())
                target = node[key].as<TargetType>();
        }
    };
}
