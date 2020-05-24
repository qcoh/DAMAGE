#include "mmu.h"

#include <iostream>
#include <assert.h>

int main() {
    // GIVEN: "A MMU instance, an address between 0xf000 and 0xffff"
    dmg::mmu mmu{};
    u8* address = &mmu[0xf567];

    // WHEN: Reading from the address
    u8 value = 0;

    asm volatile(
        "movq %[address], %%r10\n"
        "movb (%%r10), %%r11b\n"
        "movb %%r11b, %[value]\n"
    : [value] "=r" (value)  // output
    : [address] "r" (address) // input
    : "r10", "r11" // clobbered registers 
    );

    // THEN: The value is the magic value 57
    std::cout << "Value = " << (int)value << '\n';
    assert(value == 57);
}