#ifndef SCRATCH_BUFF_CONFIG_H
#define SCRATCH_BUFF_CONFIG_H
#include <stdint.h>
typedef struct {
  int64_t page_capacity_bytes;
  int64_t max_page_traversal;
} ScratchBuffConfig;
#endif
