#include "mmu.h"

#include <signal.h>
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

mmu* mmu::s_unique_mmu = nullptr;

mmu::mmu() 
    : m_file{anonymous_file{MEMORY_SIZE}}
    , m_protected{m_file, MEMORY_SIZE}
    , m_unprotected{m_file, MEMORY_SIZE}
{
    // 0x0000 .. 0x3fff: ROM bank 0
    m_protected.map(ROM_BANK_0_OFFSET, ROM_BANK_0_LENGTH, PROT_READ);

    // 0x4000 .. 0x7fff: ROM bank 1 to ???
    m_protected.map(ROM_BANK_N_OFFSET, ROM_BANK_N_LENGTH, PROT_READ);

    // 0x8000 .. 0x9fff: VRAM
    m_protected.map(VRAM_OFFSET, VRAM_LENGTH, PROT_READ | PROT_WRITE);

    // 0xa000 .. 0xbfff: External RAM
    m_protected.map(EXTERNAL_RAM_OFFSET, EXTERNAL_RAM_LENGTH, PROT_READ | PROT_WRITE);

    // 0xc000 .. 0xcfff: WRAM bank 0
    m_protected.map(WRAM_BANK_0_OFFSET, WRAM_BANK_0_LENGTH, PROT_READ | PROT_WRITE);

    // 0xd000 .. 0xdfff: WRAM bank 1
    m_protected.map(WRAM_BANK_1_OFFSET, WRAM_BANK_1_LENGTH, PROT_READ | PROT_WRITE);

    // 0xe000 .. 0xefff: Lower part of echo (mirror 0xc000 .. 0xcfff)
    m_protected.mirror(LOWER_ECHO_OFFSET, WRAM_BANK_0_OFFSET, LOWER_ECHO_LENGTH, PROT_READ | PROT_WRITE);

    // 0xf000 .. 0xffff: Multiple uses: higher part of echo, object attribute memory, hardware registers, HRAM
    m_protected.map(MULTI_USE_OFFSET, MULTI_USE_LENGTH, 0);

    m_unprotected.protect(0, MEMORY_SIZE, PROT_READ | PROT_WRITE);

    if (s_unique_mmu == nullptr) {
        s_unique_mmu = this;

        struct sigaction sa { 0 };
        sa.sa_sigaction = sigsegv_handler;
        sigaction(SIGSEGV, &sa, nullptr);
    }
}

mmu::~mmu() {
    if (s_unique_mmu == this) {
        s_unique_mmu = nullptr;
    }
}

u8& mmu::operator[](u16 i) {
    return m_protected[i];
}

void mmu::sigsegv_handler(int sig, siginfo_t* info, void* ucontext) {
    void* address = info->si_addr;

    mcontext_t* mcontext = &reinterpret_cast<ucontext_t*>(ucontext)->uc_mcontext;

    // const bool is_read_fault = mcontext->gregs[REG_ERR];

    // DAMAGE jit convention
    //
    // All operations accessing the mmu must go through r10/r11,
    // where r10 always holds the address read from/written to and r11 is either the src or dst.
    //
    // Examples:
    // 
    // * Instead of emitting
    //
    //      mov [0x1000], al, emit
    //
    // emit
    //
    //      mov r10, 0x1000
    //      mov r11b, al
    //      mov BYTE [r10], r11b
    //
    // * Instead of emitting
    //
    //      mov bh, [0x1234]
    //
    // emit
    //
    //      mov r10, 0x1234
    //      mov r11b, BYTE [r10]
    //      mov bh, r11b ; this doesn't actually work. need to shift or swap... annoying
    //
    // Only BYTEs and WORDs can be read/written. This reduces the legal reads and writes to:
    //
    // Reads:
    //
    // * mov r11b, BYTE [r10]: 0x45 0x8a 0x1a
    // * mov r11w, WORD [r10]: 0x66 0x45 0x8b 0x1a
    //
    // Writes:
    //
    // * mov BYTE [r10], r11b: 0x45 0x88 0x1a
    // * mov WORD [r11], r11w: 0x66 0x45 0x89 0x1a

    const u8* rip = reinterpret_cast<u8*>(mcontext->gregs[REG_RIP]);

    if (rip[0] == 0x45 && rip[1] == 0x8a && rip[2] == 0x1a) {
        // mov r11b, BYTE [r10]
        mcontext->gregs[REG_R11] = 57;
        mcontext->gregs[REG_RIP] += 3;
    } else if (rip[0] == 0x66 && rip[1] == 0x45 && rip[2] == 0x8b && rip[3] == 0x1a) {
        // mov r11w, WORD [r10]
        mcontext->gregs[REG_R11] = 89;
        mcontext->gregs[REG_RIP] += 4;
    }
}

}