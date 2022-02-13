#include "romonly.h"

u8 romonly::read_u8(u16 address) { return data[address]; }
void romonly::write_u8(u16, u8) {
  // romonly is read-only. If it is being written to, it is either
  // an error in my implementation or in the game. In case it's the
  // latter, the best thing to do is to ignore the error, I think.
}