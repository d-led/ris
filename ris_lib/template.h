#pragma once
/* This file has been generated using ris, do not modify! */
#include <string>
#include <cstring>
namespace ris {
class Resource /*final*/ {
public:
    typedef std::string(*ResourceGetter)();
public:
    static std::string header_preamble();
    static std::string header_includes();
    static std::string header_class();
    static std::string header_key_getter_begin();
    static std::string header_key_getter_end();
    static std::string header_key_value_getter();
    static std::string header_on_no_key();
    static std::string header_class_end();
    static std::string source_preamble();
public: // key/value api
template <typename TInserter>
static void GetKeys(TInserter inserter) {
    static const char* keys[] = {
        "header_preamble",
        "header_includes",
        "header_class",
        "header_key_getter_begin",
        "header_key_getter_end",
        "header_key_value_getter",
        "header_on_no_key",
        "header_class_end",
        "source_preamble",
    };
    for (auto key : keys) {
        inserter(key);
    }
}
public: // key/value api
    static std::string Get(std::string const& key);
public:
    static std::string OnNoKey() {
        // could be configured to throw
        return "";
    }
};
}
