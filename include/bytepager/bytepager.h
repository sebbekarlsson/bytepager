#ifndef BYTEPAGER_H
#define BYTEPAGER_H
#include <bytepager/config.h>
#include <bytepager/page.h>
#include <stdbool.h>
#include <stdint.h>
typedef struct {
  BytepagerPage root;
  BytepagerConfig config;
  bool initialized;
} Bytepager;

int bytepager_init(Bytepager *buff, BytepagerConfig cfg);

void *bytepager_malloc(Bytepager *buff, int64_t n_bytes);

const char* bytepager_strdup(Bytepager *buff, const char* strval);

int bytepager_clear(Bytepager* buff);

int bytepager_destroy(Bytepager *buff);

int64_t bytepager_count_pages(Bytepager* buff);
#endif
