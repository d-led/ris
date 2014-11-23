#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"
#include "../ris_lib/ris_bundle_compression.h"

#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#include <boost/filesystem.hpp>

void print_usage() {
    std::cout
        <<"USAGE:"<<std::endl
        <<"       ris <path_to>/ris.json"<<std::endl
    ;	
}

class write_to_temp_first_then_move {
    std::function<void(std::ostream&)> action;
    boost::filesystem::path temp_file;
    boost::filesystem::path target_file;
public:
    template<typename TAction>
    write_to_temp_first_then_move(TAction a,std::string const& filename) :
        action(a),
        target_file(filename),
        temp_file(filename + "_")
    {}

    void start() {
        std::ofstream s(temp_file.generic_string());
        if (!s)
            throw std::runtime_error(std::string("cannot write ") + temp_file.generic_string());
        action(s);
        s.close();
        rename(temp_file, target_file);
    }

    ~write_to_temp_first_then_move() {
        try {
            if (exists(temp_file))
                remove(temp_file);
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

void process(char const* path) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "processing " << full_path.generic_string() << std::endl;
    auto r = ris::json_resources(path);
    std::cout << "read " << r.resources().resources.size() << " resources" << std::endl;
    auto c = ris::bundle_compression();
    auto g = ris::get_generator(r,c);

    write_to_temp_first_then_move header([&g](std::ostream& s) {
        g.generate_header(s);
    }, r.header());
    header.start();

    write_to_temp_first_then_move source([&g](std::ostream& s) {
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
