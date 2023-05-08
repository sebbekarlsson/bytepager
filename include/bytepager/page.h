#ifndef SCRATCH_BUFF_PAGE_H
#define SCRATCH_BUFF_PAGE_H
#include <stdint.h>
#include <stdbool.h>

struct BYTEPAGER_PAGE_STRUCT;

typedef struct BYTEPAGER_PAGE_STRUCT {
  uint8_t* data;
  int64_t capacity;
  int64_t cursor;

  struct BYTEPAGER_PAGE_STRUCT* prev;
  struct BYTEPAGER_PAGE_STRUCT* next;
  
  bool initialized;
} BytepagerPage;

int bytepager_page_init(BytepagerPage *page, int64_t capacity);

int64_t bytepager_page_get_avail(BytepagerPage page);

bool bytepager_page_fits(BytepagerPage page, int64_t n_bytes);

void* bytepager_page_malloc(BytepagerPage* page, int64_t n_bytes, int64_t n_traversal, int64_t max_n_pages_traversal);

int bytepager_page_clear(BytepagerPage *page);

int bytepager_page_clear_all(BytepagerPage *page);

int bytepager_page_destroy(BytepagerPage *page, bool release);

int bytepager_page_destroy_all(BytepagerPage *page);
#endif
