#pragma once

#include "ris_json_resources.h"
#include "ris_resource_loader.h"

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>

#include <boost/filesystem/path.hpp>

namespace ris {

    template <typename TResource>
    struct default_or_from_file {
        std::unordered_map<std::string, std::string> resources;
    public:
        default_or_from_file(std::string const& t) {
            try_loading_resources(t);
        }

        std::string Get(std::string const& key) const {
            auto found = resources.find(key);
            return found != resources.end() ?
                found->second
                :
                TResource::Get(key)
                ;
        }

    private:
        void try_loading_resources(std::string const& json_path) {
            if (json_path.empty())
                return;

            try {
                auto base_dir = boost::filesystem::path(json_path).parent_path().generic_string();
                auto r = json_resources(json_path);
                for (auto& res : r.resources().resources) {
                    resources[res.name] = resource_loader(res, base_dir).get();
                }
                std::cout << "loaded " << resources.size() << " code generator overrides" << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << "could not load " << json_path << ": " << e.what() << std::endl;
            }
        }
    };

}
