#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"
#include "../ris_lib/ris_bundle_compression.h"
#include "../ris_lib/ris_writing_files.h"
#include "../ris_lib/template.h"
#include "../ris_lib/ris_resource_loader.h"
#include "../ris_lib/ris_default_or_from_file.h"

#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/filesystem.hpp>

void print_usage() {
    std::cout
        << "USAGE:" << std::endl
        << "       ris <path_to>/ris.json" << std::endl
        ;
}

void process(std::string const& path, std::string const& source_template) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "reading " << full_path.generic_string() << std::endl;
    auto r = ris::json_resources(path);
    std::cout << "read " << r.resources().resources.size() << " resources" << std::endl;
    auto c = ris::bundle_compression();
    auto t = ris::default_or_from_file<ris::Resource>(source_template);
    auto g = ris::get_generator(r, c, t);

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
    std::string source_template;

    switch (argc) {
        case 3:
            source_template = argv[2];
            // fall through
        case 2:
            try {
                process(argv[1], source_template);
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            }
            break;
        default:
            print_usage();
    }
}
