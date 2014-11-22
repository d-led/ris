#include <catch.hpp>

#include <boost/filesystem.hpp>

#include "../ris_lib/ris_json_resources.h"
#include "../ris_lib/ris_resource_loader.h"
#include "../ris_lib/ris_resources.h"

class fixture {
protected:
    boost::filesystem::path test_data;
public:
    fixture() {
        static const char* candiadates[] = {
            ".",
            "./acceptance_test",
            "../acceptance_test",
        };
        for (auto p : candiadates) {
            if (exists(boost::filesystem::path(p) / "test.bin")) {
                test_data = p;
                break;
            }
        }
        REQUIRE(exists(test_data / "test.bin"));
        REQUIRE(exists(test_data / "test.json"));
    }
};

TEST_CASE_METHOD(fixture,"loading the resource") {
    auto r = ris::json_resources((test_data / "test.json").generic_string());
    CHECK(r.resources().resources.size() > 0);
}