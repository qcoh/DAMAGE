#include "mapped_memory.h"

#include <system_error>

#include <sys/mman.h>
#include <unistd.h>

namespace dmg {

mapped_memory::mapped_memory(shared<anonymous_file> underlying_file, mapped_memory::size_type size) 
    : m_underlying_file{underlying_file}
    , m_memory{nullptr}
    , m_size{size} 
{
    void* memory = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        static_cast<anonymous_file>(m_underlying_file),
        0
    );

    if (memory == MAP_FAILED) {
        throw std::system_error{errno, std::generic_category()};  
    }

    m_memory = static_cast<u8*>(memory);
}

mapped_memory::~mapped_memory() {
    if (m_memory) {
        munmap(m_memory, m_size);
        m_memory = nullptr;
    }
}

void mapped_memory::protect(mapped_memory::size_type offset, mapped_memory::size_type length, int prot) {
    if (mprotect(m_memory + offset, length, prot) == -1) {
        throw std::system_error{errno, std::generic_category()};
    }
}

void mapped_memory::map(mapped_memory::offset_type offset, mapped_memory::size_type length, int prot) {
    void* address = mmap(
        m_memory + offset,
        length,
        prot,
        MAP_FIXED | MAP_SHARED, // MAP_FIXED: require mapping at this exact location, MAP_SHARED: use something other than -1 for fd (I think)
        static_cast<anonymous_file>(m_underlying_file),
        offset
    );

    if (address != (m_memory + offset)) {
        throw std::system_error{errno, std::generic_category()};
    }
}

void mapped_memory::mirror(mapped_memory::offset_type destination, mapped_memory::offset_type source, mapped_memory::size_type length, int prot) {
    void* address = mmap(
        m_memory + destination,
        length,
        prot,
        MAP_FIXED | MAP_SHARED, // MAP_FIXED: require mapping at this exact location, MAP_SHARED: use something other than -1 for fd (I think)
        static_cast<anonymous_file>(m_underlying_file),
        source
    );

    if (address != (m_memory + destination)) {
        throw std::system_error{errno, std::generic_category()};
    }
}


}