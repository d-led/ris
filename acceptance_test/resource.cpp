#include "resource.h"
#include <unordered_map>
namespace test {
std::string Resource::string_test() {
    static char const literal[] =  {
        112, 108, 97, 105, 110, 32, 116, 101, 120, 116, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::binary_file_test() {
    static char const literal[] =  {
        49, 50, 51, 10, 49, 50, 51, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::itself() {
    static char const literal[] =  {
        123, 13, 10, 32, 32, 32, 32, 34, 110, 97, 109, 101, 115, 112, 97, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 34, 44, 13, 10, 32, 32, 32, 32, 34, 104, 101, 97, 100, 101, 114, 34, 32, 58, 32, 34, 97, 99, 99, 101, 112, 116, 97, 110, 99, 101, 95, 116, 101, 115, 116, 47, 114, 101, 115, 111, 117, 114, 99, 101, 46, 104, 34, 44, 13, 10, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 97, 99, 99, 101, 112, 116, 97, 110, 99, 
        101, 95, 116, 101, 115, 116, 47, 114, 101, 115, 111, 117, 114, 99, 101, 46, 99, 112, 112, 34, 44, 13, 10, 32, 32, 32, 32, 34, 114, 101, 115, 111, 117, 114, 99, 101, 115, 34, 32, 58, 32, 91, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 115, 116, 114, 105, 110, 103, 95, 116, 101, 115, 116, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
        32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 115, 116, 114, 105, 110, 103, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 112, 108, 97, 105, 110, 32, 116, 101, 120, 116, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
        32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 98, 105, 110, 97, 114, 121, 95, 102, 105, 108, 101, 95, 116, 101, 115, 116, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 102, 105, 108, 101, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 46, 98, 105, 110, 34, 
        13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 105, 116, 115, 101, 108, 102, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 102, 105, 108, 101, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 
        32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 46, 106, 115, 111, 110, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 125, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 123, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 110, 97, 109, 101, 34, 32, 58, 32, 34, 105, 116, 115, 101, 108, 102, 95, 112, 97, 99, 107, 101, 100, 95, 108, 122, 52, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 
        32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 95, 116, 121, 112, 101, 34, 32, 58, 32, 34, 102, 105, 108, 101, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 115, 111, 117, 114, 99, 101, 34, 58, 32, 34, 116, 101, 115, 116, 46, 106, 115, 111, 110, 34, 44, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 99, 111, 109, 112, 114, 101, 115, 115, 105, 111, 110, 34, 32, 58, 32, 34, 76, 90, 52, 72, 67, 
        34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 125, 13, 10, 32, 32, 32, 32, 93, 13, 10, 125, 13, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::itself_packed_lz4() {
    static char const literal[] =  {
        0, 119, -37, 5, -120, 2, -13, 13, 123, 13, 10, 32, 32, 32, 32, 34, 110, 97, 109, 101, 115, 112, 97, 99, 101, 34, 32, 58, 32, 34, 116, 101, 115, 116, 34, 44, 27, 0, 97, 104, 101, 97, 100, 101, 114, 24, 0, -80, 97, 99, 99, 101, 112, 116, 97, 110, 99, 101, 95, 35, 0, -75, 47, 114, 101, 115, 111, 117, 114, 99, 101, 46, 104, 46, 0, 2, 17, 0, 15, 46, 0, 11, 53, 99, 112, 112, 48, 0, 4, 21, 0, 16, 115, 51, 0, 18, 91, 21, 0, 0, 1, 
        0, 3, -103, 0, 4, 1, 0, 1, -95, 0, 1, 86, 0, 120, 115, 116, 114, 105, 110, 103, 95, -93, 0, 5, 37, 0, 2, 125, 0, 72, 95, 116, 121, 112, 44, 0, 15, 39, 0, 4, 1, 34, 0, -74, 112, 108, 97, 105, 110, 32, 116, 101, 120, 116, 34, 37, 0, 47, 125, 44, -120, 0, 16, -65, 98, 105, 110, 97, 114, 121, 95, 102, 105, 108, 101, -115, 0, 19, 0, 42, 0, 15, -117, 0, 9, 0, 69, 0, 79, 46, 98, 105, 110, -119, 0, 29, 111, 105, 116, 115, 101, 
        108, 102, 127, 0, 51, 63, 106, 115, 111, -128, 0, 36, -65, 95, 112, 97, 99, 107, 101, 100, 95, 108, 122, 52, -117, 0, 42, 9, -118, 0, 12, 36, 0, -79, 99, 111, 109, 112, 114, 101, 115, 115, 105, 111, 110, 73, 0, 88, 76, 90, 52, 72, 67, -80, 0, -64, 13, 10, 32, 32, 32, 32, 93, 13, 10, 125, 13, 10, 
    };
    return bundle::unpack(std::string(literal, sizeof(literal)/sizeof(char)));
}
std::string Resource::Get(std::string const& key) {
    static std::unordered_map<std::string,ResourceGetter> getters = {
        { "string_test", Resource::string_test },
        { "binary_file_test", Resource::binary_file_test },
        { "itself", Resource::itself },
        { "itself_packed_lz4", Resource::itself_packed_lz4 },
    };
    auto getter = getters.find(key);
    if (getter == getters.end())
         return OnNoKey();
    return getter->second();
}
}
