#pragma once

#include "types.h"

namespace dmg {

class mapped_memory {
public:
    using size_type = decltype(sizeof(1));
    using offset_type = size_type;

    mapped_memory(size_type);
    ~mapped_memory();

    mapped_memory(const mapped_memory&) = delete;
    mapped_memory& operator=(const mapped_memory&) = delete;

    mapped_memory(mapped_memory&&);
    mapped_memory& operator=(mapped_memory&&);

    void protect(offset_type, size_type, int);

    inline u8& operator[](offset_type offset) {
        return m_memory[offset];
    }
private:
    u8* m_memory = nullptr;
    int m_fd = 0;
    const size_type m_size;

};

}