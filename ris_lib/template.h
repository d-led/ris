#pragma once
/* This file has been generated using ris, do not modify! */
#include <string>
namespace ris {
class Resource /*final*/ {
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
    static std::string source_includes();
    static std::string source_getters_begin();
    static std::string source_getters_end();
public:
    typedef std::string(*ResourceGetter)();
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
        "source_includes",
        "source_getters_begin",
        "source_getters_end",
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
