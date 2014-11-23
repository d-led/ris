#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"
#include "../ris_lib/ris_bundle_compression.h"
#include "../ris_lib/ris_writing_files.h"

#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

void print_usage() {
    std::cout
        <<"USAGE:"<<std::endl
        <<"       ris <path_to>/ris.json"<<std::endl
    ;	
}

void process(char const* path) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "reading " << full_path.generic_string() << std::endl;
    auto r = ris::json_resources(path);
    std::cout << "read " << r.resources().resources.size() << " resources" << std::endl;
    auto c = ris::bundle_compression();
    auto g = ris::get_generator(r,c);

    ris::write_to_temp_first_then_move header([&g](std::ostream& s) {
        g.generate_header(s);
    }, r.header());
    header.start();

    ris::write_to_temp_first_then_move source([&g](std::ostream& s) {
        g.generate_source(s);
    }, r.source());
    source.start();
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
