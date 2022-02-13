#include "word.h"

#include "test.h"

SCENARIO("High and low bytes of a word") {
  GIVEN("high and low bytes and a word comprising the two") {
    u8 hi = 0;
    u8 lo = 0;
    word w{hi, lo};

    rc::prop("modifying word changes hi and lo bytes",
             [&w, &hi, &lo](u16 new_value) {
               w = new_value;

               RC_ASSERT(hi == (new_value >> 8));
               RC_ASSERT(lo == (new_value & 0xff));
             });

    rc::prop("modifying hi and lobytes changes word",
             [&w, &hi, &lo](u8 rand_hi, u8 rand_lo) {
               hi = rand_hi;
               lo = rand_lo;

               const u16 rand_w = rand_hi << 8 | rand_lo;

               RC_ASSERT(w == rand_w);
             });
  }
}
