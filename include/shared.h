#pragma once

#include <memory>

namespace dmg {

template <typename T>
class shared {
    // Shared pointer semantics for arbitrary types.

public:
    explicit shared(T&& t)
        : m_t{std::make_shared<T>(std::move(t))} 
    {
    }
    
    operator T () const noexcept {
        return *m_t;
    }
private:
    std::shared_ptr<T> m_t;
};

}