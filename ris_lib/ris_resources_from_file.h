#pragma once

#include "ris_json_resources.h"
#include "ris_yaml_resources.h"

namespace ris {
    inline ris::queryable_resources load_resources_from_file(std::string const& path) {
        static std::unordered_map<std::string, ris::file_resources_loader> extension_to_loader = {
            { ".json", ris::json_resources::read_from_file },
            { ".yaml", ris::yaml_resources::read_from_file },
            { ".yml", ris::yaml_resources::read_from_file },
        };
        auto extension = boost::filesystem::path(path).extension().generic_string();

        auto loader = extension_to_loader.find(extension);
        if (loader == std::end(extension_to_loader))
            throw std::runtime_error(std::string("unknown extension: ") + extension + " in " + path);

        return ris::queryable_resources(path, loader->second);
    }
}
