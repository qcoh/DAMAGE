#pragma once

#include "types.h"

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
    u8* m_memory = nullptr;
};

}