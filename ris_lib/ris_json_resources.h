#pragma once

#include "ris_resources.h"

#include <picojson_serializer.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

namespace ris {
	class json_resources {
		resource_collection collection;

	public:
		json_resources(std::string const& json_path) {
			read_from_file(json_path);
		}

		resource_collection const& resources() const {
			return collection;
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
