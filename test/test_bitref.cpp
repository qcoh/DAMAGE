#include "test.h"

#include "bitref.h"

SCENARIO("reading from and writing to bitref") {
  GIVEN("bitref") {
    u8 v = 0xff;
    bitref<5> b{v};

    WHEN("setting bitref to false") {
      b = false;

      THEN("the corresponding bit is set to zero") {
        REQUIRE((v & 0b00100000) == 0);
      }
      AND_THEN("the other bits are still set") {
        REQUIRE(v == static_cast<u8>(~(1 << 5)));
      }
    }
  }
}
