#pragma once

#include "ris_resources.h"

#include <string>
#include <fstream>
#include <stdexcept>

#include <boost/filesystem.hpp>

namespace ris {
    class resource_loader {
        resource const& res;
        boost::filesystem::path base;
    public:
        resource_loader(resource const& r,std::string const& base_dir) :
            res(r),
            base(base_dir)
        {}
    public:
        std::string get() {
            if (res.source_type == "string")
                return res.source;
            else if (res.source_type == "file")
                return read_file_contents_binary(res.source);

            throw std::runtime_error(std::string("unknown source type: ") + res.source_type);
        }
    private:
        std::string read_file_contents_binary(std::string const& filename) {
            std::string full_filename = (base / filename).generic_string();

            std::ifstream file(full_filename, std::ios::binary);
            if (!file)
                throw std::runtime_error(std::string("cannot open ") + full_filename);

            return std::string(std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>());
        }
    };
}
