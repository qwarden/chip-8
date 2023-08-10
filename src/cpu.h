#ifndef _CPU_H_
#define _CPU_H_

#include <stdlib.h>

#include "cpu_t.h"
#include "instrs.h"

const static Instr instr_table[] = {
  instrs_00xx,
  instr_1nnn,
  instr_2nnn,
  instr_3xkk,
  instr_4xkk,
  instr_5xy0,
  instr_6xkk,
  instr_7xkk,
  instrs_8xxx,
  instr_9xy0,
  instr_Annn,
  instr_Bnnn,
  instr_Cxkk,
  instr_Dxyn,
  instrs_Exxx,
  instrs_Fxxx
};

const static uint8_t characters[NUM_CHARS] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

const static uint8_t key_map[NUM_KEYS] = {
  SDLK_0,
  SDLK_1,
  SDLK_2,
  SDLK_3,
  SDLK_4,
  SDLK_5,
  SDLK_6,
  SDLK_7,
  SDLK_8,
  SDLK_9,
  SDLK_a,
  SDLK_b,
  SDLK_c,
  SDLK_d,
  SDLK_e,
  SDLK_f
};

void run(CPU* c);
uint16_t fetch(CPU* c);
Instr_Args decode(uint16_t instr);
void exec(CPU* c, Instr_Args* a);

void reset(CPU* c);
void process_input(CPU* c);
void load_mem(CPU* c, uint8_t* data, uint16_t loc, size_t n);

size_t open_with_size(FILE *file, const char *filename);
uint8_t *read_into_buff(FILE *file, size_t size);

void print_regs(CPU* c);
void print_memory(CPU* c, uint16_t addr);
void print_screen(CPU* c);

#endif // _CPU_H_
