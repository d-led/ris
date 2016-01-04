#include "../ris_lib/ris_resources_from_file.h"
#include "../ris_lib/ris_bundle_compression.h"
#include "../ris_lib/ris_writing_files.h"
#include "../ris_lib/template.h"
#include "../ris_lib/ris_resource_loader.h"
#include "../ris_lib/ris_default_or_from_file.h"
#include "../ris_lib/ris_resource_snapshot.h"
#include "../ris_lib/ris_late_context.h"
#include "../ris_lib/ris_late.h"
#include "../ris_lib/ris_resource_loader.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>

#include <boost/filesystem.hpp>

void print_usage() {
    std::cout
        << "---      ris v0.3.1            ---" << std::endl
        << "a simple resource compiler for c++" << std::endl
        << "https://github.com/d-led/ris" << std::endl
        << "USAGE:" << std::endl
        << "       ris <path_to>/<resources>.[json/yml/yaml] [<template_overrides>.[json/yml/yaml]]" << std::endl << std::endl
        << "Available algorithms: " << ris::bundle_compression().available_algorithms() << std::endl << std::endl
        << "Minimal YAML resource file:"
        <<
R"(
#------------------------
header: "res.h"
source: "res.cpp"
namespace: "res"
class: "data"

resources:
  -
    #compression: "LZ4F" #compression needs including and linking to https://github.com/r-lyeh/bundle
    name: "some_text"
    source: "some text"
    source_type: "string"
#------------------------
)" << std::endl
        ;
}

template <typename TResource>
std::string member_name(TResource const& res) {
    if (!res.member_name.empty())
        return res.member_name;
    return res.name;
}

void process(std::string const& path, std::string const& source_template) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "reading " << full_path.generic_string() << std::endl;

    auto user_resources = ris::load_resources_from_file(path);
    auto lookup = user_resources.to_lookup();
    std::cout << "read " << user_resources.resources().resources.size() << " resources" << std::endl;

    auto compression = ris::bundle_compression();
    auto ris_res = ris::default_or_from_file<ris::Resource>(source_template);
    auto template_snapshot = ris::resource_snapshot(ris_res);
    bool any_with_compression = std::any_of(std::begin(user_resources.resources().resources),
        std::end(user_resources.resources().resources),
        [&compression](ris::resource const& res) {
        return compression.is_legal(res.compression);
    });

    ris::write_to_temp_first_then_move header([&ris_res, &template_snapshot, &user_resources,&lookup](std::ostream& s) {
        template_snapshot["namespace_name"] = user_resources.namespace_();
        template_snapshot["class_name"] = user_resources.class_();
        auto lazy = ris::get_context(template_snapshot);
        lazy
            .lazy("header", [&lazy, &ris_res](std::ostream& s) {
                ris::render(ris_res.Get("header"), lazy, s);
            })
            .lazy("header_declarations", [&ris_res,&user_resources,&lazy](std::ostream& s) {
                for (auto& resource : user_resources.resources().resources) {
                    lazy.lazy("resource_member_name", [&resource](std::ostream& s){
                        s << member_name(resource);
                    });
                    ris::render(ris_res.Get("header_single_declaration"), lazy, s);
                }
            })
            .lazy("header_resource_names", [&ris_res, &user_resources, &lazy](std::ostream& s) {
                for (auto& resource : user_resources.resources().resources) {
                    lazy.lazy("resource_name", [&resource](std::ostream& s){
                        s << resource.name;
                    });
                    ris::render(ris_res.Get("header_single_resource_name"), lazy, s);
                }
            })
        ;
        ris::render("{{header}}", lazy, s);
    }, user_resources.header());
    header.start();

    ris::write_to_temp_first_then_move source([&](std::ostream& s) {
        template_snapshot["namespace_name"] = user_resources.namespace_();
        template_snapshot["class_name"] = user_resources.class_();
        auto lazy = ris::get_context(template_snapshot);
        lazy
            .lazy("source", [&lazy, &ris_res](std::ostream& s) {
                ris::render(ris_res.Get("source"), lazy, s);
            })
            .lazy("optional_compression_header", [&](std::ostream& s) {
                if (any_with_compression)
                    s << "#include <bundle.hpp>\n";
            })
            .lazy("source_default_include", [&](std::ostream& s) {
                s << "#include \"" << boost::filesystem::path(user_resources.header()).filename().generic_string() << "\"";
            })
            .lazy("source_definitions", [&](std::ostream& s) {
                for (auto& resource : user_resources.resources().resources) {
                    lazy
                    .lazy("resource_member_name", [&](std::ostream& s){
                        s << member_name(resource);
                    })
                    .lazy("source_literal_bytes", [&](std::ostream& s){
                        static const unsigned MAX_IN_ONE_LINE = 100;
                        std::string data = ris::resource_loader(resource, user_resources.base_path()).get();

                        auto raw_size = data.size();

                        if (compression.is_legal(resource.compression)) {
                            data = compression.pack(resource.compression, data);
                            auto new_size = data.size();
                            std::cout << "[" << resource.compression << "] "
                                << resource.name << ": "
                                << new_size << "/" << raw_size
                                << " (" << ((double)new_size / raw_size*100.0) << "%)" << std::endl;
                        }

                        int count = 0;

                        for (char c : data) {
                            if (count > MAX_IN_ONE_LINE - 1) {
                                count = 0;
                            }

                            if (count == 0) {
                                s << "\n        ";
                            }

                            s << static_cast<short>(c) << ", ";

                            count++;
                        }
                    })
                    .lazy("source_return_literal", [&](std::ostream& s) {
                        if (compression.is_legal(resource.compression)) {
                            ris::render(ris_res.Get("source_return_compressed_literal"), lazy, s);
                        }
                        else {
                            ris::render(ris_res.Get("source_return_plain_literal"), lazy, s);
                        }
                    })
                    ;
                    ris::render(ris_res.Get("source_single_definition"), lazy, s);
                }
            })
            .lazy("source_getters", [&](std::ostream& s) {
                for (auto& resource : user_resources.resources().resources) {
                    lazy
                    .lazy("resource_name", [&resource](std::ostream& s){
                        s << resource.name;
                    })
                    .lazy("resource_member_name", [&](std::ostream& s){
                        s << member_name(resource);
                    })
                    ;
                    ris::render(ris_res.Get("source_single_getter"), lazy, s);
                }
            })
        ;
        ris::render("{{source}}", lazy, s);
    }, user_resources.source());
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
