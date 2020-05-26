#pragma once

#include "types.h"

namespace dmg {

class anonymous_file {
public:
    explicit anonymous_file(size_type);
    ~anonymous_file();

    operator int () const noexcept;

private:
    int m_fd = -1;
};

}