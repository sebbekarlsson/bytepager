#ifndef SCRATCHBUFF_H
#define SCRATCHBUFF_H
#include <scratchbuff/config.h>
#include <scratchbuff/page.h>
#include <stdbool.h>
#include <stdint.h>
typedef struct {
  ScratchBuffPage root;
  ScratchBuffConfig config;
  bool initialized;
} ScratchBuff;

int scratchbuff_init(ScratchBuff *buff, ScratchBuffConfig cfg);

void *scratchbuff_malloc(ScratchBuff *buff, int64_t n_bytes);

const char* scratchbuff_strdup(ScratchBuff *buff, const char* strval);

int scratchbuff_clear(ScratchBuff* buff);

int scratchbuff_destroy(ScratchBuff *buff);

int64_t scratchbuff_count_pages(ScratchBuff* buff);
#endif
