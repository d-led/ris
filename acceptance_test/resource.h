#pragma once
/* This file has been generated using ris, do not modify! */
#include <string>
#include <bundle.hpp>
namespace test {
class Resource /*final*/ {
public:
    static std::string string_test();
    static std::string binary_file_test();
    static std::string itself();
    static std::string itself_packed_lz4();
    static std::string custom_member_name();
public:
    typedef std::string(*ResourceGetter)();
public: // key/value api
template <typename TInserter>
static void GetKeys(TInserter inserter) {
    static const char* keys[] = {
        "string_test",
        "binary_file_test",
        "itself",
        "itself_packed_lz4",
        "custom.member/name",
    };
    for (auto key : keys) {
        inserter(key);
    }
}
public: // key/value api
    static std::string Get(std::string const& key);
public:
    static std::string OnNoKey(std::string const& key="") {
        // could be configured to throw
        return "";
    }
};
}
