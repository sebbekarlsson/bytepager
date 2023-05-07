#ifndef SCRATCH_BUFF_PAGE_H
#define SCRATCH_BUFF_PAGE_H
#include <stdint.h>
#include <stdbool.h>

struct SCRATCHBUFF_PAGE_STRUCT;

typedef struct SCRATCHBUFF_PAGE_STRUCT {
  uint8_t* data;
  int64_t capacity;
  int64_t cursor;

  struct SCRATCHBUFF_PAGE_STRUCT* prev;
  struct SCRATCHBUFF_PAGE_STRUCT* next;
  
  bool initialized;
} ScratchBuffPage;

int scratchbuff_page_init(ScratchBuffPage *page, int64_t capacity);

int64_t scratchbuff_page_get_avail(ScratchBuffPage page);

bool scratchbuff_page_fits(ScratchBuffPage page, int64_t n_bytes);

void* scratchbuff_page_malloc(ScratchBuffPage* page, int64_t n_bytes, int64_t n_traversal, int64_t max_n_pages_traversal);

int scratchbuff_page_clear(ScratchBuffPage *page);

int scratchbuff_page_clear_all(ScratchBuffPage *page);

int scratchbuff_page_destroy(ScratchBuffPage *page, bool release);

int scratchbuff_page_destroy_all(ScratchBuffPage *page);
#endif
