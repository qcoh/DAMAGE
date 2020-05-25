#include "shared_file_descriptor.h"

#include <system_error>

#include <fcntl.h>
#include <unistd.h>

namespace dmg::detail {

struct file_descriptor_implementation {
    int m_fd{-1};

    explicit file_descriptor_implementation(int fd) {
        // https://stackoverflow.com/a/12340730
        if (fcntl(fd, F_GETFD) == -1) {
            throw std::system_error{errno, std::generic_category()};
        }
        m_fd = fd;
    }

    ~file_descriptor_implementation() {
        if (m_fd != -1) {
            close(m_fd);
        }
    }
};

}

namespace dmg {

shared_file_descriptor::shared_file_descriptor(int fd)
    : m_ptr{std::make_shared<detail::file_descriptor_implementation>(fd)}
{
}

shared_file_descriptor::~shared_file_descriptor() = default;

shared_file_descriptor::operator int () const noexcept {
    return m_ptr->m_fd;
}

}