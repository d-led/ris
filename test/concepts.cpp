#include <catch.hpp>

#include <string>

TEST_CASE("literals encoding strategy") {
 char const literal[] = { 0, 1, 2 };
 std::string s(literal,sizeof(literal)/sizeof(char));
 CHECK(s.size()==3);
}
