#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

InstrBuff read_file_into_buff(char *filename) {
  FILE *file = fopen(filename, "rb");

  if (file == NULL) {
    fprintf(stderr, "ERROR: failed to open file %s: %s\n", filename,
            strerror(errno));
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

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

  InstrBuff result = {buff, size};

  return result;
}
