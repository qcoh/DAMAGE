#pragma once

#include "types.h"

template <int I>
struct bitref {
	static_assert(4 <= I && I < 8, "The GameBoy has flags only for bits 4 to 7");
	static constexpr u8 Mask = static_cast<u8>(1 << I);
	static constexpr u8 InverseMask = static_cast<u8>(~Mask);

	explicit bitref(u8& ref) noexcept : m_ref{ref} {}
	~bitref() = default;

	bitref(const bitref&) = delete;
	bitref& operator=(const bitref&) = delete;
	bitref(bitref&&) = delete;
	bitref& operator=(bitref&&) = delete;

	operator bool() const noexcept { return m_ref & Mask; }

	bitref& operator=(bool rhs) noexcept { m_ref = (m_ref & InverseMask) | (rhs << I); return *this; }

	u8& m_ref;
};
