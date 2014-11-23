#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"
#include "../ris_lib/ris_bundle_compression.h"

#include <iostream>
#include <fstream>
#include <string>

#include <boost/filesystem/path.hpp>

void print_usage() {
    std::cout
        <<"USAGE:"<<std::endl
        <<"       ris <path_to>/ris.json"<<std::endl
    ;	
}

void process(char const* path) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "processing " << full_path.generic_string() << std::endl;
    auto r = ris::json_resources(path);
    std::cout << "read " << r.resources().resources.size() << " resources" << std::endl;
    auto c = ris::bundle_compression();
    auto g = ris::get_generator(r,c);

    std::ofstream header(r.header());
    if (!header)
        throw std::runtime_error(std::string("cannot write ")+r.header());

    g.generate_header(header);
    header.close();

    std::ofstream source(r.source());
    if (!source)
        throw std::runtime_error(std::string("cannot write ")+r.source());

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
