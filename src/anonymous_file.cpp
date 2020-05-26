#include "anonymous_file.h"
#include "shared.h"

#include <system_error>

#include <sys/mman.h>
#include <unistd.h>

namespace dmg {

anonymous_file::anonymous_file(size_type size) {
    int fd = memfd_create("DAMAGE", 0);

    if (fd == -1) {
        throw std::system_error{errno, std::generic_category()};
    }

    if (ftruncate(fd, size) == -1) {
        close(fd);
        throw std::system_error{errno, std::generic_category()};
    }

    m_fd = fd;
}

anonymous_file::~anonymous_file() {
    if (m_fd >= 0) {
        close(m_fd);
    }
}

anonymous_file::operator int () const noexcept {
    return m_fd;
}

}