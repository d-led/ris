#pragma once
/* This file has been generated using ris, do not modify! */

#include <string>

namespace ris {
class Resource /*final*/ {
public:
    static std::string header_preamble();
    static std::string header_includes();
    static std::string class_name();
    static std::string source_preamble();
    static std::string source_includes();
    static std::string header();
    static std::string source();
    static std::string header_single_declaration();
    static std::string source_single_definition();
    static std::string source_single_getter();
    static std::string header_single_resource_name();
    static std::string source_return_plain_literal();
    static std::string source_return_compressed_literal();

public:
    typedef std::string(*ResourceGetter)();
public: // key/value api
template <typename TInserter>
static void GetKeys(TInserter inserter) {
    static const char* keys[] = {
        "header_preamble",
        "header_includes",
        "class_name",
        "source_preamble",
        "source_includes",
        "header",
        "source",
        "header_single_declaration",
        "source_single_definition",
        "source_single_getter",
        "header_single_resource_name",
        "source_return_plain_literal",
        "source_return_compressed_literal",
    };
    for (auto key : keys) {
        inserter(key);
    }
}
public: // key/value api
    static std::string Get(std::string const& key);
public:
    static std::string OnNoKey(std::string const& key="") {
        return "";
    }
};
}
