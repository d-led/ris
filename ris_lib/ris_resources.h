#pragma once

#include <picojson_vector_serializer.h>
#include <picojson.h>
#include <vector>

namespace ris {

    struct resource {
        std::string name;
        std::string source_type;
        std::string source;
        std::string compression;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("name", name);
            ar & picojson::convert::member("source_type", source_type);
            ar & picojson::convert::member("source", source);
            ar & picojson::convert::member("compression", compression);
        }
    };

    struct resource_collection {
        std::string namespace_;
        std::string header;
        std::string source;
        std::vector<resource> resources;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("namespace", namespace_);
            ar & picojson::convert::member("resources", resources);
            ar & picojson::convert::member("header", header);
            ar & picojson::convert::member("source", source);
        }
    };
}
