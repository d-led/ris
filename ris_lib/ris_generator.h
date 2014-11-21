#pragma once

#include "ris_resources.h"

#include <fstream>
#include <string>
#include <stdexcept>

#include <boost/filesystem.hpp>

namespace ris {

	template <typename TSource>
	class generator {
		TSource&& source;

	public:
		generator(TSource&& s):source(s){}

	public:
		template <typename TStream>
		void generate_header(TStream& s) {
			auto& resources = source.resources();

			s
				<< "#pragma once\n"
				<< "#include <string>\n"

			;

			if (!resources.namespace_.empty())
				s << "namespace " << resources.namespace_ << " {\n";

			s
				<< "class Resource /*final*/ {\n"
				<< "public:\n"
				<< "    typedef std::string(*ResourceGetter)();\n"
				<< "public:\n"
			;

			for (auto& resource: resources.resources) {
				s
				<< "    static std::string " << resource.name << "();\n";
			}

			s
				<< "public: // key/value api\n"
				<< "    static std::string Get(std::string const& key);\n"
				<< "public:\n"
				<< "    static std::string OnNoKey() {\n"
				<< "        // can be throwing or not\n"
				<< "        return "";\n"
				<< "	}\n"
				<< "};\n"
			;

			if (!resources.namespace_.empty())
				s << "}\n";
		}

		template <typename TStream>
		void generate_source(TStream& s) {
			auto& resources = source.resources();

			s

				<< "#include \"resource.h\"\n"
				<< "#include <unordered_map>\n"
			;

			if (!resources.namespace_.empty())
				s << "namespace " << resources.namespace_ << " {\n";

			for (auto& resource: resources.resources) {
				s
					<< "std::string Resource::" << resource.name << "()\n"
					<< "    static char const literal[] = { "
				;

				stream_resource(s,resource);

				s
					<< "};\n"
					<< "    return std::string(literal, sizeof(literal)/sizeof(char));\n"
					<< "}\n"
				;
			}

			s
				<< "std::string Resource::Get(std::string const& key) {\n"
				<< "    static std::unordered_map<std::string,ResourceGetter> getters = {\n"
			;

			for (auto& resource: resources.resources) {
				s
					<< "        { \"" << resource.name << "\", Resource::" << resource.name << " },\n"
				;
			}

			s
				<< "    };\n"
				<< "    auto getter = getters.find(key);\n"
				<< "    if (getter == getters.end())\n"
				<< "         return OnNoKey();\n"
				<< "    return getter->second();\n"
				<< "}\n"
			;

			if (!resources.namespace_.empty())
				s << "}\n";
		}

	private:
		template <typename TStream>
		void stream_resource(TStream& s,resource const& res) {
			std::string data = get_resource_data(res);
		}

		std::string get_resource_data(resource const& res) {
			if (res.source_type == "string")
				return res.source;
			else if (res.source_type == "file")
				return read_file_contents_binary(res.source);

			return "";
		}

		std::string read_file_contents_binary(std::string const& filename) {
			std::ifstream file(filename, std::ios::binary);
			if (!file)
				throw std::runtime_error(std::string("cannot open "+filename));
			return std::string(std::istreambuf_iterator<char>(file),
                               std::istreambuf_iterator<char>());
		}
	};

	template <typename TSource>
	generator<TSource> get_generator(TSource&& s) {
		return generator<TSource>(s);
	}
}
