#pragma once
#include <picojson_serializer.h>
#include <picojson_vector_serializer.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

namespace ris {

	struct resource {
		std::string name;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("name", name);
        }
	};

	struct resource_collection {
		std::vector<resource> resources;

        template<class Archive>
        void json(Archive & ar)
        {
            ar & picojson::convert::member("resources", resources);
        }
	};

	class json_resources {
		resource_collection collection;

	public:
		json_resources(std::string const& json_path) {
			read_from_file(json_path);
		}

	private:
		void read_from_file(std::string const& json_path) {
			std::ifstream json_file(json_path);
			if (!json_file)
				throw std::runtime_error(std::string("not a valid json file: ")+json_path);
			picojson::value v;
			json_file >> v;
			std::string err = picojson::get_last_error();
			if (!err.empty())
				throw std::runtime_error(json_path+": "+err);

			picojson::convert::from_value(v,collection);

			std::cout<<"read "<<collection.resources.size()<<" resources"<<std::endl;
		}
	};
}
