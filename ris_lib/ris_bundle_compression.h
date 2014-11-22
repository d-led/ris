#pragma once

#include <bundle.hpp>
#include <string>
#include <unordered_map>

namespace ris {
    class bundle_compression {
        std::unordered_map<std::string, unsigned int> compression_algos;
    public:
        bundle_compression() : 
            compression_algos({
                { "LZ4", bundle::LZ4 },
                { "LZ4HC", bundle::LZ4HC },
                { "SHOCO", bundle::SHOCO },
                { "MINIZ", bundle::MINIZ },
                { "LZIP", bundle::LZIP },
                { "LZMA", bundle::LZMA },
                { "ZPAQ", bundle::ZPAQ },
                { "BROTLI", bundle::BROTLI },
        })
        {}
    public:
        bool is_legal(std::string const& key) const {
            return compression_algos.find(key) != compression_algos.end();
        }

        unsigned int get(std::string const& key) const {
            auto it = compression_algos.find(key);
            if (it != compression_algos.end())
                return it->second;
            return bundle::NONE;
        }

        std::string pack(std::string const& key, std::string const& data) {
            return bundle::pack(this->get(key), data);
        }
    };
}
