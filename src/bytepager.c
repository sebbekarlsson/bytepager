#include <bytepager/page.h>
#include <bytepager/bytepager.h>
#include <bytepager/constants.h>
#include <bytepager/macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bytepager_init(Bytepager *buff, BytepagerConfig cfg) {
  if (!buff) return 0;
  if (buff->initialized) return 1;
  buff->initialized = true;
  
  if (cfg.page_capacity_bytes <= 0) BYTEPAGER_WARNING_RETURN(0, stderr, "cfg.page_capacity_bytes <= 0.\n");
  cfg.max_page_traversal = OR(cfg.max_page_traversal, BYTEPAGER_MAX_PAGE_TRAVERSAL_DEFAULT);

  buff->config = cfg;
  return 1;
}

void *bytepager_malloc(Bytepager *buff, int64_t n_bytes) {
  if (!buff || n_bytes <= 0) return 0;
  if (!buff->initialized) BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(0);

  if (!buff->root.initialized) {
    if (!bytepager_page_init(&buff->root, buff->config.page_capacity_bytes)) {
      BYTEPAGER_WARNING_RETURN(0, stderr, "Failed to initialize page.\n");
    }
  }
  
  return bytepager_page_malloc(&buff->root, n_bytes, 0, buff->config.max_page_traversal);
}

const char *bytepager_strdup(Bytepager *buff, const char *strval) {
  if (!buff || !strval || strval[0] == 0) return 0;
  if (!buff->initialized) BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(0);
  int64_t n_bytes = strlen(strval);
  char* new_str = (char*)bytepager_malloc(buff, (n_bytes + 1) * sizeof(char));
  if (!new_str) BYTEPAGER_WARNING_RETURN(0, stderr, "Allocation failure.\n");
  
  memcpy(&new_str[0], &strval[0], n_bytes * sizeof(char));
  return new_str;
}

int bytepager_clear(Bytepager *buff) {
  if (!buff) return 0;
  if (!buff->initialized) BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(0);
  return bytepager_page_clear_all(&buff->root);
}

int bytepager_destroy(Bytepager *buff) {
  if (!buff) return 0;
  if (!buff->initialized) BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(0);
  return bytepager_page_destroy_all(&buff->root);
}

int64_t bytepager_count_pages(Bytepager *buff) {
  if (!buff) return 0;
  if (!buff->initialized || !buff->root.initialized) return 0;

  int64_t count = 1;
  BytepagerPage* page = &buff->root;

  while (page != 0) {
    page = page->next;
    count++;
  }

  return count;
}
