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
			s
				<< "#pragma once\n"
				<< "#include <string>\n"
				<< "class Resource /*final*/ {\n"
				<< "public:\n"
				<< "	typedef std::string(*ResourceGetter)();\n"
				<< "public:\n"
			;
				//variable part
			s
				<< "public: // key/value api\n"
				<< "	static std::string Get(std::string const& key);\n"
				<< "public:\n"
				<< "	static std::string OnNoKey() {\n"
				<< "		// can be throwing or not\n"
				<< "		return "";\n"
				<< "	}\n"
				<< "};\n"
			;
		}

		template <typename TStream>
		void generate_source(TStream& s) {
			s

				<< "#include \"resource.h\"\n"
				<< "#include <unordered_map>\n"
				<< "std::string Resource::Get(std::string const& key) {\n"
				<< "	static std::unordered_map<std::string,ResourceGetter> getters\n"
			;
				// variable part
			s
				<< "	;\n"
				<< "	auto getter = getters.find(key);\n"
				<< "	if (getter == getters.end())\n"
				<< "		return OnNoKey();\n"
				<< "	return getter->second();\n"
				<< "}\n"
			;
		}
	};

	template <typename TSource>
	generator<TSource> get_generator(TSource&& s) {
		return generator<TSource>(s);
	}
}
