#include "mmu.h"

#include <system_error>

#include <sys/mman.h>

namespace {

constexpr size_t MEMORY_SIZE = 0x10000U;

}

namespace dmg {

mmu::mmu() {
    void* memory = mmap(
        nullptr,
        MEMORY_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    if (memory == MAP_FAILED) {
        throw std::system_error(errno, std::generic_category());
    }

    m_memory = static_cast<u8*>(memory);
}

mmu::~mmu() {
    if (m_memory) {
        munmap(m_memory, MEMORY_SIZE);
        m_memory = nullptr;
    }
}

u8& mmu::operator[](u16 i) {
    return m_memory[i];
}

}