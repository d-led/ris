/* This file has been generated using ris, do not modify! */
#include "resource.h"
#include <unordered_map>
#include <bundle.hpp>
namespace test {
std::string Resource::string_test() {
    static char const literal[] =  {
        112, 108, 97, 105, 110, 32, 116, 101, 120, 116, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::binary_file_test() {
    static char const literal[] =  {
        49, 50, 51, 10, 49, 50, 51, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::itself() {
    static char const literal[] =  {
        123, 13, 10, 32, 32, 32, 34, 104, 101, 97, 100, 101, 114, 34, 32, 58, 32, 34, 97, 99, 99, 101, 112, 116, 97, 110, 99, 101, 95, 116, 101, 115, 116, 47, 114, 101, 115, 111, 117, 114, 99, 101, 46, 104, 34, 44, 13, 10, 32, 32, 32, 34, 110, 97, 109, 101, 115, 112, 97, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 34, 44, 13, 10, 9, 34, 99, 108, 97, 115, 115, 34, 32, 58, 32, 34, 82, 101, 115, 111, 117, 114, 99, 101, 34, 44, 13, 10, 32, 32, 32,         34, 114, 101, 115, 111, 117, 114, 99, 101, 115, 34, 32, 58, 32, 91, 13, 10, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 115, 116, 114, 105, 110, 103, 95, 116, 101, 115, 116, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 112, 108, 97, 105, 110, 32, 116, 101, 120, 116, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32,         32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 115, 116, 114, 105, 110, 103, 34, 13, 10, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 98, 105, 110, 97, 114, 121, 95, 102, 105, 108, 101, 95, 116, 101, 115, 116, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114,         99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 46, 98, 105, 110, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 102, 105, 108, 101, 34, 13, 10, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 105, 116, 115, 101, 108, 102, 34, 44, 13, 10, 32,         32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 46, 106, 115, 111, 110, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 102, 105, 108, 101, 34, 13, 10, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 99, 111, 109, 112, 114, 101,         115, 115, 105, 111, 110, 34, 32, 58, 32, 34, 76, 90, 52, 72, 67, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 105, 116, 115, 101, 108, 102, 95, 112, 97, 99, 107, 101, 100, 95, 108, 122, 52, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 46, 106, 115, 111, 110, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32,         32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 102, 105, 108, 101, 34, 13, 10, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 109, 101, 109, 98, 101, 114, 95, 110, 97, 109, 101, 34, 32, 58, 32, 34, 99, 117, 115, 116, 111, 109, 95, 109, 101, 109, 98, 101, 114, 95, 110, 97, 109, 101, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32,         34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 99, 117, 115, 116, 111, 109, 46, 109, 101, 109, 98, 101, 114, 47, 110, 97, 109, 101, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 115, 116, 114, 105, 110, 103, 34, 13, 10, 32, 32, 32, 32, 32,         32, 125, 13, 10, 32, 32, 32, 93, 44, 13, 10, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 97, 99, 99, 101, 112, 116, 97, 110, 99, 101, 95, 116, 101, 115, 116, 47, 114, 101, 115, 111, 117, 114, 99, 101, 46, 99, 112, 112, 34, 13, 10, 125, 13, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::itself_packed_lz4() {
    static char const literal[] =  {
        0, 119, -28, 6, -69, 2, -14, 31, 123, 13, 10, 32, 32, 32, 34, 104, 101, 97, 100, 101, 114, 34, 32, 58, 32, 34, 97, 99, 99, 101, 112, 116, 97, 110, 99, 101, 95, 116, 101, 115, 116, 47, 114, 101, 115, 111, 117, 114, 99, 101, 46, 104, 34, 44, 45, 0, -111, 110, 97, 109, 101, 115, 112, 97, 99, 101, 48, 0, 0, 37, 0, 0, 26, 0, 113, 9, 34, 99, 108, 97, 115, 115, 20, 0, 19, 82, 52, 0, 4, 50, 0, 4, 68, 0, 1, 30, 0, 17, 91, 20, 0,         50, 32, 32, 32, 124, 0, 2, 1, 0, 1, 85, 0, 1, 60, 0, 116, 115, 116, 114, 105, 110, 103, 95, 87, 0, 6, 34, 0, 3, 83, 0, 0, 36, 0, -97, 112, 108, 97, 105, 110, 32, 116, 101, 120, 35, 0, 2, 72, 95, 116, 121, 112, 76, 0, 20, 34, 35, 0, 47, 125, 44, 123, 0, 11, -65, 98, 105, 110, 97, 114, 121, 95, 102, 105, 108, 101, -128, 0, 11, 0, 29, 0, 79, 46, 98, 105, 110, 126, 0, 11, 0, 72, 0, 15, 124, 0, 22, 111, 105, 116, 115,         101, 108, 102, 114, 0, 11, 63, 106, 115, 111, 115, 0, 48, -79, 99, 111, 109, 112, 114, 101, 115, 115, 105, 111, 110, 52, 0, 127, 76, 90, 52, 72, 67, 34, 44, -106, 0, 8, -65, 95, 112, 97, 99, 107, 101, 100, 95, 108, 122, 52, -95, 0, 81, 117, 109, 101, 109, 98, 101, 114, 95, -123, 0, 120, 99, 117, 115, 116, 111, 109, 95, 23, 0, 15, -82, 0, 3, 2, 41, 0, 18, 46, 41, 0, 30, 47, 41, 0, 11, -81, 0, 15, 60, 2, 27, 1, 9, 0, 19, 93, -47,         2, 7, 74, 0, 15, 48, 3, 6, -112, 99, 112, 112, 34, 13, 10, 125, 13, 10, 
    };
    return bundle::unpack(std::string(literal, sizeof(literal)/sizeof(char)));
}
std::string Resource::custom_member_name() {
    static char const literal[] =  {
        116, 101, 115, 116, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::Get(std::string const& key) {
    static std::unordered_map<std::string,ResourceGetter> getters = {
        { "string_test", Resource::string_test },
        { "binary_file_test", Resource::binary_file_test },
        { "itself", Resource::itself },
        { "itself_packed_lz4", Resource::itself_packed_lz4 },
        { "custom.member/name", Resource::custom_member_name },
    };
    auto getter = getters.find(key);
    if (getter == getters.end())
         return OnNoKey(key);
    return getter->second();
}
}
