#pragma once
#include <string>
namespace test {
class Resource /*final*/ {
public:
    typedef std::string(*ResourceGetter)();
public:
    static std::string string_test();
    static std::string binary_file_test();
    static std::string itself();
public: // key/value api
template <typename TInserter>
static void GetKeys(TInserter inserter) {
static const char* keys[] = {
    "string_test",
    "binary_file_test",
    "itself",
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
