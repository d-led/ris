#include "../ris_lib/ris_writing_files.h"

#include <catch.hpp>

#include <boost/filesystem.hpp>

TEST_CASE("successful write") {
    boost::filesystem::path p("test.test");
    {
        ris::write_to_temp_first_then_move f([](std::ostream& s) {
            s << "test";
        }, p.generic_string());
        f.start();
    }
    REQUIRE(exists(p));
    std::ifstream is(p.generic_string());
    std::string line;
    std::getline(is, line);
    CHECK(line == "test");
    is.close();
    remove(p);
}

TEST_CASE("aborted write") {
    boost::filesystem::path p("test2.test");
    try { remove(p); }
    catch (...) {}

    {
        ris::write_to_temp_first_then_move f([](std::ostream& s) {
            s << "test";
            throw std::runtime_error("test");
        }, p.generic_string());

        try {
            CHECK_THROWS(f.start());
        }
        catch (...) {}
    }

    REQUIRE(!exists(p));
}
