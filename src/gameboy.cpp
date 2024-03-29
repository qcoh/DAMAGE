#include "gameboy.h"

#include "cpu.h"
#include "lr35902.h"
#include "mmu.h"
#include "registers.h"

#include <cstdio>
#include <cstdlib>

gameboy::gameboy(cpu &cpu_, mmu &mmu_) : m_cpu{cpu_}, m_mmu{mmu_} {}

void gameboy::step() {
  const u8 opcode = m_mmu.read_u8(m_cpu.pc);

  // TODO: this might cause problems with toggling the mmu from bios to
  // cartridge mode!
  m_cpu.im = m_mmu.read_u8(m_cpu.pc + 1);
  m_cpu.imm = m_mmu.read_u8(m_cpu.pc + 1);

  if (opcode == 0xcb) {
    extended_step(m_cpu.im);
  } else {
    regular_step(opcode);
  }
}

void gameboy::regular_step(u8 opcode) {
  switch (opcode) {
  case 0x00:
    goto not_implemented;
  case 0x01:
    ld_imm<bc>(m_cpu, m_mmu);
    break;
  case 0x02:
    ld_at_16<at_bc>(m_cpu, m_mmu);
    break;
  case 0x03:
    inc_16<bc>(m_cpu, m_mmu);
    break;
  case 0x04:
    goto not_implemented;
  case 0x05:
    goto not_implemented;
  case 0x06:
    ld_im<b>(m_cpu, m_mmu);
    break;
  case 0x07:
    goto not_implemented;
  case 0x08:
    goto not_implemented;
  case 0x09:
    goto not_implemented;
  case 0x0a:
    goto not_implemented;
  case 0x0b:
    goto not_implemented;
  case 0x0c:
    goto not_implemented;
  case 0x0d:
    goto not_implemented;
  case 0x0e:
    ld_im<c>(m_cpu, m_mmu);
    break;
  case 0x0f:
    goto not_implemented;
  case 0x10:
    jr_n<zf>(m_cpu, m_mmu);
    break;
  case 0x11:
    ld_imm<de>(m_cpu, m_mmu);
    break;
  case 0x12:
    ld_at_16<at_de>(m_cpu, m_mmu);
    break;
  case 0x13:
    inc_16<de>(m_cpu, m_mmu);
    break;
  case 0x14:
    goto not_implemented;
  case 0x15:
    goto not_implemented;
  case 0x16:
    ld_im<d>(m_cpu, m_mmu);
    break;
  case 0x17:
    goto not_implemented;
  case 0x18:
    goto not_implemented;
  case 0x19:
    goto not_implemented;
  case 0x1a:
    goto not_implemented;
  case 0x1b:
    goto not_implemented;
  case 0x1c:
    goto not_implemented;
  case 0x1d:
    goto not_implemented;
  case 0x1e:
    ld_im<e>(m_cpu, m_mmu);
    break;
  case 0x1f:
    goto not_implemented;
  case 0x20:
    jr_n<cf>(m_cpu, m_mmu);
    break;
  case 0x21:
    ld_imm<hl>(m_cpu, m_mmu);
    break;
  case 0x22:
    ldi_at_hl(m_cpu, m_mmu);
    break;
  case 0x23:
    inc_16<hl>(m_cpu, m_mmu);
    break;
  case 0x24:
    goto not_implemented;
  case 0x25:
    goto not_implemented;
  case 0x26:
    ld_im<h>(m_cpu, m_mmu);
    break;
  case 0x27:
    goto not_implemented;
  case 0x28:
    goto not_implemented;
  case 0x29:
    goto not_implemented;
  case 0x2a:
    goto not_implemented;
  case 0x2b:
    goto not_implemented;
  case 0x2c:
    goto not_implemented;
  case 0x2d:
    goto not_implemented;
  case 0x2e:
    ld_im<l>(m_cpu, m_mmu);
    break;
  case 0x2f:
    goto not_implemented;
  case 0x30:
    goto not_implemented;
  case 0x31:
    ld_imm<sp>(m_cpu, m_mmu);
    break;
  case 0x32:
    ldd_at_hl(m_cpu, m_mmu);
    break;
  case 0x33:
    inc_16<sp>(m_cpu, m_mmu);
    break;
  case 0x34:
    goto not_implemented;
  case 0x35:
    goto not_implemented;
  case 0x36:
    ld_im<at_hl>(m_cpu, m_mmu);
    break;
  case 0x37:
    goto not_implemented;
  case 0x38:
    goto not_implemented;
  case 0x39:
    goto not_implemented;
  case 0x3a:
    goto not_implemented;
  case 0x3b:
    goto not_implemented;
  case 0x3c:
    goto not_implemented;
  case 0x3d:
    goto not_implemented;
  case 0x3e:
    ld_im<a>(m_cpu, m_mmu);
    break;
  case 0x3f:
    goto not_implemented;
  case 0x40:
    ld<b, b>(m_cpu, m_mmu);
    break;
  case 0x41:
    ld<b, c>(m_cpu, m_mmu);
    break;
  case 0x42:
    ld<b, d>(m_cpu, m_mmu);
    break;
  case 0x43:
    ld<b, e>(m_cpu, m_mmu);
    break;
  case 0x44:
    ld<b, h>(m_cpu, m_mmu);
    break;
  case 0x45:
    ld<b, l>(m_cpu, m_mmu);
    break;
  case 0x46:
    ld<b, at_hl>(m_cpu, m_mmu);
    break;
  case 0x47:
    ld<b, a>(m_cpu, m_mmu);
    break;
  case 0x48:
    ld<c, b>(m_cpu, m_mmu);
    break;
  case 0x49:
    ld<c, c>(m_cpu, m_mmu);
    break;
  case 0x4a:
    ld<c, d>(m_cpu, m_mmu);
    break;
  case 0x4b:
    ld<c, e>(m_cpu, m_mmu);
    break;
  case 0x4c:
    ld<c, h>(m_cpu, m_mmu);
    break;
  case 0x4d:
    ld<c, l>(m_cpu, m_mmu);
    break;
  case 0x4e:
    ld<c, at_hl>(m_cpu, m_mmu);
    break;
  case 0x4f:
    ld<c, a>(m_cpu, m_mmu);
    break;
  case 0x50:
    ld<d, b>(m_cpu, m_mmu);
    break;
  case 0x51:
    ld<d, c>(m_cpu, m_mmu);
    break;
  case 0x52:
    ld<d, d>(m_cpu, m_mmu);
    break;
  case 0x53:
    ld<d, e>(m_cpu, m_mmu);
    break;
  case 0x54:
    ld<d, h>(m_cpu, m_mmu);
    break;
  case 0x55:
    ld<d, l>(m_cpu, m_mmu);
    break;
  case 0x56:
    ld<d, at_hl>(m_cpu, m_mmu);
    break;
  case 0x57:
    ld<d, a>(m_cpu, m_mmu);
    break;
  case 0x58:
    ld<e, b>(m_cpu, m_mmu);
    break;
  case 0x59:
    ld<e, c>(m_cpu, m_mmu);
    break;
  case 0x5a:
    ld<e, d>(m_cpu, m_mmu);
    break;
  case 0x5b:
    ld<e, e>(m_cpu, m_mmu);
    break;
  case 0x5c:
    ld<e, h>(m_cpu, m_mmu);
    break;
  case 0x5d:
    ld<e, l>(m_cpu, m_mmu);
    break;
  case 0x5e:
    ld<e, at_hl>(m_cpu, m_mmu);
    break;
  case 0x5f:
    ld<e, a>(m_cpu, m_mmu);
    break;
  case 0x60:
    ld<h, b>(m_cpu, m_mmu);
    break;
  case 0x61:
    ld<h, c>(m_cpu, m_mmu);
    break;
  case 0x62:
    ld<h, d>(m_cpu, m_mmu);
    break;
  case 0x63:
    ld<h, e>(m_cpu, m_mmu);
    break;
  case 0x64:
    ld<h, h>(m_cpu, m_mmu);
    break;
  case 0x65:
    ld<h, l>(m_cpu, m_mmu);
    break;
  case 0x66:
    ld<h, at_hl>(m_cpu, m_mmu);
    break;
  case 0x67:
    ld<h, a>(m_cpu, m_mmu);
    break;
  case 0x68:
    ld<l, b>(m_cpu, m_mmu);
    break;
  case 0x69:
    ld<l, c>(m_cpu, m_mmu);
    break;
  case 0x6a:
    ld<l, d>(m_cpu, m_mmu);
    break;
  case 0x6b:
    ld<l, e>(m_cpu, m_mmu);
    break;
  case 0x6c:
    ld<l, h>(m_cpu, m_mmu);
    break;
  case 0x6d:
    ld<l, l>(m_cpu, m_mmu);
    break;
  case 0x6e:
    ld<l, at_hl>(m_cpu, m_mmu);
    break;
  case 0x6f:
    ld<l, a>(m_cpu, m_mmu);
    break;
  case 0x70:
    ld<at_hl, b>(m_cpu, m_mmu);
    break;
  case 0x71:
    ld<at_hl, c>(m_cpu, m_mmu);
    break;
  case 0x72:
    ld<at_hl, d>(m_cpu, m_mmu);
    break;
  case 0x73:
    ld<at_hl, e>(m_cpu, m_mmu);
    break;
  case 0x74:
    ld<at_hl, h>(m_cpu, m_mmu);
    break;
  case 0x75:
    ld<at_hl, l>(m_cpu, m_mmu);
    break;
  case 0x76:
    goto not_implemented;
  case 0x77:
    ld<at_hl, a>(m_cpu, m_mmu);
    break;
  case 0x78:
    ld<a, b>(m_cpu, m_mmu);
    break;
  case 0x79:
    ld<a, c>(m_cpu, m_mmu);
    break;
  case 0x7a:
    ld<a, d>(m_cpu, m_mmu);
    break;
  case 0x7b:
    ld<a, e>(m_cpu, m_mmu);
    break;
  case 0x7c:
    ld<a, h>(m_cpu, m_mmu);
    break;
  case 0x7d:
    ld<a, l>(m_cpu, m_mmu);
    break;
  case 0x7e:
    ld<a, at_hl>(m_cpu, m_mmu);
    break;
  case 0x7f:
    ld<a, a>(m_cpu, m_mmu);
    break;
  case 0x80:
    goto not_implemented;
  case 0x81:
    goto not_implemented;
  case 0x82:
    goto not_implemented;
  case 0x83:
    goto not_implemented;
  case 0x84:
    goto not_implemented;
  case 0x85:
    goto not_implemented;
  case 0x86:
    goto not_implemented;
  case 0x87:
    goto not_implemented;
  case 0x88:
    goto not_implemented;
  case 0x89:
    goto not_implemented;
  case 0x8a:
    goto not_implemented;
  case 0x8b:
    goto not_implemented;
  case 0x8c:
    goto not_implemented;
  case 0x8d:
    goto not_implemented;
  case 0x8e:
    goto not_implemented;
  case 0x8f:
    goto not_implemented;
  case 0x90:
    goto not_implemented;
  case 0x91:
    goto not_implemented;
  case 0x92:
    goto not_implemented;
  case 0x93:
    goto not_implemented;
  case 0x94:
    goto not_implemented;
  case 0x95:
    goto not_implemented;
  case 0x96:
    goto not_implemented;
  case 0x97:
    goto not_implemented;
  case 0x98:
    goto not_implemented;
  case 0x99:
    goto not_implemented;
  case 0x9a:
    goto not_implemented;
  case 0x9b:
    goto not_implemented;
  case 0x9c:
    goto not_implemented;
  case 0x9d:
    goto not_implemented;
  case 0x9e:
    goto not_implemented;
  case 0x9f:
    goto not_implemented;
  case 0xa0:
    goto not_implemented;
  case 0xa1:
    goto not_implemented;
  case 0xa2:
    goto not_implemented;
  case 0xa3:
    goto not_implemented;
  case 0xa4:
    goto not_implemented;
  case 0xa5:
    goto not_implemented;
  case 0xa6:
    goto not_implemented;
  case 0xa7:
    goto not_implemented;
  case 0xa8:
    xor_<b>(m_cpu, m_mmu);
    break;
  case 0xa9:
    xor_<c>(m_cpu, m_mmu);
    break;
  case 0xaa:
    xor_<d>(m_cpu, m_mmu);
    break;
  case 0xab:
    xor_<e>(m_cpu, m_mmu);
    break;
  case 0xac:
    xor_<h>(m_cpu, m_mmu);
    break;
  case 0xad:
    xor_<l>(m_cpu, m_mmu);
    break;
  case 0xae:
    xor_<at_hl>(m_cpu, m_mmu);
    break;
  case 0xaf:
    xor_<a>(m_cpu, m_mmu);
    break;
  case 0xb0:
    goto not_implemented;
  case 0xb1:
    goto not_implemented;
  case 0xb2:
    goto not_implemented;
  case 0xb3:
    goto not_implemented;
  case 0xb4:
    goto not_implemented;
  case 0xb5:
    goto not_implemented;
  case 0xb6:
    goto not_implemented;
  case 0xb7:
    goto not_implemented;
  case 0xb8:
    goto not_implemented;
  case 0xb9:
    goto not_implemented;
  case 0xba:
    goto not_implemented;
  case 0xbb:
    goto not_implemented;
  case 0xbc:
    goto not_implemented;
  case 0xbd:
    goto not_implemented;
  case 0xbe:
    goto not_implemented;
  case 0xbf:
    goto not_implemented;
  case 0xc0:
    goto not_implemented;
  case 0xc1:
    goto not_implemented;
  case 0xc2:
    goto not_implemented;
  case 0xc3:
    goto not_implemented;
  case 0xc4:
    goto not_implemented;
  case 0xc5:
    goto not_implemented;
  case 0xc6:
    goto not_implemented;
  case 0xc7:
    goto not_implemented;
  case 0xc8:
    goto not_implemented;
  case 0xc9:
    goto not_implemented;
  case 0xca:
    goto not_implemented;
  case 0xcb:
    goto not_implemented;
  case 0xcc:
    goto not_implemented;
  case 0xcd:
    goto not_implemented;
  case 0xce:
    goto not_implemented;
  case 0xcf:
    goto not_implemented;
  case 0xd0:
    goto not_implemented;
  case 0xd1:
    goto not_implemented;
  case 0xd2:
    goto not_implemented;
  case 0xd3:
    goto not_implemented;
  case 0xd4:
    goto not_implemented;
  case 0xd5:
    goto not_implemented;
  case 0xd6:
    goto not_implemented;
  case 0xd7:
    goto not_implemented;
  case 0xd8:
    goto not_implemented;
  case 0xd9:
    goto not_implemented;
  case 0xda:
    goto not_implemented;
  case 0xdb:
    goto not_implemented;
  case 0xdc:
    goto not_implemented;
  case 0xdd:
    goto not_implemented;
  case 0xde:
    goto not_implemented;
  case 0xdf:
    goto not_implemented;
  case 0xe0:
    goto not_implemented;
  case 0xe1:
    goto not_implemented;
  case 0xe2:
    ld_at_c(m_cpu, m_mmu);
    break;
  case 0xe3:
    goto not_implemented;
  case 0xe4:
    goto not_implemented;
  case 0xe5:
    goto not_implemented;
  case 0xe6:
    goto not_implemented;
  case 0xe7:
    goto not_implemented;
  case 0xe8:
    goto not_implemented;
  case 0xe9:
    goto not_implemented;
  case 0xea:
    goto not_implemented;
  case 0xeb:
    goto not_implemented;
  case 0xec:
    goto not_implemented;
  case 0xed:
    goto not_implemented;
  case 0xee:
    goto not_implemented;
  case 0xef:
    goto not_implemented;
  case 0xf0:
    goto not_implemented;
  case 0xf1:
    goto not_implemented;
  case 0xf2:
    goto not_implemented;
  case 0xf3:
    goto not_implemented;
  case 0xf4:
    goto not_implemented;
  case 0xf5:
    goto not_implemented;
  case 0xf6:
    goto not_implemented;
  case 0xf7:
    goto not_implemented;
  case 0xf8:
    goto not_implemented;
  case 0xf9:
    goto not_implemented;
  case 0xfa:
    goto not_implemented;
  case 0xfb:
    goto not_implemented;
  case 0xfc:
    goto not_implemented;
  case 0xfd:
    goto not_implemented;
  case 0xfe:
    goto not_implemented;
  case 0xff:
    goto not_implemented;
  default:
  not_implemented:
    std::printf("Instruction 0x%x (at 0x%x) not implemented!", opcode,
                m_cpu.pc);
    std::exit(EXIT_FAILURE);
  }
}

void gameboy::extended_step(u8 opcode) {
  switch (opcode) {
  case 0x00:
    goto not_implemented;
  case 0x01:
    goto not_implemented;
  case 0x02:
    goto not_implemented;
  case 0x03:
    goto not_implemented;
  case 0x04:
    goto not_implemented;
  case 0x05:
    goto not_implemented;
  case 0x06:
    goto not_implemented;
  case 0x07:
    goto not_implemented;
  case 0x08:
    goto not_implemented;
  case 0x09:
    goto not_implemented;
  case 0x0a:
    goto not_implemented;
  case 0x0b:
    goto not_implemented;
  case 0x0c:
    goto not_implemented;
  case 0x0d:
    goto not_implemented;
  case 0x0e:
    goto not_implemented;
  case 0x0f:
    goto not_implemented;
  case 0x10:
    goto not_implemented;
  case 0x11:
    goto not_implemented;
  case 0x12:
    goto not_implemented;
  case 0x13:
    goto not_implemented;
  case 0x14:
    goto not_implemented;
  case 0x15:
    goto not_implemented;
  case 0x16:
    goto not_implemented;
  case 0x17:
    goto not_implemented;
  case 0x18:
    goto not_implemented;
  case 0x19:
    goto not_implemented;
  case 0x1a:
    goto not_implemented;
  case 0x1b:
    goto not_implemented;
  case 0x1c:
    goto not_implemented;
  case 0x1d:
    goto not_implemented;
  case 0x1e:
    goto not_implemented;
  case 0x1f:
    goto not_implemented;
  case 0x20:
    goto not_implemented;
  case 0x21:
    goto not_implemented;
  case 0x22:
    goto not_implemented;
  case 0x23:
    goto not_implemented;
  case 0x24:
    goto not_implemented;
  case 0x25:
    goto not_implemented;
  case 0x26:
    goto not_implemented;
  case 0x27:
    goto not_implemented;
  case 0x28:
    goto not_implemented;
  case 0x29:
    goto not_implemented;
  case 0x2a:
    goto not_implemented;
  case 0x2b:
    goto not_implemented;
  case 0x2c:
    goto not_implemented;
  case 0x2d:
    goto not_implemented;
  case 0x2e:
    goto not_implemented;
  case 0x2f:
    goto not_implemented;
  case 0x30:
    goto not_implemented;
  case 0x31:
    goto not_implemented;
  case 0x32:
    goto not_implemented;
  case 0x33:
    goto not_implemented;
  case 0x34:
    goto not_implemented;
  case 0x35:
    goto not_implemented;
  case 0x36:
    goto not_implemented;
  case 0x37:
    goto not_implemented;
  case 0x38:
    goto not_implemented;
  case 0x39:
    goto not_implemented;
  case 0x3a:
    goto not_implemented;
  case 0x3b:
    goto not_implemented;
  case 0x3c:
    goto not_implemented;
  case 0x3d:
    goto not_implemented;
  case 0x3e:
    goto not_implemented;
  case 0x3f:
    goto not_implemented;
  case 0x40:
    goto not_implemented;
  case 0x41:
    goto not_implemented;
  case 0x42:
    goto not_implemented;
  case 0x43:
    goto not_implemented;
  case 0x44:
    goto not_implemented;
  case 0x45:
    goto not_implemented;
  case 0x46:
    goto not_implemented;
  case 0x47:
    goto not_implemented;
  case 0x48:
    goto not_implemented;
  case 0x49:
    goto not_implemented;
  case 0x4a:
    goto not_implemented;
  case 0x4b:
    goto not_implemented;
  case 0x4c:
    goto not_implemented;
  case 0x4d:
    goto not_implemented;
  case 0x4e:
    goto not_implemented;
  case 0x4f:
    goto not_implemented;
  case 0x50:
    goto not_implemented;
  case 0x51:
    goto not_implemented;
  case 0x52:
    goto not_implemented;
  case 0x53:
    goto not_implemented;
  case 0x54:
    goto not_implemented;
  case 0x55:
    goto not_implemented;
  case 0x56:
    goto not_implemented;
  case 0x57:
    goto not_implemented;
  case 0x58:
    goto not_implemented;
  case 0x59:
    goto not_implemented;
  case 0x5a:
    goto not_implemented;
  case 0x5b:
    goto not_implemented;
  case 0x5c:
    goto not_implemented;
  case 0x5d:
    goto not_implemented;
  case 0x5e:
    goto not_implemented;
  case 0x5f:
    goto not_implemented;
  case 0x60:
    goto not_implemented;
  case 0x61:
    goto not_implemented;
  case 0x62:
    goto not_implemented;
  case 0x63:
    goto not_implemented;
  case 0x64:
    goto not_implemented;
  case 0x65:
    goto not_implemented;
  case 0x66:
    goto not_implemented;
  case 0x67:
    goto not_implemented;
  case 0x68:
    goto not_implemented;
  case 0x69:
    goto not_implemented;
  case 0x6a:
    goto not_implemented;
  case 0x6b:
    goto not_implemented;
  case 0x6c:
    goto not_implemented;
  case 0x6d:
    goto not_implemented;
  case 0x6e:
    goto not_implemented;
  case 0x6f:
    goto not_implemented;
  case 0x70:
    goto not_implemented;
  case 0x71:
    goto not_implemented;
  case 0x72:
    goto not_implemented;
  case 0x73:
    goto not_implemented;
  case 0x74:
    goto not_implemented;
  case 0x75:
    goto not_implemented;
  case 0x76:
    goto not_implemented;
  case 0x77:
    goto not_implemented;
  case 0x78:
    bit<b, 7>(m_cpu, m_mmu);
    break;
  case 0x79:
    bit<c, 7>(m_cpu, m_mmu);
    break;
  case 0x7a:
    bit<d, 7>(m_cpu, m_mmu);
    break;
  case 0x7b:
    bit<e, 7>(m_cpu, m_mmu);
    break;
  case 0x7c:
    bit<h, 7>(m_cpu, m_mmu);
    break;
  case 0x7d:
    bit<l, 7>(m_cpu, m_mmu);
    break;
  case 0x7e:
    bit<at_hl, 7>(m_cpu, m_mmu);
    break;
  case 0x7f:
    bit<a, 7>(m_cpu, m_mmu);
    break;
  case 0x80:
    goto not_implemented;
  case 0x81:
    goto not_implemented;
  case 0x82:
    goto not_implemented;
  case 0x83:
    goto not_implemented;
  case 0x84:
    goto not_implemented;
  case 0x85:
    goto not_implemented;
  case 0x86:
    goto not_implemented;
  case 0x87:
    goto not_implemented;
  case 0x88:
    goto not_implemented;
  case 0x89:
    goto not_implemented;
  case 0x8a:
    goto not_implemented;
  case 0x8b:
    goto not_implemented;
  case 0x8c:
    goto not_implemented;
  case 0x8d:
    goto not_implemented;
  case 0x8e:
    goto not_implemented;
  case 0x8f:
    goto not_implemented;
  case 0x90:
    goto not_implemented;
  case 0x91:
    goto not_implemented;
  case 0x92:
    goto not_implemented;
  case 0x93:
    goto not_implemented;
  case 0x94:
    goto not_implemented;
  case 0x95:
    goto not_implemented;
  case 0x96:
    goto not_implemented;
  case 0x97:
    goto not_implemented;
  case 0x98:
    goto not_implemented;
  case 0x99:
    goto not_implemented;
  case 0x9a:
    goto not_implemented;
  case 0x9b:
    goto not_implemented;
  case 0x9c:
    goto not_implemented;
  case 0x9d:
    goto not_implemented;
  case 0x9e:
    goto not_implemented;
  case 0x9f:
    goto not_implemented;
  case 0xa0:
    goto not_implemented;
  case 0xa1:
    goto not_implemented;
  case 0xa2:
    goto not_implemented;
  case 0xa3:
    goto not_implemented;
  case 0xa4:
    goto not_implemented;
  case 0xa5:
    goto not_implemented;
  case 0xa6:
    goto not_implemented;
  case 0xa7:
    goto not_implemented;
  case 0xa8:
    goto not_implemented;
  case 0xa9:
    goto not_implemented;
  case 0xaa:
    goto not_implemented;
  case 0xab:
    goto not_implemented;
  case 0xac:
    goto not_implemented;
  case 0xad:
    goto not_implemented;
  case 0xae:
    goto not_implemented;
  case 0xaf:
    goto not_implemented;
  case 0xb0:
    goto not_implemented;
  case 0xb1:
    goto not_implemented;
  case 0xb2:
    goto not_implemented;
  case 0xb3:
    goto not_implemented;
  case 0xb4:
    goto not_implemented;
  case 0xb5:
    goto not_implemented;
  case 0xb6:
    goto not_implemented;
  case 0xb7:
    goto not_implemented;
  case 0xb8:
    goto not_implemented;
  case 0xb9:
    goto not_implemented;
  case 0xba:
    goto not_implemented;
  case 0xbb:
    goto not_implemented;
  case 0xbc:
    goto not_implemented;
  case 0xbd:
    goto not_implemented;
  case 0xbe:
    goto not_implemented;
  case 0xbf:
    goto not_implemented;
  case 0xc0:
    goto not_implemented;
  case 0xc1:
    goto not_implemented;
  case 0xc2:
    goto not_implemented;
  case 0xc3:
    goto not_implemented;
  case 0xc4:
    goto not_implemented;
  case 0xc5:
    goto not_implemented;
  case 0xc6:
    goto not_implemented;
  case 0xc7:
    goto not_implemented;
  case 0xc8:
    goto not_implemented;
  case 0xc9:
    goto not_implemented;
  case 0xca:
    goto not_implemented;
  case 0xcb:
    goto not_implemented;
  case 0xcc:
    goto not_implemented;
  case 0xcd:
    goto not_implemented;
  case 0xce:
    goto not_implemented;
  case 0xcf:
    goto not_implemented;
  case 0xd0:
    goto not_implemented;
  case 0xd1:
    goto not_implemented;
  case 0xd2:
    goto not_implemented;
  case 0xd3:
    goto not_implemented;
  case 0xd4:
    goto not_implemented;
  case 0xd5:
    goto not_implemented;
  case 0xd6:
    goto not_implemented;
  case 0xd7:
    goto not_implemented;
  case 0xd8:
    goto not_implemented;
  case 0xd9:
    goto not_implemented;
  case 0xda:
    goto not_implemented;
  case 0xdb:
    goto not_implemented;
  case 0xdc:
    goto not_implemented;
  case 0xdd:
    goto not_implemented;
  case 0xde:
    goto not_implemented;
  case 0xdf:
    goto not_implemented;
  case 0xe0:
    goto not_implemented;
  case 0xe1:
    goto not_implemented;
  case 0xe2:
    goto not_implemented;
  case 0xe3:
    goto not_implemented;
  case 0xe4:
    goto not_implemented;
  case 0xe5:
    goto not_implemented;
  case 0xe6:
    goto not_implemented;
  case 0xe7:
    goto not_implemented;
  case 0xe8:
    goto not_implemented;
  case 0xe9:
    goto not_implemented;
  case 0xea:
    goto not_implemented;
  case 0xeb:
    goto not_implemented;
  case 0xec:
    goto not_implemented;
  case 0xed:
    goto not_implemented;
  case 0xee:
    goto not_implemented;
  case 0xef:
    goto not_implemented;
  case 0xf0:
    goto not_implemented;
  case 0xf1:
    goto not_implemented;
  case 0xf2:
    goto not_implemented;
  case 0xf3:
    goto not_implemented;
  case 0xf4:
    goto not_implemented;
  case 0xf5:
    goto not_implemented;
  case 0xf6:
    goto not_implemented;
  case 0xf7:
    goto not_implemented;
  case 0xf8:
    goto not_implemented;
  case 0xf9:
    goto not_implemented;
  case 0xfa:
    goto not_implemented;
  case 0xfb:
    goto not_implemented;
  case 0xfc:
    goto not_implemented;
  case 0xfd:
    goto not_implemented;
  case 0xfe:
    goto not_implemented;
  case 0xff:
    goto not_implemented;
  default:
  not_implemented:
    std::printf("Instruction 0x%x (at 0x%x) not implemented!", opcode,
                m_cpu.pc);
    std::exit(EXIT_FAILURE);
  }
}