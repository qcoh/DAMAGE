#include "file.h"
#include "shared_file_descriptor.h"

#include <system_error>

#include <sys/mman.h>
#include <unistd.h>

namespace dmg {

shared_file_descriptor open_anonymous_file(size_type size, int prot) {
    int fd = memfd_create("DAMAGE", 0);

    if (fd == -1) {
        throw std::system_error{errno, std::generic_category()};
    }

    if (ftruncate(fd, size) == -1) {
        const int errno_ = errno;
        close(fd);
        throw std::system_error{errno_, std::generic_category()};        
    }

    return shared_file_descriptor(fd);
}


}