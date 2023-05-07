#include <scratchbuff/macros.h>
#include <scratchbuff/page.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scratchbuff_page_init(ScratchBuffPage *page, int64_t capacity) {
  if (!page)
    return 0;
  if (page->initialized)
    return 1;
  if (capacity <= 0)
    SCRATCHBUFF_WARNING_RETURN(0, stderr, "capacity <= 0.\n");
  page->initialized = true;

  page->capacity = capacity;
  page->cursor = 0;

  if (!page->data) {
    page->data = (uint8_t *)calloc(page->capacity, sizeof(uint8_t));
  }
  
  page->next = 0;
  page->prev = 0;

  if (!page->data) {
    SCRATCHBUFF_WARNING(stderr, "Allocation failure.\n");
    page->initialized = false;
    page->data = 0;
    return 0;
  }

  return 1;
}

int64_t scratchbuff_page_get_avail(ScratchBuffPage page) {
  if (page.capacity <= 0)
    return 0;
  if (!page.data)
    return 0;
  int64_t avail = (page.capacity - page.cursor);
  return MAX(0, avail);
}

bool scratchbuff_page_fits(ScratchBuffPage page, int64_t n_bytes) {
  if (!page.data)
    return false;
  int64_t avail = scratchbuff_page_get_avail(page);
  return avail >= n_bytes;
}

void *scratchbuff_page_malloc(ScratchBuffPage *page, int64_t n_bytes,
			      int64_t n_traversal,
			      int64_t max_n_pages_traversal) {
  if (n_traversal >= max_n_pages_traversal)
    SCRATCHBUFF_WARNING_RETURN(0, stderr,
			       "max page traversal limit reached.\n");
  if (!page)
    return 0;
  if (!page->initialized)
    SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(0);
  if (n_bytes <= 0)
    return 0;
  if (n_bytes > page->capacity)
    SCRATCHBUFF_WARNING_RETURN(0, stderr,
			       "allocation overflows page capacity.\n");

  if (page->data == 0) {
    SCRATCHBUFF_WARNING_RETURN(0, stderr, "did not expect page data to be null.\n");
  }
  
  // int64_t avail = scratchbuff_page_get_avail(*page);
  // printf("wants: %ld, avail: %ld\n", n_bytes, avail);
  
  if (scratchbuff_page_fits(*page, n_bytes)) {
    uint8_t *ptr = &page->data[page->cursor];
    memset(&ptr[0], 0, n_bytes);
    page->cursor += n_bytes;
    
    return (void *)ptr;
  }

  if (!page->next) {
    page->next = NEW(ScratchBuffPage);
    if (!page->next) {
      SCRATCHBUFF_WARNING_RETURN(0, stderr, "allocation failure.\n");
    }
  }
  
  if (!page->next->initialized) {
    scratchbuff_page_init(page->next, page->capacity);
  }

  if (!page->next->prev) {
    page->next->prev = page;
  }
  
  return scratchbuff_page_malloc(page->next, n_bytes, n_traversal + 1,
				 max_n_pages_traversal);
}

int scratchbuff_page_clear(ScratchBuffPage *page) {
  if (!page)
    return 0;
  //if (!page->initialized)
  //  SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(0);

  page->cursor = 0;

  return 1;
}

int scratchbuff_page_clear_all(ScratchBuffPage *page) {
  if (!page) return 0;
  scratchbuff_page_clear(page);

  if (page->next) {
    return scratchbuff_page_clear_all(page->next);
  }

  return 1;
}

int scratchbuff_page_destroy(ScratchBuffPage *page, bool release) {
  if (!page) return 0;
  scratchbuff_page_clear(page);

  if (page->data != 0) {
    free(page->data);
  }

  page->data = 0;
  page->initialized = false;
  
  if (release) {
    free(page);
    page = 0;
  }


  return 1;
}

int scratchbuff_page_destroy_all(ScratchBuffPage *page) {
  ScratchBuffPage* next = page;

  int64_t i = 0;
  while (next != 0) { 
    ScratchBuffPage* sibling = next->next;
    next->next = 0;
    scratchbuff_page_destroy(next, i > 0);
    next = sibling;
    i++;
  }

  return 1;
}
