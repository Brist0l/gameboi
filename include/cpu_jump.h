#ifndef CPU_JUMP_H
#define CPU_JUMP_H

void opcd_rst_0();
void opcd_rst_1();
void opcd_rst_2();
void opcd_rst_3();
void opcd_rst_4();
void opcd_rst_5();
void opcd_rst_6();
void opcd_rst_7();
void opcd_ret();
void opcd_reti();
void opcd_ret_nc();
void opcd_ret_nz();
void opcd_pop_af();
void opcd_ret_c();
void opcd_ret_z();
void opcd_jp_hl();
void opcd_jp_u16();
void opcd_jp_z_u16();
void opcd_jp_nz_u16();
void opcd_jp_nc_u16();
void opcd_jp_c_u16();
void opcd_call_nz_u16();
void opcd_call_z_u16();
void opcd_call_c_u16();
void opcd_call_nc_u16();
void opcd_call_u16();
void opcd_jr_u8();
void opcd_jr_nz_u8();
void opcd_jr_z_u8();
void opcd_jr_nc_u8();
void opcd_jr_c_u8();

#endif /* CPU_JUMP_H */
