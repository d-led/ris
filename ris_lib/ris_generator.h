#pragma once

#include <iostream>

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
					<< "    static char const literal[] = { ";
					//0, 1, 2, 0, 1 
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
	};

	template <typename TSource>
	generator<TSource> get_generator(TSource&& s) {
		return generator<TSource>(s);
	}
}
