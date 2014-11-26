#pragma once

#include "ris_resources.h"

#include <picojson_serializer.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include <boost/filesystem.hpp>

namespace ris {
    class json_resources {
        resource_collection collection;
        std::string root_path;

    public:
        json_resources(std::string const& json_path) {
            read_from_file(json_path);
            root_path = boost::filesystem::path(json_path).parent_path().generic_string();
        }

        resource_collection const& resources() const {
            return collection;
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

        void override_header_if_not_empty(std::string const& h) {
            if (!h.empty())
                collection.header = h;
        }

        void override_source_if_not_empty(std::string const& s) {
            if (!s.empty())
                collection.source = s;
        }

        void override_namespace_if_not_empty(std::string const& n) {
            if (!n.empty())
                collection.namespace_ = n;
        }

    private:
        void read_from_file(std::string const& json_path) {
            std::ifstream json_file(json_path);
            if (!json_file)
                throw std::runtime_error(std::string("not a valid json file: ") + json_path);
            picojson::value v;
            json_file >> v;
            std::string err = picojson::get_last_error();
            if (!err.empty())
                throw std::runtime_error(json_path + ": " + err);

            picojson::convert::from_value(v, collection);
        }
    };
}
