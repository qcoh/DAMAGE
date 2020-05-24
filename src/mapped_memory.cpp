#include "mapped_memory.h"

#include <system_error>

#include <sys/mman.h>
#include <unistd.h>

namespace dmg {

mapped_memory::mapped_memory(mapped_memory::size_type size) 
    : m_protected{nullptr}
    , m_unprotected{nullptr}
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

    void* protected_ = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        fd,
        0
    );

    if (protected_ == MAP_FAILED) {
        const int errno_ = errno;
        close(fd);
        throw std::system_error{errno_, std::generic_category()};  
    }

    void* unprotected = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        fd,
        0
    );

    if (unprotected == MAP_FAILED) {
        munmap(protected_, size);
        const int errno_ = errno;
        close(fd);
        throw std::system_error{errno_, std::generic_category()};  
    }

    m_fd = fd;
    m_protected = static_cast<u8*>(protected_);
    m_unprotected = static_cast<u8*>(unprotected);
}

mapped_memory::~mapped_memory() {
    if (m_protected) {
        munmap(m_protected, m_size);
    }
    if (m_unprotected) {
        munmap(m_unprotected, m_size);
    }
    if (m_protected || m_unprotected) {
        close(m_fd);
        m_protected = nullptr;
        m_unprotected = nullptr;
    }
}

void mapped_memory::protect(mapped_memory::size_type offset, mapped_memory::size_type length, int prot) {
    if (mprotect(m_protected + offset, length, prot) == -1) {
        throw std::system_error{errno, std::generic_category()};
    }
}

void mapped_memory::map(mapped_memory::offset_type offset, mapped_memory::size_type length, int prot) {
    void* address = mmap(
        m_protected + offset,
        length,
        prot,
        MAP_FIXED | MAP_SHARED, // MAP_FIXED: require mapping at this exact location, MAP_SHARED: use something other than -1 for fd (I think)
        m_fd,
        offset
    );

    if (address != (m_protected + offset)) {
        throw std::system_error{errno, std::generic_category()};
    }
}

void mapped_memory::mirror(mapped_memory::offset_type destination, mapped_memory::offset_type source, mapped_memory::size_type length, int prot) {
    void* address = mmap(
        m_protected + destination,
        length,
        prot,
        MAP_FIXED | MAP_SHARED, // MAP_FIXED: require mapping at this exact location, MAP_SHARED: use something other than -1 for fd (I think)
        m_fd,
        source
    );

    if (address != (m_protected + destination)) {
        throw std::system_error{errno, std::generic_category()};
    }
}


}