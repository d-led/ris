#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"

#include <iostream>
#include <fstream>
#include <string>

void print_usage() {
	std::cout
		<<"USAGE:"<<std::endl
		<<"       ris <path_to>/ris.json"<<std::endl
	;	
}

void process(char const* path) {
	std::cout << "processing " << path << std::endl;
	auto r=ris::json_resources(path);
	auto g=ris::get_generator(r);

	const std::string header_filename("ris.h");
	std::ofstream header(header_filename);
	if (!header)
		throw std::runtime_error(std::string("cannot write ")+header_filename);

	g.generate_header(header);
	header.close();

	const std::string source_filename("ris.cpp");
	std::ofstream source(source_filename);
	if (!source)
		throw std::runtime_error(std::string("cannot write ")+source_filename);

	g.generate_source(source);
	source.close();
}

int main(int argc, char ** argv) {
	switch(argc) {
		case 2:
			try {
				process(argv[1]);
			} catch (std::exception& e) {
				std::cerr<<"Error: "<< e.what() <<std::endl;
				return 1;
			}
			break;
		default:
			print_usage();
	}
}
