#include <catch.hpp>
#include "../ris_lib/ris_late.h"

#include <unordered_map>
#include <sstream>

TEST_CASE("splitting along simple mustache tags") {
    const char* temp = R"(Hello {{name}}
You have just won {{value }} dollars!
{{#in_ca}}
    Well, {{ taxed_value }} dollars, after taxes.
{{/in_ca}}
)";

    const char* expected = R"(Hello John
You have just won 33 dollars!

    Well, 42 dollars, after taxes.

)";

    std::unordered_map<std::string, std::string> context {
        { "name", "John" },
        { "taxed_value", "42" },
        { "value", "33" }
    };


    std::stringstream output;
    ris::render(temp, context, output);

    WARN(output.str().empty());
}
