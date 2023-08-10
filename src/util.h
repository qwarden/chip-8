#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>

typedef struct {
  uint8_t *data;
  size_t size;
} InstrBuff;

InstrBuff read_file_into_buff(char *filename);

#endif // _UTIL_H_
