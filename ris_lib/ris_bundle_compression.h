#pragma once

#include <bundle.hpp>
#include <string>
#include <unordered_map>

namespace ris {
    class bundle_compression {
        std::unordered_map<std::string, unsigned> compression_algos;
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
    };
}
