#pragma once

#include "ris_resources.h"

#include <picojson_serializer.h>
#include <fstream>
#include <string>
#include <stdexcept>

namespace ris {
    struct json_resources {
        static void read_from_file(std::string const& json_path, resource_collection& collection) {
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
