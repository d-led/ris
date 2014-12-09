#include <catch.hpp>
#include "../ris_lib/ris_late.h"
#include "../ris_lib/ris_late_context.h"

#include <unordered_map>
#include <sstream>

typedef std::unordered_map<std::string, std::string> default_context_t;

TEST_CASE("splitting along simple mustache tags and skipping others") {
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

    default_context_t context {
        { "name", "John" },
        { "taxed_value", "42" },
        { "value", "33" }
    };

    std::stringstream output;
    ris::render(temp, ris::get_context(context), output);

    std::string output_str(output.str());
    CHECK(output_str == expected);
}

TEST_CASE("newlines are preserved and non-variables are ignored") {
    std::stringstream output;
    default_context_t context;
    ris::render("\n{{#a}}\n", ris::get_context(context), output);

    CHECK(output.str() == "\n\n");
}

TEST_CASE("spaces in tags are allowed") {
    std::stringstream output;
    default_context_t context{ 
        { "a", "42" }
    };
    ris::render("{{a}}{{  a   }}", ris::get_context(context), output);

    CHECK(output.str() == "4242");
}

TEST_CASE("empty templates are ok") {
    std::stringstream output;
    default_context_t context;
    REQUIRE_NOTHROW(ris::render("", ris::get_context(context), output));

    CHECK(output.str() == "");
}

TEST_CASE("non-word characters in tags") {
    std::stringstream output;
    default_context_t context{
        { "a_", "42" },
        { "a.b", "33" } // . or - not allowed 
    };
    ris::render("{{a_}}{{a.b}}", ris::get_context(context), output);

    CHECK(output.str() == "42");
}

TEST_CASE("confusion avoidance") {
    std::stringstream output;
    default_context_t context;
    ris::render("{{{a}}", ris::get_context(context), output);

    CHECK(output.str() == "{");
    
    output.str("");
    ris::render("{{{a }}}", ris::get_context(context), output);
    CHECK(output.str() == "{}");
}

TEST_CASE("late replacements have preference") {
    std::stringstream output;
    default_context_t context{
        { "a", "33" }
    };

    auto context_late = ris::get_context(context);
    context_late
        .lazy("a", [](std::ostream& s) { s << 42; });
    ris::render("{{a}}", context_late, output);

    CHECK(output.str() == "42");
}

TEST_CASE("recursive lazy replacement") {
    std::stringstream output;
    default_context_t context{};

    auto context_late = ris::get_context(context);
    context_late
       .lazy("a", [&context_late](std::ostream& s) {
            ris::render("{{b}}=42", context_late, s);
        })
       .lazy("b", [](std::ostream& s) {
            s << "answer";
        });
    ris::render("{{a}}", context_late, output);

    CHECK(output.str() == "answer=42");
}