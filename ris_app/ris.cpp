#include "../ris_lib/ris_generator.h"
#include "../ris_lib/ris_json_resources.h"
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

#include <boost/filesystem.hpp>

void print_usage() {
    std::cout
        << "---      ris v0.0.1            ---" << std::endl
        << "a simple resource compiler for c++" << std::endl
        << "https://github.com/d-led/ris" << std::endl
        << "USAGE:" << std::endl
        << "       ris <path_to>/<resources>.json [<template_overrides>.json]" << std::endl
        ;
}

void process(std::string const& path, std::string const& source_template) {
    auto full_path = absolute(boost::filesystem::path(path));
    full_path.make_preferred();
    std::cout << "reading " << full_path.generic_string() << std::endl;

    auto user_resources = ris::json_resources(path);
    auto lookup = user_resources.to_lookup();
    std::cout << "read " << user_resources.resources().resources.size() << " resources" << std::endl;

    auto c = ris::bundle_compression();
    auto ris_res = ris::default_or_from_file<ris::Resource>(source_template);
    auto template_snapshot = ris::resource_snapshot(ris_res);

    ris::write_to_temp_first_then_move header([&ris_res, &template_snapshot, &user_resources,&lookup](std::ostream& s) {
        template_snapshot["namespace_name"] = user_resources.namespace_();
        template_snapshot["class_name"] = user_resources.class_();
        auto lazy = ris::get_context(template_snapshot);
        lazy
            .lazy("header", [&lazy, &ris_res](std::ostream& s) {
                ris::render(ris_res.Get("header"), lazy, s);
            })
        ;
        ris::render("{{header}}", lazy, s);
    }, user_resources.header());
    header.start();

    //ris::write_to_temp_first_then_move source([&g](std::ostream& s) {
    //    g.generate_source(s);
    //}, user_resources.source());
    //source.start();
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
