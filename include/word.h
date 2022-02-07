#pragma once

#include "types.h"

// word takes two u8 references and presents itself like a u16.
struct word {
	word(u8& hi, u8& lo) : m_hi{hi}, m_lo{lo} {}

	operator u16 () const noexcept { return m_hi << 8 | m_lo; }
	word& operator=(u16 rhs) noexcept { m_hi = rhs >> 8; m_lo = rhs & 0xff; return *this; }

	u8& m_hi;
	u8& m_lo;
};
