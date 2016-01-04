#pragma once

#include <bundle.hpp>
#include <string>
#include <unordered_map>
#include <stdexcept>

namespace ris {
    class bundle_compression {
        std::unordered_map<std::string, unsigned int> compression_algos;
    public:
        bundle_compression() : 
            compression_algos({
                { "RAW", bundle::RAW },
                { "SHOCO", bundle::SHOCO },
                { "LZ4F", bundle::LZ4F },
                { "MINIZ", bundle::MINIZ },
                { "LZIP", bundle::LZIP },
                { "LZMA20", bundle::LZMA20 },
                { "ZPAQ", bundle::ZPAQ },
                { "LZ4", bundle::LZ4 },
                { "BROTLI9", bundle::BROTLI9 },
                { "ZSTD", bundle::ZSTD },
                { "LZMA25", bundle::LZMA25 },
                { "BSC", bundle::BSC },
                { "BROTLI11", bundle::BROTLI11 },
                { "SHRINKER", bundle::SHRINKER },
                { "CSC20", bundle::CSC20 },
                { "ZSTDF", bundle::ZSTDF },
                { "BCM", bundle::BCM },
                { "ZLING", bundle::ZLING },
                { "MCM", bundle::MCM },
                { "TANGELO", bundle::TANGELO },
                { "ZMOLLY", bundle::ZMOLLY },
                { "CRUSH", bundle::CRUSH },
                { "LZJB", bundle::LZJB },
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

            throw std::runtime_error(std::string("no such compression algorithm: ")+key);
            // return bundle::NONE;
        }

        std::string pack(std::string const& key, std::string const& data) {
            return bundle::pack(this->get(key), data);
        }
    };
}
