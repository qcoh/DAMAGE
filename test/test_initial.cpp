#include "foo.h"

#include <catch2/catch_test_macros.hpp>
#include "rapidcheck.h"
#include "prop.h"


TEST_CASE("foo") {
	rc::prop("The sum of identical numbers is even",
		[](int a) {
			RC_ASSERT(sum(a, a) % 2 == 0);
		});
}
