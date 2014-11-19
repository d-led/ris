#include <catch.hpp>

#include <string>
#include <map>

TEST_CASE("literals encoding strategy") {
 char const literal[] = { 0, 1, 2 };
 std::string s(literal, sizeof(literal)/sizeof(char));
 CHECK(s.size()==3);
}

namespace {
	class Resource {
	public:
		static std::string Test();
	};

	std::string Resource::Test() {
		static char const literal[] = { 0, 1, 2, 0, 1 };
		return std::string(literal, sizeof(literal)/sizeof(char));
	}

}

TEST_CASE("api") {
	auto res=Resource::Test();
	char const literal[] = { 0, 1, 2, 0, 1 };
	std::string reference(literal, 5);
	CHECK( reference == res );
	std::string another(literal, 3);
	CHECK( another != res );
}
