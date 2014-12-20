/* This file has been generated using ris, do not modify! */
#include "template.h"
#include <unordered_map>
namespace ris {
std::string Resource::header_preamble() {
    static char const literal[] = {
        47, 42, 32, 84, 104, 105, 115, 32, 102, 105, 108, 101, 32, 104, 97, 115, 32, 98, 101, 101, 110, 32, 103, 101, 110, 101, 114, 97, 116, 101, 100, 32, 117, 115, 105, 110, 103, 32, 114, 105, 115, 44, 32, 100, 111, 32, 110, 111, 116, 32, 109, 111, 100, 105, 102, 121, 33, 32, 42, 47, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::header_includes() {
    static char const literal[] = {
        35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 115, 116, 114, 105, 110, 103, 62, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::class_name() {
    static char const literal[] = {
        82, 101, 115, 111, 117, 114, 99, 101, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source_preamble() {
    static char const literal[] = {
        47, 42, 32, 84, 104, 105, 115, 32, 102, 105, 108, 101, 32, 104, 97, 115, 32, 98, 101, 101, 110, 32, 103, 101, 110, 101, 114, 97, 116, 101, 100, 32, 117, 115, 105, 110, 103, 32, 114, 105, 115, 44, 32, 100, 111, 32, 110, 111, 116, 32, 109, 111, 100, 105, 102, 121, 33, 32, 42, 47, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source_includes() {
    static char const literal[] = {
        35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 117, 110, 111, 114, 100, 101, 114, 101, 100, 95, 109, 97, 112, 62, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::header() {
    static char const literal[] = {
        35, 112, 114, 97, 103, 109, 97, 32, 111, 110, 99, 101, 10, 123, 123, 104, 101, 97, 100, 101, 114, 95, 112, 114, 101, 97, 109, 98, 108, 101, 125, 125, 10, 123, 123, 104, 101, 97, 100, 101, 114, 95, 105, 110, 99, 108, 117, 100, 101, 115, 125, 125, 10, 110, 97, 109, 101, 115, 112, 97, 99, 101, 32, 123, 123, 110, 97, 109, 101, 115, 112, 97, 99, 101, 95, 110, 97, 109, 101, 125, 125, 32, 123, 10, 99, 108, 97, 115, 115, 32, 123, 123, 99, 108, 97, 115, 115, 95, 110, 97, 
        109, 101, 125, 125, 32, 47, 42, 102, 105, 110, 97, 108, 42, 47, 32, 123, 10, 112, 117, 98, 108, 105, 99, 58, 10, 123, 123, 104, 101, 97, 100, 101, 114, 95, 100, 101, 99, 108, 97, 114, 97, 116, 105, 111, 110, 115, 125, 125, 10, 112, 117, 98, 108, 105, 99, 58, 10, 32, 32, 32, 32, 116, 121, 112, 101, 100, 101, 102, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 40, 42, 82, 101, 115, 111, 117, 114, 99, 101, 71, 101, 116, 116, 101, 114, 41, 40, 41, 59, 
        10, 112, 117, 98, 108, 105, 99, 58, 32, 47, 47, 32, 107, 101, 121, 47, 118, 97, 108, 117, 101, 32, 97, 112, 105, 10, 116, 101, 109, 112, 108, 97, 116, 101, 32, 60, 116, 121, 112, 101, 110, 97, 109, 101, 32, 84, 73, 110, 115, 101, 114, 116, 101, 114, 62, 10, 115, 116, 97, 116, 105, 99, 32, 118, 111, 105, 100, 32, 71, 101, 116, 75, 101, 121, 115, 40, 84, 73, 110, 115, 101, 114, 116, 101, 114, 32, 105, 110, 115, 101, 114, 116, 101, 114, 41, 32, 123, 10, 32, 32, 
        32, 32, 115, 116, 97, 116, 105, 99, 32, 99, 111, 110, 115, 116, 32, 99, 104, 97, 114, 42, 32, 107, 101, 121, 115, 91, 93, 32, 61, 32, 123, 10, 123, 123, 104, 101, 97, 100, 101, 114, 95, 114, 101, 115, 111, 117, 114, 99, 101, 95, 110, 97, 109, 101, 115, 125, 125, 32, 32, 32, 32, 125, 59, 10, 32, 32, 32, 32, 102, 111, 114, 32, 40, 97, 117, 116, 111, 32, 107, 101, 121, 32, 58, 32, 107, 101, 121, 115, 41, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 
        105, 110, 115, 101, 114, 116, 101, 114, 40, 107, 101, 121, 41, 59, 10, 32, 32, 32, 32, 125, 10, 125, 10, 112, 117, 98, 108, 105, 99, 58, 32, 47, 47, 32, 107, 101, 121, 47, 118, 97, 108, 117, 101, 32, 97, 112, 105, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 71, 101, 116, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 99, 111, 110, 115, 116, 38, 32, 107, 101, 121, 41, 59, 10, 
        112, 117, 98, 108, 105, 99, 58, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 79, 110, 78, 111, 75, 101, 121, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 99, 111, 110, 115, 116, 38, 32, 107, 101, 121, 61, 34, 34, 41, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 34, 34, 59, 10, 32, 32, 32, 32, 125, 10, 125, 59, 10, 125, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source() {
    static char const literal[] = {
        123, 123, 115, 111, 117, 114, 99, 101, 95, 112, 114, 101, 97, 109, 98, 108, 101, 125, 125, 10, 123, 123, 115, 111, 117, 114, 99, 101, 95, 100, 101, 102, 97, 117, 108, 116, 95, 105, 110, 99, 108, 117, 100, 101, 125, 125, 10, 123, 123, 115, 111, 117, 114, 99, 101, 95, 105, 110, 99, 108, 117, 100, 101, 115, 125, 125, 10, 123, 123, 111, 112, 116, 105, 111, 110, 97, 108, 95, 99, 111, 109, 112, 114, 101, 115, 115, 105, 111, 110, 95, 104, 101, 97, 100, 101, 114, 125, 125, 110, 97, 
        109, 101, 115, 112, 97, 99, 101, 32, 123, 123, 110, 97, 109, 101, 115, 112, 97, 99, 101, 95, 110, 97, 109, 101, 125, 125, 32, 123, 10, 123, 123, 115, 111, 117, 114, 99, 101, 95, 100, 101, 102, 105, 110, 105, 116, 105, 111, 110, 115, 125, 125, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 82, 101, 115, 111, 117, 114, 99, 101, 58, 58, 71, 101, 116, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 99, 111, 110, 115, 116, 38, 32, 107, 101, 121, 41, 
        32, 123, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 117, 110, 111, 114, 100, 101, 114, 101, 100, 95, 109, 97, 112, 60, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 44, 82, 101, 115, 111, 117, 114, 99, 101, 71, 101, 116, 116, 101, 114, 62, 32, 103, 101, 116, 116, 101, 114, 115, 32, 61, 32, 123, 10, 123, 123, 115, 111, 117, 114, 99, 101, 95, 103, 101, 116, 116, 101, 114, 115, 125, 125, 32, 32, 32, 32, 125, 59, 10, 32, 32, 
        32, 32, 97, 117, 116, 111, 32, 103, 101, 116, 116, 101, 114, 32, 61, 32, 103, 101, 116, 116, 101, 114, 115, 46, 102, 105, 110, 100, 40, 107, 101, 121, 41, 59, 10, 32, 32, 32, 32, 105, 102, 32, 40, 103, 101, 116, 116, 101, 114, 32, 61, 61, 32, 103, 101, 116, 116, 101, 114, 115, 46, 101, 110, 100, 40, 41, 41, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 79, 110, 78, 111, 75, 101, 121, 40, 107, 101, 121, 41, 59, 10, 32, 32, 
        32, 32, 114, 101, 116, 117, 114, 110, 32, 103, 101, 116, 116, 101, 114, 45, 62, 115, 101, 99, 111, 110, 100, 40, 41, 59, 10, 125, 10, 125, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::header_single_declaration() {
    static char const literal[] = {
        32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 123, 123, 114, 101, 115, 111, 117, 114, 99, 101, 95, 109, 101, 109, 98, 101, 114, 95, 110, 97, 109, 101, 125, 125, 40, 41, 59, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source_single_definition() {
    static char const literal[] = {
        115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 32, 82, 101, 115, 111, 117, 114, 99, 101, 58, 58, 123, 123, 114, 101, 115, 111, 117, 114, 99, 101, 95, 109, 101, 109, 98, 101, 114, 95, 110, 97, 109, 101, 125, 125, 40, 41, 32, 123, 10, 32, 32, 32, 32, 115, 116, 97, 116, 105, 99, 32, 99, 104, 97, 114, 32, 99, 111, 110, 115, 116, 32, 108, 105, 116, 101, 114, 97, 108, 91, 93, 32, 61, 32, 123, 123, 123, 115, 111, 117, 114, 99, 101, 95, 108, 105, 116, 101, 114, 
        97, 108, 95, 98, 121, 116, 101, 115, 125, 125, 10, 32, 32, 32, 32, 125, 59, 10, 123, 123, 115, 111, 117, 114, 99, 101, 95, 114, 101, 116, 117, 114, 110, 95, 108, 105, 116, 101, 114, 97, 108, 125, 125, 10, 125, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source_single_getter() {
    static char const literal[] = {
        32, 32, 32, 32, 32, 32, 32, 32, 123, 32, 34, 123, 123, 114, 101, 115, 111, 117, 114, 99, 101, 95, 110, 97, 109, 101, 125, 125, 34, 44, 32, 123, 123, 99, 108, 97, 115, 115, 95, 110, 97, 109, 101, 125, 125, 58, 58, 123, 123, 114, 101, 115, 111, 117, 114, 99, 101, 95, 109, 101, 109, 98, 101, 114, 95, 110, 97, 109, 101, 125, 125, 32, 125, 44, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::header_single_resource_name() {
    static char const literal[] = {
        32, 32, 32, 32, 32, 32, 32, 32, 34, 123, 123, 114, 101, 115, 111, 117, 114, 99, 101, 95, 110, 97, 109, 101, 125, 125, 34, 44, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source_return_plain_literal() {
    static char const literal[] = {
        32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 40, 108, 105, 116, 101, 114, 97, 108, 44, 32, 115, 105, 122, 101, 111, 102, 40, 108, 105, 116, 101, 114, 97, 108, 41, 47, 115, 105, 122, 101, 111, 102, 40, 99, 104, 97, 114, 41, 41, 59, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::source_return_compressed_literal() {
    static char const literal[] = {
        32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 98, 117, 110, 100, 108, 101, 58, 58, 117, 110, 112, 97, 99, 107, 40, 115, 116, 100, 58, 58, 115, 116, 114, 105, 110, 103, 40, 108, 105, 116, 101, 114, 97, 108, 44, 32, 115, 105, 122, 101, 111, 102, 40, 108, 105, 116, 101, 114, 97, 108, 41, 47, 115, 105, 122, 101, 111, 102, 40, 99, 104, 97, 114, 41, 41, 41, 59, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::Get(std::string const& key) {
    static std::unordered_map<std::string,ResourceGetter> getters = {
        { "header_preamble", Resource::header_preamble },
        { "header_includes", Resource::header_includes },
        { "class_name", Resource::class_name },
        { "source_preamble", Resource::source_preamble },
        { "source_includes", Resource::source_includes },
        { "header", Resource::header },
        { "source", Resource::source },
        { "header_single_declaration", Resource::header_single_declaration },
        { "source_single_definition", Resource::source_single_definition },
        { "source_single_getter", Resource::source_single_getter },
        { "header_single_resource_name", Resource::header_single_resource_name },
        { "source_return_plain_literal", Resource::source_return_plain_literal },
        { "source_return_compressed_literal", Resource::source_return_compressed_literal },
    };
    auto getter = getters.find(key);
    if (getter == getters.end())
         return OnNoKey(key);
    return getter->second();
}
}
