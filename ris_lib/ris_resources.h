#pragma once

#include <picojson_vector_serializer.h>
#include <picojson.h>

namespace ris {

	struct resource {
		std::string name;
        std::string source_type;
        std::string source;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("name", name);
            ar & picojson::convert::member("source_type", source_type);
            ar & picojson::convert::member("source", source);
        }
	};

	struct resource_collection {
        std::string namespace_;
		std::vector<resource> resources;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("namespace", namespace_);
            ar & picojson::convert::member("resources", resources);
        }
	};
}
