#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"
#include "../ris_lib/ris_bundle_compression.h"
#include "../ris_lib/ris_writing_files.h"
#include "../ris_lib/template.h"
#include "../ris_lib/ris_resource_loader.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>

#include <boost/filesystem.hpp>

void print_usage() {
    std::cout
        <<"USAGE:"<<std::endl
        <<"       ris <path_to>/ris.json"<<std::endl
    ;	
}

struct default_or_from_file {
    std::string header_;
    std::string source_;
    std::string namespace__;
    std::unordered_map<std::string,std::string> resources;
public:
    default_or_from_file(std::string const& t) {
        try_loading_resources(t);
    }

    std::string Get(std::string const& key) const {
        auto found = resources.find(key);
        return found != resources.end() ?
            found->second
            :
            ris::Resource::Get(key)
        ;
    }

    std::string source() const {
        return source_;
    }

    std::string header() const {
        return header_;
    }

    std::string namespace_() const {
        return namespace__;
    }

private:
    void try_loading_resources(std::string const& json_path) {
        try {
            auto base_dir = boost::filesystem::path(json_path).parent_path().generic_string();
            auto r = ris::json_resources(json_path);
            for (auto& res : r.resources().resources) {
                resources[res.name] = ris::resource_loader(res,base_dir).get();
            }
            std::cout<< "loaded "<<resources.size()<<" code generator overrides"<<std::endl;
            if (!r.header().empty()) {
                header_ = r.header();
                std::cout<<"overriding header output to: "<<header_<<std::endl;
            }
            if (!r.source().empty()) {
                source_ = r.source();
                std::cout<<"overriding source output to: "<<source_<<std::endl;
            }
            if (!r.namespace_().empty()) {
                namespace__ = r.namespace_();
                std::cout<<"overriding namespace to: "<<namespace__<<std::endl;
            }
        }
        catch(std::exception& e) {

        }
    }
};

void process(std::string const& path,std::string const& source_template) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "reading " << full_path.generic_string() << std::endl;
    auto r = ris::json_resources(path);
    std::cout << "read " << r.resources().resources.size() << " resources" << std::endl;
    auto c = ris::bundle_compression();
    auto t = default_or_from_file(source_template);
    r.override_header_if_not_empty(t.header());
    r.override_source_if_not_empty(t.source());
    r.override_namespace_if_not_empty(t.namespace_());
    auto g = ris::get_generator(r,c,t);

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
    
    switch(argc) {
        case 3:
            source_template = argv[2];
        case 2:
            try {
                process(argv[1],source_template);
            } catch (std::exception& e) {
                std::cerr<<"Error: "<< e.what() <<std::endl;
                return 1;
            }
            break;
        default:
            print_usage();
    }
}
