#ifndef CPU_ALU_H
#define CPU_ALU_H

void opcd_add_hl_hl();
void opcd_add_a_b();
void opcd_add_a_hl();
void opcd_add_a_a();
void opcd_sub_a_b();
void opcd_sub_a_c();
void opcd_or_b();
void opcd_or_c();
void opcd_or_hl();
void opcd_or_a();
void opcd_xor_c();
void opcd_xor_l();
void opcd_xor_memhl();
void opcd_xor_a();
void opcd_add_a_u8();
void opcd_cp_a_hl();
void opcd_sub_u8();
void opcd_and_u8();

#endif /* CPU_ALU_H */
