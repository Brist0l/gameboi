#include "cpu_rotate.h"
#include "cpu_shift.h"
#include "debug.h"
#include "flags.h"
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

				case 0x3f:
					// SRL A

					opcd_srl_a();
					break;


				case 0x4f:
					// BIT 1,A
					// lenght is 2 bytes

					printf("BIT 1,A\n");
					exit(1);
					break;

				case 0x7c:
					// BIT 7,H
					// lenght is 2 bytes
					// basically get the 7th bit
					// of H and see if it's 1 or 0
					// changes:
					//
					// Z = 1 ( if bit is 0)
					// Z = 0 ( if bit is 1)
					// N = 0
					// H = 1
					// C = same


					dprintf("BIT 7,H\n");
					dprintf("value of register H is : 0b%b\n",cpu.H);

					seventh_bit = cpu.H & GET7BIT;
					seventh_bit >>= 7;

					dprintf("value of seventh bit of H is : 0b%b\n",seventh_bit);

					setz(!seventh_bit);
					setn(0);
					seth(1);

					break;

				default:
					printf("NULL RN\n");
					printf("[%lld]Opcode to implement: 0xCB%02x\n",instr_cnt,memory_read(cpu.PC));
					exit(1);

					break;
			}
}
