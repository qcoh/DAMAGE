#pragma once

#include <memory>

namespace dmg::detail {

struct file_descriptor_implementation;

}

namespace dmg {

class shared_file_descriptor final {
public:
    explicit shared_file_descriptor(int);
    ~shared_file_descriptor();

    operator int () const noexcept; 
private:
    std::shared_ptr<dmg::detail::file_descriptor_implementation> m_ptr;
};

}