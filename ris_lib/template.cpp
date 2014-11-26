/* This file has been generated using ris, do not modify! */
#include "template.h"
#include <unordered_map>
namespace ris {
std::string Resource::header_preamble() {
    static char const literal[] =  {
        47, 42, 32, 84, 104, 105, 115, 32, 102, 105, 108, 101, 32, 104, 97, 115, 32, 98, 101, 101, 110, 32, 103, 101, 110, 101, 114, 97, 116, 101, 100, 32, 117, 115, 105, 110, 103, 32, 114, 105, 115, 44, 32, 100, 111, 32, 110, 111, 116, 32, 109, 111, 100, 105, 102, 121, 33, 32, 42, 47, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_includes() {
    static char const literal[] =  {
        35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 115, 116, 114, 105, 110, 103, 62, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_class() {
    static char const literal[] =  {
        99, 108, 97, 115, 115, 32, 82, 101, 115, 111, 117, 114, 99, 101, 32, 47, 42, 102, 105, 110, 97, 108, 42, 47, 32, 123, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_key_getter_begin() {
    static char const literal[] =  {
        112, 117, 98, 108, 105, 99, 58, 10, 32, 32, 32, 32, 116, 121, 112, 101, 100, 101, 102, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 40, 42, 82, 101, 115, 111, 117, 114, 99, 101, 71, 101, 116, 116, 101, 114, 41, 40, 41, 59, 10, 112, 117, 98, 108, 105, 99, 58, 32, 47, 47, 32, 107, 101, 121, 47, 118, 97, 108, 117, 101, 32, 97, 112, 105, 10, 116, 101, 109, 112, 108, 97, 116, 101, 32, 60, 116, 121, 112, 101, 110, 97, 109, 101, 32, 84, 73, 110, 115, 101, 
        114, 116, 101, 114, 62, 10, 115, 116, 97, 116, 105, 99, 32, 118, 111, 105, 100, 32, 71, 101, 116, 75, 101, 121, 115, 40, 84, 73, 110, 115, 101, 114, 116, 101, 114, 32, 105, 110, 115, 101, 114, 116, 101, 114, 41, 32, 123, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 99, 111, 110, 115, 116, 32, 99, 104, 97, 114, 42, 32, 107, 101, 121, 115, 91, 93, 32, 61, 32, 123, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_key_getter_end() {
    static char const literal[] =  {
        32, 32, 32, 32, 125, 59, 10, 32, 32, 32, 32, 102, 111, 114, 32, 40, 97, 117, 116, 111, 32, 107, 101, 121, 32, 58, 32, 107, 101, 121, 115, 41, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 105, 110, 115, 101, 114, 116, 101, 114, 40, 107, 101, 121, 41, 59, 10, 32, 32, 32, 32, 125, 10, 125, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_key_value_getter() {
    static char const literal[] =  {
        112, 117, 98, 108, 105, 99, 58, 32, 47, 47, 32, 107, 101, 121, 47, 118, 97, 108, 117, 101, 32, 97, 112, 105, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 71, 101, 116, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 99, 111, 110, 115, 116, 38, 32, 107, 101, 121, 41, 59, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_on_no_key() {
    static char const literal[] =  {
        112, 117, 98, 108, 105, 99, 58, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 79, 110, 78, 111, 75, 101, 121, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 99, 111, 110, 115, 116, 38, 32, 107, 101, 121, 61, 34, 34, 41, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 47, 47, 32, 99, 111, 117, 108, 100, 32, 98, 101, 32, 99, 111, 110, 102, 105, 103, 117, 114, 101, 100, 32, 116, 111, 
        32, 116, 104, 114, 111, 119, 10, 32, 32, 32, 32, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 34, 34, 59, 10, 32, 32, 32, 32, 125, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::header_class_end() {
    static char const literal[] =  {
        125, 59, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::source_preamble() {
    static char const literal[] =  {
        47, 42, 32, 84, 104, 105, 115, 32, 102, 105, 108, 101, 32, 104, 97, 115, 32, 98, 101, 101, 110, 32, 103, 101, 110, 101, 114, 97, 116, 101, 100, 32, 117, 115, 105, 110, 103, 32, 114, 105, 115, 44, 32, 100, 111, 32, 110, 111, 116, 32, 109, 111, 100, 105, 102, 121, 33, 32, 42, 47, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::source_includes() {
    static char const literal[] =  {
        35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 117, 110, 111, 114, 100, 101, 114, 101, 100, 95, 109, 97, 112, 62, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::source_getters_begin() {
    static char const literal[] =  {
        115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 82, 101, 115, 111, 117, 114, 99, 101, 58, 58, 71, 101, 116, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 99, 111, 110, 115, 116, 38, 32, 107, 101, 121, 41, 32, 123, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 117, 110, 111, 114, 100, 101, 114, 101, 100, 95, 109, 97, 112, 60, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 44, 82, 101, 115, 111, 117, 114, 99, 
        101, 71, 101, 116, 116, 101, 114, 62, 32, 103, 101, 116, 116, 101, 114, 115, 32, 61, 32, 123, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::source_getters_end() {
    static char const literal[] =  {
        32, 32, 32, 32, 125, 59, 10, 32, 32, 32, 32, 97, 117, 116, 111, 32, 103, 101, 116, 116, 101, 114, 32, 61, 32, 103, 101, 116, 116, 101, 114, 115, 46, 102, 105, 110, 100, 40, 107, 101, 121, 41, 59, 10, 32, 32, 32, 32, 105, 102, 32, 40, 103, 101, 116, 116, 101, 114, 32, 61, 61, 32, 103, 101, 116, 116, 101, 114, 115, 46, 101, 110, 100, 40, 41, 41, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 79, 110, 78, 111, 75, 101, 121, 40, 
        107, 101, 121, 41, 59, 10, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 103, 101, 116, 116, 101, 114, 45, 62, 115, 101, 99, 111, 110, 100, 40, 41, 59, 10, 125, 10, 
    };
    return {literal, sizeof(literal)/sizeof(char)};
}
std::string Resource::Get(std::string const& key) {
    static std::unordered_map<std::string,ResourceGetter> getters = {
        { "header_preamble", Resource::header_preamble },
        { "header_includes", Resource::header_includes },
        { "header_class", Resource::header_class },
        { "header_key_getter_begin", Resource::header_key_getter_begin },
        { "header_key_getter_end", Resource::header_key_getter_end },
        { "header_key_value_getter", Resource::header_key_value_getter },
        { "header_on_no_key", Resource::header_on_no_key },
        { "header_class_end", Resource::header_class_end },
        { "source_preamble", Resource::source_preamble },
        { "source_includes", Resource::source_includes },
        { "source_getters_begin", Resource::source_getters_begin },
        { "source_getters_end", Resource::source_getters_end },
    };
    auto getter = getters.find(key);
    if (getter == getters.end())
         return OnNoKey(key);
    return getter->second();
}
}
