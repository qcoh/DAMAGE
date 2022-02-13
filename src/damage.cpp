#include "bios.h"
#include "cpu.h"
#include "gameboy.h"
#include "mmu.h"
#include "romonly.h"

#include <algorithm>
#include <fstream>

int main(int argc, char *argv[]) {
  std::ifstream bios_stream{argv[1], std::ios::binary};
  bios bios_{std::istreambuf_iterator<char>{bios_stream}};

  std::ifstream rom_stream{argv[2], std::ios::binary};
  romonly rom_{std::istreambuf_iterator<char>{rom_stream}};

  mmu mmu_{bios_, rom_};
  cpu cpu_;

  gameboy gameboy_{cpu_, mmu_};
}