#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cpu.h"
#include "cpu_t.h"
#include "devices.h"
#include "instrs.h"

void run(CPU *c) {
  Devices d;
  create_devices(c, &d);

  while (c->running) {
    c->draw_screen = false;

    uint16_t instr = fetch(c);
    Instr_Args args = decode(instr);

    do {
      process_input(c);
      exec(c, &args);
    } while (c->wait_for_key && c->running);

    update_sound(c, &d);

    if (c->draw_screen) {
      buffer_graphics(c, &d);
      draw_graphics(&d);
    }

    if (DEBUG) {
      print_regs(c);
      print_screen(c);
    }
  }

  destroy_devices(&d);
}

uint16_t fetch(CPU *c) {

  uint8_t msb = c->memory[c->pc++];
  uint8_t lsb = c->memory[c->pc++];

  return (msb << 8) | lsb;
}

Instr_Args decode(uint16_t instr) {
  Instr_Args a;

  a.idx = (instr & 0xF000) >> 12;
  a.nnn = instr & 0x0FFF;
  a.kk = instr & 0x00FF;
  a.x = (instr & 0x0F00) >> 8;
  a.y = (instr & 0x00F0) >> 4;
  a.n = instr & 0x000F;

  return a;
}

void exec(CPU *c, Instr_Args *a) { instr_table[a->idx](c, a); }

void reset(CPU *c) {
  memset(c->regs, 0, NUM_REGS * sizeof(uint8_t));
  memset(c->stack, 0, STACK_SIZE * sizeof(uint16_t));
  memset(c->memory, 0, MEM_SIZE * sizeof(uint8_t));
  memset(c->screen, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint8_t));
  memcpy(c->memory, characters, NUM_CHARS);
  memset(c->keys, 0, NUM_KEYS * sizeof(uint8_t));
  c->I = 0;
  c->pc = MEM_START;
  c->sp = 0;
  c->dt = 0;
  c->st = 0;
  c->running = true;
  c->draw_screen = false;
  c->wait_for_key = false;
}

void process_input(CPU *c) {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      c->running = false;
      break;

    case SDL_KEYDOWN:
      for (int i = 0; i < NUM_KEYS; i++) {
        if (e.key.keysym.sym == key_map[i]) {
          c->keys[i] = true;
          break;
        }
      }
      break;

    case SDL_KEYUP:
      for (int i = 0; i < NUM_KEYS; i++) {
        if (e.key.keysym.sym == key_map[i]) {
          c->keys[i] = false;
          break;
        }
      }
      break;

    default:
      break;
    }
  }
}

void load_mem(CPU *c, uint8_t *data, uint16_t loc, size_t n) {
  if (MEM_START + n > MEM_SIZE) {
    fprintf(stderr, "ERROR: data cannot fit into memory\n");
    exit(1);
  }

  memcpy(c->memory + MEM_START + loc, data, n);
}

size_t open_with_size(FILE *file, const char *filename) {
  file = fopen(filename, "rb");

  if (file == NULL) {
    fprintf(stderr, "ERROR: failed to open file %s: %s\n", filename,
            strerror(errno));
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

uint8_t *read_into_buff(FILE *file, size_t size) {
  uint8_t *buff = (uint8_t *)malloc(size);

  if (buff == NULL) {
    fprintf(stderr, "ERROR: Failed to allocate buffer.\n");
    fclose(file);
    exit(1);
  }

  size_t size_read = fread(buff, 1, size, file);
  fclose(file);

  if (size_read != size) {
    fprintf(stderr, "ERROR: failed to read file %s", strerror(errno));
    free(buff);
    exit(1);
  }

  return buff;
}

void print_regs(CPU *c) {
  for (int i = 0; i < NUM_REGS; ++i)
    printf("reg 0x%x: 0x%x\n", i, c->regs[i]);

  printf("I: 0x%x\n", c->I);
}

void print_memory(CPU *c, uint16_t addr) {
  if (addr > MEM_SIZE) {
    fprintf(stderr, "ERROR: address outside of memory range\n");
    exit(1);
  }

  for (int i = 0; i < MEM_PRINT_LEN; i++) {
    if (i % (MEM_PRINT_LEN / MEM_PRINT_LINES) == 0)
      printf("\n0x%-3x | ", i + addr);

    printf("0x%-2x ", c->memory[i + addr]);
  }

  printf("\n\n");
}

void print_screen(CPU *c) {
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      printf("%d ", c->screen[y][x]);
    }
    printf("\n");
  }
}
