#include "mapped_memory.h"

#include <system_error>

#include <sys/mman.h>

namespace dmg {

mapped_memory::mapped_memory(mapped_memory::size_type size) 
    : m_memory{nullptr}
    , m_size{size} 
{
    void* memory = mmap(
        nullptr,
        size,
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

mapped_memory::~mapped_memory() {
    if (m_memory) {
        munmap(m_memory, m_size);
        m_memory = nullptr;
    }
}

void mapped_memory::protect(mapped_memory::size_type offset, mapped_memory::size_type length, int flags) {
    if (mprotect(m_memory + offset, length, flags) == -1) {
        throw std::system_error{errno, std::generic_category()};
    }
}


}