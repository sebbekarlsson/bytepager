#include <bytepager/config.h>
#include <bytepager/macros.h>
#include <bytepager/bytepager.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONLY_OUTPUT_FAILS 1

static const char *mock_strings[] = {"hello world", "fruit", "apple", "banana",
                                     "prepare for unforseen consequences"};

#define NUM_MALLOCS_A 256
#define NUM_MALLOCS_B 512


#define SB_TEST_BEGIN() fprintf(stdout, "[Test]: %s\n", __func__); 


#define SB_ASSERT(expr)                                                        \
  {                                                                            \
    if (!(expr)) {                                                             \
      BYTEPAGER_WARNING(stderr, "[Fail]: `%s`\n", #expr);                    \
      exit(0);                                                                 \
    } else if (!ONLY_OUTPUT_FAILS) {					       \
      fprintf(stdout, "[OK]: %s\n", #expr);                                    \
    }                                                                          \
  }


static void test_allocate_clear_allocate_destroy() {
  SB_TEST_BEGIN();
  
  size_t num_mock_strings = sizeof(mock_strings) / sizeof(mock_strings[0]);

  Bytepager buff = {0};
  bytepager_init(&buff, (BytepagerConfig){.max_page_traversal = 32,
                                              .page_capacity_bytes = 256});

  for (int i = 0; i < NUM_MALLOCS_A; i++) {
    const char *expected = mock_strings[i % num_mock_strings];
    const char *copied = bytepager_strdup(&buff, expected);
    SB_ASSERT(copied != 0);
    SB_ASSERT(strcmp(copied, expected) == 0);
  }

  bytepager_clear(&buff);

  for (int i = 0; i < NUM_MALLOCS_B; i++) {
    const char *expected = mock_strings[i % num_mock_strings];
    const char *copied = bytepager_strdup(&buff, expected);
    SB_ASSERT(copied != 0);
    SB_ASSERT(strcmp(copied, expected) == 0);
  }

  int64_t n_pages = bytepager_count_pages(&buff);

  SB_ASSERT(n_pages > 0);

  bytepager_destroy(&buff);

  n_pages = bytepager_count_pages(&buff);

  SB_ASSERT(n_pages == 0);
}

static void test_allocate_after_destroy() {
  SB_TEST_BEGIN();
  
  size_t num_mock_strings = sizeof(mock_strings) / sizeof(mock_strings[0]);

  Bytepager buff = {0};
  bytepager_init(&buff, (BytepagerConfig){.max_page_traversal = 32,
                                              .page_capacity_bytes = 256});

  for (int i = 0; i < NUM_MALLOCS_A; i++) {
    const char *expected = mock_strings[i % num_mock_strings];
    const char *copied = bytepager_strdup(&buff, expected);
    SB_ASSERT(copied != 0);
    SB_ASSERT(strcmp(copied, expected) == 0);
  }

  bytepager_destroy(&buff);

  for (int i = 0; i < NUM_MALLOCS_B; i++) {
    const char *expected = mock_strings[i % num_mock_strings];
    const char *copied = bytepager_strdup(&buff, expected);
    SB_ASSERT(copied != 0);
    SB_ASSERT(strcmp(copied, expected) == 0);
  }

  int64_t n_pages = bytepager_count_pages(&buff);

  SB_ASSERT(n_pages > 0);

  bytepager_destroy(&buff);

  n_pages = bytepager_count_pages(&buff);

  SB_ASSERT(n_pages == 0);
}

int main(int argc, char *argv[]) {
  test_allocate_clear_allocate_destroy();
  test_allocate_after_destroy();
  return 0;
}
