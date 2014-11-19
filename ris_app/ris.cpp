#include <iostream>

void print_usage() {
	std::cout
		<<"USAGE:"<<std::endl
		<<"       ris <path_to>/ris.json"<<std::endl
	;	
}

int main(int argc, char ** argv) {
	switch(argc) {
		case 2:
			std::cout << "processing " << argv[1] << std::endl;
		default:
			print_usage();
	}
}
