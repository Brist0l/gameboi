#include "cpu_rotate.h"
#include "cpu_shift.h"
#include "registers.h"
#include "cpu_bit.h"

#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "memory.h"

void execute_cb(unsigned int nxtbyt,long long instr_cnt){
			switch(nxtbyt){
				case 0x00:
					// RLC B

					opcd_rlc_b();
					break;

				case 0x01:
					// RLC C

					opcd_rlc_c();
					break;

				case 0x02:
					// RLC D

					opcd_rlc_d();
					break;

				case 0x03:
					// RLC E

					opcd_rlc_e();
					break;

				case 0x04:
					// RLC H

					opcd_rlc_h();
					break;

				case 0x05:
					// RLC L

					opcd_rlc_l();
					break;

				case 0x06:
					// RLC (HL)

					opcd_rlc_hl();
					break;

				case 0x7:
					// RLC A

					opcd_rlc_a();
					break;

				case 0x8:
					// RRC B

					opcd_rrc_b();
					break;

				case 0x9:
					// RRC C

					opcd_rrc_c();
					break;

				case 0xa:
					// RRC D

					opcd_rrc_d();
					break;

				case 0xb:
					// RRC E

					opcd_rrc_e();
					break;

				case 0xc:
					// RRC H

					opcd_rrc_h();
					break;

				case 0xd:
					// RRC L

					opcd_rrc_l();
					break;

				case 0xe:
					// RRC (HL)

					opcd_rrc_hl();
					break;

				case 0xf:
					// RRC A

					opcd_rrc_a();
					break;

				case 0x10:
					// RL B

					opcd_rl_b();
					break;

				case 0x11:
					// RL C
					// lenght is 2 bytes
					// Shift the value in C by 1
					// and put carry flag value in
					// the LSB and copy the shifted
					// out bit to the carry flag

					opcd_rl_c();
					break;

				case 0x12:
					// RL D

					opcd_rl_d();
					break;

				case 0x13:
					// RL E

					opcd_rl_e();
					break;

				case 0x14:
					// RL H

					opcd_rl_h();
					break;

				case 0x15:
					// RL L

					opcd_rl_l();
					break;

				case 0x16:
					// RL (HL)

					opcd_rl_hl();
					break;

				case 0x17:
					// RL A

					opcd_rl_a();
					break;

				case 0x18:
					// RR B

					opcd_rr_b();
					break;

				case 0x19:
					// RR C
					// Rotate the values of C with the C flag
					// i.e just shift the values to the right
					// and the value of C goes into MSB and
					// LSB into the C flag


					opcd_rr_c();
					//exit(1);
					break;

				case 0x1a:
					// RR D
					// Rotate the values of D with the C flag
					// i.e just shift the values to the right
					// and the value of D goes into MSB and
					// LSB into the C flag

					opcd_rr_d();
					break;

				case 0x1b:
					// RR E
					// Rotate the values of E with the C flag
					// i.e just shift the values to the right
					// and the value of E goes into MSB and
					// LSB into the C flag

					opcd_rr_e();
					break;

				case 0x1c:
					// RR H

					opcd_rr_h();
					break;

				case 0x1d:
					// RR L

					opcd_rr_l();
					break;

				case 0x1e:
					// RR HL

					opcd_rr_hl();
					break;

				case 0x1f:
					// RR A
					// Rotate the values of A with the C flag
					// i.e just shift the values to the right
					// and the value of A goes into MSB and
					// LSB into the C flag

					opcd_rr_a();
					break;

				case 0x20:
					// SLA B

					opcd_sla_b();
					break;

				case 0x21:
					// SLA C

					opcd_sla_c();
					break;

				case 0x22:
					// SLA D

					opcd_sla_d();
					break;

				case 0x23:
					// SLA E

					opcd_sla_e();
					break;

				case 0x24:
					// SLA H

					opcd_sla_h();
					break;

				case 0x25:
					// SLA L

					opcd_sla_l();
					break;

				case 0x26:
					// SLA (HL)

					opcd_sla_hl();
					break;

				case 0x27:
					// SLA A

					opcd_sla_a();
					break;

				case 0x28:
					// SRA B

					opcd_sra_b();
					break;

				case 0x29:
					// SRA C

					opcd_sra_c();
					break;

				case 0x2a:
					// SRA D

					opcd_sra_d();
					break;

				case 0x2b:
					// SRA E

					opcd_sra_e();
					break;

				case 0x2c:
					// SRA H

					opcd_sra_h();
					break;

				case 0x2d:
					// SRA L

					opcd_sra_l();
					break;

				case 0x2e:
					// SRA (HL)

					opcd_sra_hl();
					break;

				case 0x2f:
					// SRA A

					opcd_sra_a();
					break;

				case 0x30:
					// SWAP B

					opcd_swap_b();
					break;

				case 0x31:
					// SWAP C

					opcd_swap_c();
					break;

				case 0x32:
					// SWAP D

					opcd_swap_d();
					break;

				case 0x33:
					// SWAP E

					opcd_swap_e();
					break;

				case 0x34:
					// SWAP H

					opcd_swap_h();
					break;

				case 0x35:
					// SWAP L

					opcd_swap_l();
					break;

				case 0x36:
					// SWAP (HL)
					// REDO

					opcd_swap_hl();
					break;

				case 0x37:
					// SWAP A
					// Swap the first 4 bits with the last 4 bits
					//
					// b7 b6 b5 b4 b3 b2 b1 b0
					// 	    ||
					// b3 b2 b1 b0 b7 b6 b5 b4
					//
					// Z = set flag
					// N = 0
					// H = 0
					// C = 0

					opcd_swap_a();
					break;

				case 0x38:
					// SRL B
					// lenght is 2 bytes
					// B's value is shifted to the right
					// by 1 bit.
					// The MSB is set to 0.
					// The carry flag is set to LSB
					// N and H are set to 0

					opcd_srl_b();
					break;

				case 0x39:
					// SRL C

					opcd_srl_c();
					break;

				case 0x3a:
					// SRL D

					opcd_srl_d();
					break;

				case 0x3b:
					// SRL E

					opcd_srl_e();
					break;

				case 0x3c:
					// SRL H

					opcd_srl_h();
					break;

				case 0x3d:
					// SRL L

					opcd_srl_l();
					break;
				case 0x3e:
					// SRL (HE)

					opcd_srl_hl();
					break;

				case 0x3f:
					// SRL A

					opcd_srl_a();
					break;
				
				case 0x40:
					// BIT 0, B

					opcd_bit_0_b();
					break;

				case 0x41:
					// BIT 0, C

					opcd_bit_0_c();
					break;

				case 0x42:
					// BIT 0, D

					opcd_bit_0_d();
					break;

				case 0x43:
					// BIT 0, E

					opcd_bit_0_e();
					break;

				case 0x44:
					// BIT 0, H

					opcd_bit_0_h();
					break;

				case 0x45:
					// BIT 0, L

					opcd_bit_0_l();
					break;

				case 0x46:
					// BIT 0, (HL)
					
					opcd_bit_0_hl();
					break;

				case 0x47:
					// BIT 0,A
					
					opcd_bit_0_a();
					break;
				
				case 0x48:
					// BIT 1 , B

					opcd_bit_1_b();
					break;

				case 0x49:
					// BIT 1 , C

					opcd_bit_1_c();
					break;

				case 0x4a:
					// BIT 1 , D

					opcd_bit_1_d();
					break;

				case 0x4b:
					// BIT 1 , E

					opcd_bit_1_e();
					break;

				case 0x4c:
					// BIT 1 , H

					opcd_bit_1_h();
					break;

				case 0x4d:
					// BIT 1 , L

					opcd_bit_1_l();
					break;

				case 0x4e:
					// BIT 1 , (HL)

					opcd_bit_1_b();
					break;

				case 0x4f:
					// BIT 1,A
					// lenght is 2 bytes
					
					opcd_bit_1_a();
					break;

				case 0x50:
					//BIT 2, B
					
					opcd_bit_2_b();
					break;

				case 0x51:
					//BIT 2, C
					
					opcd_bit_2_c();
					break;

				case 0x52:
					//BIT 2, D
					
					opcd_bit_2_d();
					break;

				case 0x53:
					//BIT 2, E

					opcd_bit_2_e();
					break;

				case 0x54:
					//BIT 2, H
					
					opcd_bit_2_h();
					break;

				case 0x55:
					//BIT 2, L
					
					opcd_bit_2_l();
					break;

				case 0x56:
					//BIT 2, (HL)
					
					opcd_bit_2_hl();
					break;

				case 0x57:
					//BIT 2, A
					
					opcd_bit_2_a();
					break;

				case 0x58:
					//BIT 3, B
					
					opcd_bit_3_b();
					break;

				case 0x59:
					//BIT 3, C
					
					opcd_bit_3_c();
					break;

				case 0x5a:
					//BIT 3, D
					
					opcd_bit_3_d();
					break;

				case 0x5b:
					//BIT 3, E
					
					opcd_bit_3_e();
					break;

				case 0x5c:
					//BIT 3, H
					
					opcd_bit_3_h();
					break;

				case 0x5d:
					//BIT 3, L
					
					opcd_bit_3_l();
					break;

				case 0x5e:
					//BIT 3, (HL)
					
					opcd_bit_3_hl();
					break;

				case 0x5f:
					//BIT 3, A
					
					opcd_bit_3_a();
					break;

				case 0x60:
					//BIT 4, B
					
					opcd_bit_4_b();
					break;

				case 0x61:
					//BIT 4, C
					
					opcd_bit_4_c();
					break;
					
				case 0x62:
					//BIT 4, D
					
					opcd_bit_4_d();
					break;

				case 0x63:
					//BIT 4, E
					
					opcd_bit_4_e();
					break;

				case 0x64:
					//BIT 4, H
					
					opcd_bit_4_h();
					break;

				case 0x65:
					//BIT 4, L
					
					opcd_bit_4_l();
					break;

				case 0x66:
					//BIT 4, (HL)
					
					opcd_bit_4_hl();
					break;

				case 0x67:
					//BIT 4, A
					
					opcd_bit_4_a();
					break;

				case 0x68:
					//BIT 5, B
					
					opcd_bit_5_b();
					break;

				case 0x69:
					//BIT 5, C
					
					opcd_bit_5_c();
					break;

				case 0x6a:
					//BIT 5, D
					
					opcd_bit_5_d();
					break;

				case 0x6b:
					//BIT 5, E
					
					opcd_bit_5_e();
					break;

				case 0x6c:
					//BIT 5, H
					
					opcd_bit_5_h();
					break;

				case 0x6d:
					//BIT 5, L
					
					opcd_bit_5_l();
					break;

				case 0x6e:
					//BIT 5, (HL)
					
					opcd_bit_5_hl();
					break;

				case 0x6f:
					//BIT 5, A
					
					opcd_bit_5_a();
					break;

				case 0x70:
					// BIT 6,B
					
					opcd_bit_6_b();
					break;
				case 0x71:
					// BIT 6,C
					
					opcd_bit_6_c();
					break;

				case 0x72:
					// BIT 6,D
					
					opcd_bit_6_d();
					break;

				case 0x73:
					// BIT 6,E
					
					opcd_bit_6_e();
					break;

				case 0x74:
					// BIT 6,H
					
					opcd_bit_6_h();
					break;

				case 0x75:
					// BIT 6,L
					
					opcd_bit_6_l();
					break;

				case 0x76:
					// BIT 6,(HL)
					
					opcd_bit_6_hl();
					break;

				case 0x77:
					// BIT 6,A
					
					opcd_bit_6_a();
					break;

				case 0x78:
					// BIT 7,B
					
					opcd_bit_7_b();
					break;

				case 0x79:
					// BIT 7,C
					
					opcd_bit_7_c();
					break;

				case 0x7a:
					// BIT 7,D
					
					opcd_bit_7_d();
					break;

				case 0x7b:
					// BIT 7,E
					
					opcd_bit_7_e();
					break;

				case 0x7c:
					// BIT 7,H
					
					opcd_bit_7_h();
					break;

				case 0x7d:
					// BIT 7,L
					
					opcd_bit_7_l();
					break;

				case 0x7e:
					// BIT 7,(HL)
					
					opcd_bit_7_hl();
					break;

				case 0x7f:
					// BIT 7,A
					
					opcd_bit_7_a();
					break;
				
				case 0x80:
					// RES 0, B

					opcd_res_0_b();
					break;

				case 0x81:
					// RES 0, C

					opcd_res_0_c();
					break;
					
				case 0x82:
					// RES 0, D

					opcd_res_0_d();
					break;

				case 0x83:
					// RES 0, E

					opcd_res_0_e();
					break;

				case 0x84:
					// RES 0, H

					opcd_res_0_h();
					break;

				case 0x85:
					// RES 0, L

					opcd_res_0_l();
					break;

				case 0x86:
					// RES 0, (HL)

					opcd_res_0_hl();
					break;

				case 0x87:
					// RES 0, A

					opcd_res_0_a();
					break;

				case 0x88:
					// RES 1, B

					opcd_res_1_b();
					break;

				case 0x89:
					// RES 1, C

					opcd_res_1_c();
					break;

				case 0x8a:
					// RES 1, D

					opcd_res_1_d();
					break;

				case 0x8b:
					// RES 1, E

					opcd_res_1_e();
					break;

				case 0x8c:
					// RES 1, H

					opcd_res_1_h();
					break;

				case 0x8d:
					// RES 1, L

					opcd_res_1_l();
					break;

				case 0x8e:
					// RES 1, (HL)

					opcd_res_1_hl();
					break;

				case 0x8f:
					// RES 1, A

					opcd_res_1_a();
					break;

				case 0x90: res_bit(&cpu.B, 2); break;
				case 0x91: res_bit(&cpu.C, 2); break;
				case 0x92: res_bit(&cpu.D, 2); break;
				case 0x93: res_bit(&cpu.E, 2); break;
				case 0x94: res_bit(&cpu.H, 2); break;
				case 0x95: res_bit(&cpu.L, 2); break;

				case 0x96:
				    u8 = memory_read(getHL());
				    u8 &= ~(1 << 2);
				    memory_write(getHL(), u8);
				    break;

				case 0x97: res_bit(&cpu.A, 2); break;


				case 0x98: res_bit(&cpu.B, 3); break;
				case 0x99: res_bit(&cpu.C, 3); break;
				case 0x9A: res_bit(&cpu.D, 3); break;
				case 0x9B: res_bit(&cpu.E, 3); break;
				case 0x9C: res_bit(&cpu.H, 3); break;
				case 0x9D: res_bit(&cpu.L, 3); break;

				case 0x9E:
				    u8 = memory_read(getHL());
				    u8 &= ~(1 << 3);
				    memory_write(getHL(), u8);
				    break;

				case 0x9F: res_bit(&cpu.A, 3); break;


				case 0xA0: res_bit(&cpu.B, 4); break;
				case 0xA1: res_bit(&cpu.C, 4); break;
				case 0xA2: res_bit(&cpu.D, 4); break;
				case 0xA3: res_bit(&cpu.E, 4); break;
				case 0xA4: res_bit(&cpu.H, 4); break;
				case 0xA5: res_bit(&cpu.L, 4); break;

				case 0xA6:
				    u8 = memory_read(getHL());
				    u8 &= ~(1 << 4);
				    memory_write(getHL(), u8);
				    break;

				case 0xA7: res_bit(&cpu.A, 4); break;


				case 0xA8: res_bit(&cpu.B, 5); break;
				case 0xA9: res_bit(&cpu.C, 5); break;
				case 0xAA: res_bit(&cpu.D, 5); break;
				case 0xAB: res_bit(&cpu.E, 5); break;
				case 0xAC: res_bit(&cpu.H, 5); break;
				case 0xAD: res_bit(&cpu.L, 5); break;

				case 0xAE:
				    u8 = memory_read(getHL());
				    u8 &= ~(1 << 5);
				    memory_write(getHL(), u8);
				    break;

				case 0xAF: res_bit(&cpu.A, 5); break;


				case 0xB0: res_bit(&cpu.B, 6); break;
				case 0xB1: res_bit(&cpu.C, 6); break;
				case 0xB2: res_bit(&cpu.D, 6); break;
				case 0xB3: res_bit(&cpu.E, 6); break;
				case 0xB4: res_bit(&cpu.H, 6); break;
				case 0xB5: res_bit(&cpu.L, 6); break;

				case 0xB6:
				    u8 = memory_read(getHL());
				    u8 &= ~(1 << 6);
				    memory_write(getHL(), u8);
				    break;

				case 0xB7: res_bit(&cpu.A, 6); break;


				case 0xB8: res_bit(&cpu.B, 7); break;
				case 0xB9: res_bit(&cpu.C, 7); break;
				case 0xBA: res_bit(&cpu.D, 7); break;
				case 0xBB: res_bit(&cpu.E, 7); break;
				case 0xBC: res_bit(&cpu.H, 7); break;
				case 0xBD: res_bit(&cpu.L, 7); break;

				case 0xBE:
				    u8 = memory_read(getHL());
				    u8 &= ~(1 << 7);
				    memory_write(getHL(), u8);
				    break;

				case 0xBF: res_bit(&cpu.A, 7); break;
				case 0xC0: set_bit(&cpu.B, 0); break;
				case 0xC1: set_bit(&cpu.C, 0); break;
				case 0xC2: set_bit(&cpu.D, 0); break;
				case 0xC3: set_bit(&cpu.E, 0); break;
				case 0xC4: set_bit(&cpu.H, 0); break;
				case 0xC5: set_bit(&cpu.L, 0); break;
				case 0xC6: set_bit_hl(0); break;
				case 0xC7: set_bit(&cpu.A, 0); break;

				case 0xC8: set_bit(&cpu.B, 1); break;
				case 0xC9: set_bit(&cpu.C, 1); break;
				case 0xCA: set_bit(&cpu.D, 1); break;
				case 0xCB: set_bit(&cpu.E, 1); break;
				case 0xCC: set_bit(&cpu.H, 1); break;
				case 0xCD: set_bit(&cpu.L, 1); break;
				case 0xCE: set_bit_hl(1); break;
				case 0xCF: set_bit(&cpu.A, 1); break;

				case 0xD0: set_bit(&cpu.B, 2); break;
				case 0xD1: set_bit(&cpu.C, 2); break;
				case 0xD2: set_bit(&cpu.D, 2); break;
				case 0xD3: set_bit(&cpu.E, 2); break;
				case 0xD4: set_bit(&cpu.H, 2); break;
				case 0xD5: set_bit(&cpu.L, 2); break;
				case 0xD6: set_bit_hl(2); break;
				case 0xD7: set_bit(&cpu.A, 2); break;

				case 0xD8: set_bit(&cpu.B, 3); break;
				case 0xD9: set_bit(&cpu.C, 3); break;
				case 0xDA: set_bit(&cpu.D, 3); break;
				case 0xDB: set_bit(&cpu.E, 3); break;
				case 0xDC: set_bit(&cpu.H, 3); break;
				case 0xDD: set_bit(&cpu.L, 3); break;
				case 0xDE: set_bit_hl(3); break;
				case 0xDF: set_bit(&cpu.A, 3); break;

				case 0xE0: set_bit(&cpu.B, 4); break;
				case 0xE1: set_bit(&cpu.C, 4); break;
				case 0xE2: set_bit(&cpu.D, 4); break;
				case 0xE3: set_bit(&cpu.E, 4); break;
				case 0xE4: set_bit(&cpu.H, 4); break;
				case 0xE5: set_bit(&cpu.L, 4); break;
				case 0xE6: set_bit_hl(4); break;
				case 0xE7: set_bit(&cpu.A, 4); break;

				case 0xE8: set_bit(&cpu.B, 5); break;
				case 0xE9: set_bit(&cpu.C, 5); break;
				case 0xEA: set_bit(&cpu.D, 5); break;
				case 0xEB: set_bit(&cpu.E, 5); break;
				case 0xEC: set_bit(&cpu.H, 5); break;
				case 0xED: set_bit(&cpu.L, 5); break;
				case 0xEE: set_bit_hl(5); break;
				case 0xEF: set_bit(&cpu.A, 5); break;

				case 0xF0: set_bit(&cpu.B, 6); break;
				case 0xF1: set_bit(&cpu.C, 6); break;
				case 0xF2: set_bit(&cpu.D, 6); break;
				case 0xF3: set_bit(&cpu.E, 6); break;
				case 0xF4: set_bit(&cpu.H, 6); break;
				case 0xF5: set_bit(&cpu.L, 6); break;
				case 0xF6: set_bit_hl(6); break;
				case 0xF7: set_bit(&cpu.A, 6); break;

				case 0xF8: set_bit(&cpu.B, 7); break;
				case 0xF9: set_bit(&cpu.C, 7); break;
				case 0xFA: set_bit(&cpu.D, 7); break;
				case 0xFB: set_bit(&cpu.E, 7); break;
				case 0xFC: set_bit(&cpu.H, 7); break;
				case 0xFD: set_bit(&cpu.L, 7); break;
				case 0xFE: set_bit_hl(7); break;
				case 0xFF: set_bit(&cpu.A, 7); break;

				default:
					printf("NULL RN\n");
					printf("[%lld]Opcode to implement: 0xCB%02x\n",instr_cnt,memory_read(cpu.PC));
					exit(1);

					break;
			}
}
