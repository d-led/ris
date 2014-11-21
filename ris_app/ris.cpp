#include <iostream>
#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"

void print_usage() {
	std::cout
		<<"USAGE:"<<std::endl
		<<"       ris <path_to>/ris.json"<<std::endl
	;	
}

void process(char const* path) {
	std::cout << "processing " << path << std::endl;
	auto r=ris::json_resources(path);
	auto g=ris::generator();
	g.generate_header(std::cout);
	std::cout<<std::endl;
	g.generate_source(std::cout);
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
