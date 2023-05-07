#include <scratchbuff/page.h>
#include <scratchbuff/scratchbuff.h>
#include <scratchbuff/constants.h>
#include <scratchbuff/macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scratchbuff_init(ScratchBuff *buff, ScratchBuffConfig cfg) {
  if (!buff) return 0;
  if (buff->initialized) return 1;
  buff->initialized = true;
  
  if (cfg.page_capacity_bytes <= 0) SCRATCHBUFF_WARNING_RETURN(0, stderr, "cfg.page_capacity_bytes <= 0.\n");
  cfg.max_page_traversal = OR(cfg.max_page_traversal, SCRATCHBUFF_MAX_PAGE_TRAVERSAL_DEFAULT);

  buff->config = cfg;
  return 1;
}

void *scratchbuff_malloc(ScratchBuff *buff, int64_t n_bytes) {
  if (!buff || n_bytes <= 0) return 0;
  if (!buff->initialized) SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(0);

  if (!buff->root.initialized) {
    if (!scratchbuff_page_init(&buff->root, buff->config.page_capacity_bytes)) {
      SCRATCHBUFF_WARNING_RETURN(0, stderr, "Failed to initialize page.\n");
    }
  }
  
  return scratchbuff_page_malloc(&buff->root, n_bytes, 0, buff->config.max_page_traversal);
}

const char *scratchbuff_strdup(ScratchBuff *buff, const char *strval) {
  if (!buff || !strval || strval[0] == 0) return 0;
  if (!buff->initialized) SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(0);
  int64_t n_bytes = strlen(strval);
  char* new_str = (char*)scratchbuff_malloc(buff, (n_bytes + 1) * sizeof(char));
  if (!new_str) SCRATCHBUFF_WARNING_RETURN(0, stderr, "Allocation failure.\n");
  
  memcpy(&new_str[0], &strval[0], n_bytes * sizeof(char));
  return new_str;
}

int scratchbuff_clear(ScratchBuff *buff) {
  if (!buff) return 0;
  if (!buff->initialized) SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(0);
  return scratchbuff_page_clear_all(&buff->root);
}

int scratchbuff_destroy(ScratchBuff *buff) {
  if (!buff) return 0;
  if (!buff->initialized) SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(0);
  return scratchbuff_page_destroy_all(&buff->root);
}

int64_t scratchbuff_count_pages(ScratchBuff *buff) {
  if (!buff) return 0;
  if (!buff->initialized || !buff->root.initialized) return 0;

  int64_t count = 1;
  ScratchBuffPage* page = &buff->root;

  while (page != 0) {
    page = page->next;
    count++;
  }

  return count;
}
