#pragma once

#include "types.h"
#include "mapped_memory.h"

namespace dmg {

class mmu final {
public:
    mmu();
    ~mmu() = default;

    mmu(const mmu&) = delete;
    mmu& operator=(const mmu&) = delete;

    mmu(mmu&&) = delete;
    mmu& operator=(mmu&) = delete;

    u8& operator[](u16);
private:
    mapped_memory m_memory;
};

}