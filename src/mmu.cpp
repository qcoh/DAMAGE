#include "mmu.h"

#include <system_error>

#include <sys/mman.h>

namespace {

constexpr size_t MEMORY_SIZE = 0x10000U;

constexpr size_t ROM_BANK_0_OFFSET = 0x0000U;
constexpr size_t ROM_BANK_0_LENGTH = 0x4000U;

constexpr size_t ROM_BANK_N_OFFSET = 0x4000U;
constexpr size_t ROM_BANK_N_LENGTH = 0x4000U;

constexpr size_t VRAM_OFFSET = 0x8000U;
constexpr size_t VRAM_LENGTH = 0x2000U;

constexpr size_t EXTERNAL_RAM_OFFSET = 0xA000U;
constexpr size_t EXTERNAL_RAM_LENGTH = 0x2000U;

constexpr size_t WRAM_BANK_0_OFFSET = 0xC000U;
constexpr size_t WRAM_BANK_0_LENGTH = 0x1000U;

constexpr size_t WRAM_BANK_1_OFFSET = 0xD000U;
constexpr size_t WRAM_BANK_1_LENGTH = 0x1000U;

constexpr size_t LOWER_ECHO_OFFSET = 0xE000U;
constexpr size_t LOWER_ECHO_LENGTH = 0x1000U;

constexpr size_t MULTI_USE_OFFSET = 0xF000U;
constexpr size_t MULTI_USE_LENGTH = 0x1000U;

}

namespace dmg {

mmu::mmu() 
    : m_memory{MEMORY_SIZE} {
    
    // 0x0000 .. 0x3fff: ROM bank 0
    m_memory.map(ROM_BANK_0_OFFSET, ROM_BANK_0_LENGTH, PROT_READ);

    // 0x4000 .. 0x7fff: ROM bank 1 to ???
    m_memory.map(ROM_BANK_N_OFFSET, ROM_BANK_N_LENGTH, PROT_READ);

    // 0x8000 .. 0x9fff: VRAM
    m_memory.map(VRAM_OFFSET, VRAM_LENGTH, PROT_READ | PROT_WRITE);

    // 0xa000 .. 0xbfff: External RAM
    m_memory.map(EXTERNAL_RAM_OFFSET, EXTERNAL_RAM_LENGTH, PROT_READ | PROT_WRITE);

    // 0xc000 .. 0xcfff: WRAM bank 0
    m_memory.map(WRAM_BANK_0_OFFSET, WRAM_BANK_0_LENGTH, PROT_READ | PROT_WRITE);

    // 0xd000 .. 0xdfff: WRAM bank 1
    m_memory.map(WRAM_BANK_1_OFFSET, WRAM_BANK_1_LENGTH, PROT_READ | PROT_WRITE);

    // 0xe000 .. 0xefff: Lower part of echo (mirror 0xc000 .. 0xcfff)
    m_memory.mirror(LOWER_ECHO_OFFSET, WRAM_BANK_0_OFFSET, LOWER_ECHO_LENGTH, PROT_READ | PROT_WRITE);

    // 0xf000 .. 0xffff: Multiple uses: higher part of echo, object attribute memory, hardware registers, HRAM
    m_memory.map(MULTI_USE_OFFSET, MULTI_USE_LENGTH, PROT_READ);
}

u8& mmu::operator[](u16 i) {
    return m_memory[i];
}

}