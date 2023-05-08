#include <bytepager/macros.h>
#include <bytepager/page.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bytepager_page_init(BytepagerPage *page, int64_t capacity) {
  if (!page)
    return 0;
  if (page->initialized)
    return 1;
  if (capacity <= 0)
    BYTEPAGER_WARNING_RETURN(0, stderr, "capacity <= 0.\n");
  page->initialized = true;

  page->capacity = capacity;
  page->cursor = 0;

  if (!page->data) {
    page->data = (uint8_t *)calloc(page->capacity, sizeof(uint8_t));
  }
  
  page->next = 0;
  page->prev = 0;

  if (!page->data) {
    BYTEPAGER_WARNING(stderr, "Allocation failure.\n");
    page->initialized = false;
    page->data = 0;
    return 0;
  }

  return 1;
}

int64_t bytepager_page_get_avail(BytepagerPage page) {
  if (page.capacity <= 0)
    return 0;
  if (!page.data)
    return 0;
  int64_t avail = (page.capacity - page.cursor);
  return MAX(0, avail);
}

bool bytepager_page_fits(BytepagerPage page, int64_t n_bytes) {
  if (!page.data)
    return false;
  int64_t avail = bytepager_page_get_avail(page);
  return avail >= n_bytes;
}

void *bytepager_page_malloc(BytepagerPage *page, int64_t n_bytes,
			      int64_t n_traversal,
			      int64_t max_n_pages_traversal) {
  if (n_traversal >= max_n_pages_traversal)
    BYTEPAGER_WARNING_RETURN(0, stderr,
			       "max page traversal limit reached.\n");
  if (!page)
    return 0;
  if (!page->initialized)
    BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(0);
  if (n_bytes <= 0)
    return 0;
  if (n_bytes > page->capacity)
    BYTEPAGER_WARNING_RETURN(0, stderr,
			       "allocation overflows page capacity.\n");

  if (page->data == 0) {
    BYTEPAGER_WARNING_RETURN(0, stderr, "did not expect page data to be null.\n");
  }
  
  // int64_t avail = bytepager_page_get_avail(*page);
  // printf("wants: %ld, avail: %ld\n", n_bytes, avail);
  
  if (bytepager_page_fits(*page, n_bytes)) {
    uint8_t *ptr = &page->data[page->cursor];
    memset(&ptr[0], 0, n_bytes);
    page->cursor += n_bytes;
    
    return (void *)ptr;
  }

  if (!page->next) {
    page->next = NEW(BytepagerPage);
    if (!page->next) {
      BYTEPAGER_WARNING_RETURN(0, stderr, "allocation failure.\n");
    }
  }
  
  if (!page->next->initialized) {
    bytepager_page_init(page->next, page->capacity);
  }

  if (!page->next->prev) {
    page->next->prev = page;
  }
  
  return bytepager_page_malloc(page->next, n_bytes, n_traversal + 1,
				 max_n_pages_traversal);
}

int bytepager_page_clear(BytepagerPage *page) {
  if (!page)
    return 0;
  //if (!page->initialized)
  //  BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(0);

  page->cursor = 0;

  return 1;
}

int bytepager_page_clear_all(BytepagerPage *page) {
  if (!page) return 0;
  bytepager_page_clear(page);

  if (page->next) {
    return bytepager_page_clear_all(page->next);
  }

  return 1;
}

int bytepager_page_destroy(BytepagerPage *page, bool release) {
  if (!page) return 0;
  bytepager_page_clear(page);

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

int bytepager_page_destroy_all(BytepagerPage *page) {
  BytepagerPage* next = page;

  int64_t i = 0;
  while (next != 0) { 
    BytepagerPage* sibling = next->next;
    next->next = 0;
    bytepager_page_destroy(next, i > 0);
    next = sibling;
    i++;
  }

  return 1;
}
