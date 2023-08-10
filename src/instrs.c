#include "instrs.h"

void instr_invalid(CPU* c, Instr_Args* a) {
  printf("ERROR: invalid opcode %X at byte %X\nEnding execution...\n", (a->idx << 12) | a->nnn, c->pc-2);
  c->running = false;
}

void instr_00E0(CPU* c) {
  memset(c->screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint8_t));
}

void instr_00EE(CPU* c) {
  c->pc = c->stack[c->sp--];
}

void instr_1nnn(CPU* c, Instr_Args* a) {
  c->pc = a->nnn; 
}

void instr_2nnn(CPU* c, Instr_Args* a) {
  c->stack[++c->sp] = c->pc;
  c->pc = a->nnn;
}

void instr_3xkk(CPU* c, Instr_Args* a) {
  if (c->regs[a->x] == a->kk)
    c->pc += 2;
}

void instr_4xkk(CPU* c, Instr_Args* a) {
  if (c->regs[a->x] != a->kk)
    c->pc += 2;
}

void instr_5xy0(CPU* c, Instr_Args* a) {
  if (c->regs[a->x] == c->regs[a->y])
    c->pc += 2;
}

void instr_6xkk(CPU* c, Instr_Args* a) {
  c->regs[a->x] = a->kk;
}

void instr_7xkk(CPU* c, Instr_Args* a) {
  c->regs[a->x] = c->regs[a->x] + a->kk;
}

void instr_8xy0(CPU* c, Instr_Args* a) {
  c->regs[a->x] = c->regs[a->y];
}

void instr_8xy1(CPU* c, Instr_Args* a) {
  c->regs[a->x] = c->regs[a->x] | c->regs[a->y];
} 

void instr_8xy2(CPU* c, Instr_Args* a) {
  c->regs[a->x] = c->regs[a->x] & c->regs[a->y];
}

void instr_8xy3(CPU* c, Instr_Args* a) {
  c->regs[a->x] = c->regs[a->x] ^ c->regs[a->y];
}

void instr_8xy4(CPU* c, Instr_Args* a) {
  uint16_t res = c->regs[a->x] + c->regs[a->y];

  c->regs[0xF] = res > 0xFF;
  c->regs[a->x] = res & 0xFF;
}

void instr_8xy5(CPU* c, Instr_Args* a) {
  c->regs[0xF] = c->regs[a->x] > c->regs[a->y];
  c->regs[a->x] = c->regs[a->x] - c->regs[a->y];
}

void instr_8xy6(CPU* c, Instr_Args* a) {
  c->regs[0xF] = c->regs[a->x] & 1;
  c->regs[a->x] = c->regs[a->x] >> 1;
}

void instr_8xy7(CPU* c, Instr_Args* a) {
  c->regs[0xF] = c->regs[a->y] > c->regs[a->x];
  c->regs[a->x] = c->regs[a->y] - c->regs[a->x];
}

void instr_8xyE(CPU* c, Instr_Args* a) {
  c->regs[0xF] = c->regs[a->x] & 0x80;
  c->regs[a->x] = c->regs[a->x] << 1;
}

void instr_9xy0(CPU* c, Instr_Args* a) {
  if (c->regs[a->x] != c->regs[a->y])
    c->pc += 2;
}

void instr_Annn(CPU* c, Instr_Args* a) {
  c->I = a->nnn; 
}

void instr_Bnnn(CPU* c, Instr_Args* a) {
  c->pc = a->nnn + c->regs[0];
}

void instr_Cxkk(CPU* c, Instr_Args* a) {
  c->regs[a->x] = (rand() % 0xFF) & a->kk;
}

void instr_Dxyn(CPU* c, Instr_Args* a) {
  uint8_t x_start = c->regs[a->x];
  uint8_t y_start = c->regs[a->y];
  uint8_t byte, screen_y, screen_x, new_pix, old_pix;
  c->regs[0xF] = false;

  for (int y = 0; y < a->n; y++) {
    byte = c->memory[c->I + y];
    
    for (int x = 0; x < 8; x++) {
      screen_y = (y_start + y) % SCREEN_HEIGHT;
      screen_x = (x_start + x) % SCREEN_WIDTH;
      
      new_pix = (byte & (0x80 >> x)) >> (7 - x);
      old_pix = c->screen[screen_y][screen_x];
      
      if (new_pix == 1 && old_pix == 1) {
          c->regs[0xF] = true;
      }

      c->screen[screen_y][screen_x] ^= new_pix;
    }
  }
  
  c->draw_screen = true;
}

void instr_Ex9E(CPU* c, Instr_Args* a) {
  if (c->keys[c->regs[a->x]]) {
    c->pc += 2;
  }
}

void instr_ExA1(CPU* c, Instr_Args* a) {
  if (!c->keys[c->regs[a->x]]) {
    c->pc += 2;
  }
}

void instr_Fx07(CPU* c, Instr_Args* a) {
  c->regs[a->x] = c->dt;
}

void instr_Fx0A(CPU* c, Instr_Args* a) {
  c->wait_for_key = true;
  
  for (int i = 0; i < NUM_KEYS; i++) {
    if (c->keys[i]) {
      c->wait_for_key = false;
      c->regs[a->x] = i;
      return;
    }
  }
}

void instr_Fx15(CPU* c, Instr_Args* a) {
  c->dt = c->regs[a->x];
}

void instr_Fx18(CPU* c, Instr_Args* a) {
  c->st = c->regs[a->x];
}

void instr_Fx1E(CPU* c, Instr_Args* a) {
  c->I += c->regs[a->x];
}

void instr_Fx29(CPU* c, Instr_Args* a) {
  c->I = c->regs[a->x] * 5;
}

void instr_Fx33(CPU* c, Instr_Args* a) {
  c->memory[c->I] = c->regs[a->x / 100];
  c->memory[c->I+1] = (c->regs[a->x / 10]) % 10;
  c->memory[c->I+2] = (c->regs[a->x % 100]) % 10;
}


void instr_Fx55(CPU* c, Instr_Args* a) {
  for (int i = 0; i <= a->x; ++i) {
    c->memory[c->I+i] = c->regs[i];
  }
}

void instr_Fx65(CPU* c, Instr_Args* a) {
  for (int i = 0; i <= a->x; ++i) {
    c->regs[i] = c->memory[c->I+i];
  }
}

void instrs_00xx(CPU* c, Instr_Args* a) {
  switch (a->kk) {
    case (0xE0):
      instr_00E0(c);
      break; 

    case (0xEE):
      instr_00EE(c);
      break;

    default:
      instr_invalid(c, a);
      break;
  }
}

Instr instr_8xxx_table[] = {
  instr_8xy0,
  instr_8xy1,
  instr_8xy2,
  instr_8xy3,
  instr_8xy4,
  instr_8xy5,
  instr_8xy6,
  instr_8xy7,
  instr_invalid,
  instr_invalid,
  instr_invalid,
  instr_invalid,
  instr_invalid,
  instr_invalid,
  instr_8xyE,
  instr_invalid
};

void instrs_8xxx(CPU* c, Instr_Args* a) {
  instr_8xxx_table[a->n](c, a);
}

void instrs_Exxx(CPU* c, Instr_Args* a) {
  switch (a->kk) {
    case (0x9E):
      instr_Ex9E(c, a);
      break; 

    case (0xA1):
      instr_ExA1(c, a);
      break;

    default:
      instr_invalid(c, a);
      break;
  }
}

void instrs_Fxxx(CPU* c, Instr_Args* a) {
  switch (a->kk) {
    case (0x07):
      instr_Fx07(c, a);
      break; 

    case (0x0A):
      instr_Fx0A(c, a);
      break;

    case (0x15):
      instr_Fx15(c, a);
      break;

    case (0x18):
      instr_Fx18(c, a);
      break;

    case (0x1E):
      instr_Fx1E(c, a);
      break;

    case (0x29):
      instr_Fx29(c, a);
      break;

    case (0x33):
      instr_Fx33(c, a);
      break;

    case (0x55):
      instr_Fx55(c, a);
      break;

    case (0x65):
      instr_Fx65(c, a);
      break;

    default:
      instr_invalid(c, a);
      break;
  }
}
