#pragma once

#include "types.h"
#include "shared.h"
#include "anonymous_file.h"

namespace dmg {

class mapped_memory {
public:
    using size_type = decltype(sizeof(1));
    using offset_type = size_type;

    mapped_memory(shared<anonymous_file>, size_type);
    ~mapped_memory();
  
    void protect(offset_type, size_type, int);
    void map(offset_type, size_type, int);
    void mirror(offset_type, offset_type, size_type, int);

    inline u8& operator[](u16 addr) const noexcept { return m_memory[addr]; }

private:
    shared<anonymous_file> m_underlying_file;
    u8* m_memory;
    const size_type m_size;
};

}