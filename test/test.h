#pragma once

// source: https://github.com/emil-e/rapidcheck/blob/master/extras/catch/include/rapidcheck/catch.h

#include <sstream>

#include <rapidcheck.h>
#include <catch2/catch_test_macros.hpp>

namespace rc {
	template <typename Testable>
	void prop(const std::string &description, Testable &&testable, bool verbose=false) {
		using namespace detail;
		SECTION(description) {
			const auto result = checkTestable(std::forward<Testable>(testable));
			if (result.template is<SuccessResult>()) {
				const auto success = result.template get<SuccessResult>();
				if (verbose || !success.distribution.empty()) {
					std::cout << "- " << description << std::endl;
					printResultMessage(result, std::cout);
					std::cout << std::endl;
				}
				SUCCEED();
			} else {
				std::ostringstream ss;
				printResultMessage(result, ss);
				INFO(ss.str() << "\n");
				FAIL();
			}
		}
	}
}

