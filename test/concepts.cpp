#include <catch.hpp>

#include <string>
#include <unordered_map>

TEST_CASE("literals encoding strategy") {
 char const literal[] = { 0, 1, 2 };
 std::string s(literal, sizeof(literal)/sizeof(char));
 CHECK(s.size()==3);
}

namespace {

    class Resource /*final*/ {
    public:
        typedef std::string(*ResourceGetter)();
    public:
        static std::string Test();
        static std::string PlainText();
    public: // key/value api
        template <typename TInserter>
        static void GetKeys(TInserter inserter) {
            static const char* keys[] = {
                "Test",
                "PlainText"
            };
            for (auto key : keys) {
                inserter(key);
            }
        }

        static std::string Get(std::string const& key);
    public:
        static std::string OnNoKey() {
            // can be throwing or not
            return "";
        }
    };

    std::string Resource::Test() {
        static char const literal[] = { 0, 1, 2, 0, 1 };
        return std::string(literal, sizeof(literal)/sizeof(char));
    }

    std::string Resource::PlainText() {
        static char const literal[] = "some plain text"; // not in scope at the moment
        return std::string(literal);
    }

    std::string Resource::Get(std::string const& key) {
        static std::unordered_map<std::string,ResourceGetter> getters = {
            { "Test", Resource::Test },
            { "PlainText", Resource::PlainText },
        };

        auto getter = getters.find(key);
        if (getter == getters.end())
            return OnNoKey();

        return getter->second();
    }
}

TEST_CASE("api") {
    auto res=Resource::Test();
    char const literal[] = { 0, 1, 2, 0, 1 };
    std::string reference(literal, 5);
    CHECK( reference == res );
    std::string another(literal, 3);
    CHECK( another != res );

    CHECK( Resource::PlainText() == "some plain text" );

    SECTION("key/value api") {
        CHECK( Resource::Get("PlainText") == "some plain text" );
        CHECK( Resource::Get("Whatever") == "" );
    }

    SECTION("getting all keys") {
        std::vector<std::string> keys;
        Resource::GetKeys([&keys](char const* key){
            keys.emplace_back(key);
        });
        CHECK(keys.size() == 2);
        CHECK(keys[0] == "Test");
        CHECK(keys[1] == "PlainText");
    }
}
