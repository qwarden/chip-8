#include "cpu.h"
#include "util.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: chip-8 [filename]\n");
    return 1;
  }

  char *filename = argv[1];
  InstrBuff instrs = read_file_into_buff(filename);

  CPU cpu;

  reset(&cpu);
  load_mem(&cpu, instrs.data, 0, instrs.size / sizeof(uint8_t));
  free(instrs.data);

  run(&cpu);

  return 0;
}
