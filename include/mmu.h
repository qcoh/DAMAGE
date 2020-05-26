#pragma once

#include <signal.h>

#include "types.h"
#include "mapped_memory.h"

namespace dmg {

class mmu final {
public:
    mmu();
    ~mmu();

    mmu(const mmu&) = delete;
    mmu& operator=(const mmu&) = delete;

    mmu(mmu&&) = delete;
    mmu& operator=(mmu&) = delete;

    u8& operator[](u16);
private:
    shared<anonymous_file> m_file;
    mapped_memory m_protected;
    mapped_memory m_unprotected;

    static mmu* s_unique_mmu;
    static void sigsegv_handler(int, siginfo_t*, void*);
};

}