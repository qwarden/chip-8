#ifndef _INSTRS_H_
#define _INSTRS_H_

#include "cpu_t.h"

void instr_invalid(CPU* c, Instr_Args* a);

void instr_00E0(CPU* c);
void instr_00EE(CPU* c);

void instr_1nnn(CPU* c, Instr_Args* a);
void instr_2nnn(CPU* c, Instr_Args* a);
void instr_3xkk(CPU* c, Instr_Args* a);
void instr_4xkk(CPU* c, Instr_Args* a);
void instr_5xy0(CPU* c, Instr_Args* a);
void instr_6xkk(CPU* c, Instr_Args* a);
void instr_7xkk(CPU* c, Instr_Args* a);

void instr_8xy0(CPU* c, Instr_Args* a);
void instr_8xy1(CPU* c, Instr_Args* a);
void instr_8xy2(CPU* c, Instr_Args* a);
void instr_8xy3(CPU* c, Instr_Args* a);
void instr_8xy4(CPU* c, Instr_Args* a);
void instr_8xy5(CPU* c, Instr_Args* a);
void instr_8xy6(CPU* c, Instr_Args* a);
void instr_8xy7(CPU* c, Instr_Args* a);
void instr_8xyE(CPU* c, Instr_Args* a);
void instr_9xy0(CPU* c, Instr_Args* a);
void instr_Annn(CPU* c, Instr_Args* a);
void instr_Bnnn(CPU* c, Instr_Args* a);
void instr_Cxkk(CPU* c, Instr_Args* a);
void instr_Dxyn(CPU* c, Instr_Args* a);

void instr_Ex9E(CPU* c, Instr_Args* a);
void instr_ExA1(CPU* c, Instr_Args* a);

void instr_Fx07(CPU* c, Instr_Args* a);
void instr_Fx0A(CPU* c, Instr_Args* a);
void instr_Fx15(CPU* c, Instr_Args* a);
void instr_Fx18(CPU* c, Instr_Args* a);
void instr_Fx1E(CPU* c, Instr_Args* a);
void instr_Fx29(CPU* c, Instr_Args* a);
void instr_Fx33(CPU* c, Instr_Args* a);
void instr_Fx55(CPU* c, Instr_Args* a);
void instr_Fx65(CPU* c, Instr_Args* a);

void instrs_00xx(CPU* c, Instr_Args* a);
void instrs_8xxx(CPU* c, Instr_Args* a);
void instrs_Exxx(CPU* c, Instr_Args* a);
void instrs_Fxxx(CPU* c, Instr_Args* a);

#endif // _INSTRS_H_
