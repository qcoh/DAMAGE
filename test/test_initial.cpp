#include "foo.h"

#include <catch2/catch_test_macros.hpp>


TEST_CASE("Sum of 1 and 2 is 3", "[foo]") {
	REQUIRE(sum(1, 2) == 3);
}
