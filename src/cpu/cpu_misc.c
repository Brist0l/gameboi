#include "debug.h"
#include "cpu.h"
#include "flags.h"

void opcd_daa(){
 	// DAA
	// bruh wot
    int correction = 0;
    if (geth() || (!getn() && (cpu.A & 0x0F) > 0x09)) {
        correction |= 0x06;
    }
    if (getC() || (!getn() && (cpu.A & 0xFF) > 0x99)) {
        correction |= 0x60;
        setc(true);
    }
    bool carry = false;
    int right = correction;
    if (getn()) {
        carry = true;
        right = (~right) & 0xFF;
    }
    int result = (cpu.A + right + (carry ? 1 : 0));
    cpu.A = (result);
    seth(false);
    setz((result & 0xFF) == 0);
	
	dprintf("ok");
}

void opcd_cpl(){
	// Take compliment of register A

	dprintf("CPL\n");
	dprintf("Value of register A before: 0b%08b\n",cpu.A);

	cpu.A = ~(cpu.A);

	setn(1);
	seth(1);

	dprintf("Value of register A after: 0b%08b\n",cpu.A);

}

void opcd_scf(){
	// SCF
	// Set the C flag to 1
	// N = 0
	// H = 0

	setc(1);
	setn(0);
	seth(0);
}

void opcd_ccf(){
	// CCF
	// take compliment of C flag

	if(getC() == 0)
		setc(1);
	else
		setc(0);

	setn(0);
	seth(0);
}
