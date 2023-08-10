#include "cpu.h"

int main(int argc, char **argv) {
  CPU cpu;

  if (argc != 2) {
    printf("Usage: chip-8 [filename]\n");
    return 1;
  }

  char *filename = argv[1];
  uint8_t instrs[MEM_SIZE - MEM_START];
  size_t size = read_file_into_buff(filename, instrs);

  reset(&cpu);
  load_mem(&cpu, instrs, 0, size / sizeof(uint8_t));
  run(&cpu);

  return 0;
}
