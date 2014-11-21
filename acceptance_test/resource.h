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
    static std::string Get(std::string const& key);
public:
    static std::string OnNoKey() {
        // could be configured to throw
        return "";
    }
};
}
