#include "mapped_memory.h"

#include <system_error>

#include <sys/mman.h>
#include <unistd.h>

namespace dmg {

mapped_memory::mapped_memory(mapped_memory::size_type size) 
    : m_memory{nullptr}
    , m_fd{0}
    , m_size{size} 
{
    int fd = memfd_create("DAMAGE mmu", 0);

    if (fd == -1) {
        throw std::system_error{errno, std::generic_category()};
    }

    if (ftruncate(fd, m_size) == -1) {
        const int errno_ = errno;
        close(fd);
        throw std::system_error{errno_, std::generic_category()};        
    }

    void* memory = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        fd,
        0
    );

    if (memory == MAP_FAILED) {
        const int errno_ = errno;
        close(fd);
        throw std::system_error{errno_, std::generic_category()};  
    }

    m_fd = fd;
    m_memory = static_cast<u8*>(memory);
}

mapped_memory::~mapped_memory() {
    if (m_memory) {
        close(m_fd);
        munmap(m_memory, m_size);
        m_memory = nullptr;
        close(m_fd);
    }
}

void mapped_memory::protect(mapped_memory::size_type offset, mapped_memory::size_type length, int flags) {
    if (mprotect(m_memory + offset, length, flags) == -1) {
        throw std::system_error{errno, std::generic_category()};
    }
}


}