#ifndef _CPU_T_H_
#define _CPU_T_H_

#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

#define NUM_REGS 0x10
#define STACK_SIZE 0x10
#define MEM_SIZE 0x1000
#define MEM_START 0x200
#define MEM_PRINT_LEN 64
#define MEM_PRINT_LINES 4
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 640
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NUM_CHARS 80
#define NUM_KEYS 0x10

#define DEBUG 0

typedef struct {
  uint8_t regs[NUM_REGS];
  uint16_t stack[STACK_SIZE];
  uint8_t memory[MEM_SIZE];
  uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
  uint8_t keys[NUM_KEYS];
  uint16_t I;
  uint16_t pc;
  uint8_t sp;
  uint8_t dt;
  uint8_t st;
  bool running;
  bool draw_screen;
  bool wait_for_key;
} CPU;

typedef struct {
  uint8_t idx;
  uint16_t nnn;
  uint8_t kk;
  uint8_t x;
  uint8_t y;
  uint8_t n;
} Instr_Args;

typedef void (*Instr)(CPU*, Instr_Args*);

#endif // _CPU_T_H_
