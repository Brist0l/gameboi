#ifndef CPU_JUMP_H
#define CPU_JUMP_H

void opcd_ret();
void opcd_ret_nc();
void opcd_ret_z();
void opcd_jp_hl();
void opcd_jp_u16();
void opcd_call_nz_u16();
void opcd_call_u16();
void opcd_jr_u8();
void opcd_jr_nz_u8();
void opcd_jr_z_u8();
void opcd_jr_nc_u8();
void opcd_jr_c_u8();

#endif /* CPU_JUMP_H */
