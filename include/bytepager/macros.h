#ifndef BYTEPAGER_MACROS_H
#define BYTEPAGER_MACROS_H

#ifndef NEW
#define NEW(T) ((T *)(calloc(1, sizeof(T))))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef OR
#define OR(a, b) ((a) ? (a) : (b))
#endif

#define BYTEPAGER_CLI_RED "\x1B[31m"
#define BYTEPAGER_CLI_GREEN "\x1B[32m"
#define BYTEPAGER_CLI_YELLLOW "\x1B[33m"
#define BYTEPAGER_CLI_BLUE "\x1B[34m"
#define BYTEPAGER_CLI_MAGENTA "\x1B[35m"
#define BYTEPAGER_CLI_CYAN "\x1B[36m"
#define BYTEPAGER_CLI_WHITE "\x1B[37m"
#define BYTEPAGER_CLI_RESET "\x1B[0m"


#define BYTEPAGER_WARN_MSG() printf(BYTEPAGER_CLI_RED "(BYTEPAGER)(Warning)(%s): \n" BYTEPAGER_CLI_RESET, __func__)

#define BYTEPAGER_WARNING(...)                                                    \
  {                                                                          \
    BYTEPAGER_WARN_MSG();						\
    fprintf(__VA_ARGS__);                                                    \
  }
#define BYTEPAGER_WARNING_RETURN(ret, ...)                                        \
  {                                                                          \
    printf("\n****\n");                                                      \
    BYTEPAGER_WARN_MSG();						\
    fprintf(__VA_ARGS__);                                                    \
    printf("\n****\n");                                                      \
    return ret;                                                              \
  }


#define BYTEPAGER_WARNING_RETURN_NOT_INITIALIZED(ret)                                        \
  {                                                                          \
    printf("\n****\n");                                                      \
    printf(BYTEPAGER_CLI_RED "(BYTEPAGER)(Not initialized)(%s): \n" BYTEPAGER_CLI_RESET, __func__); \
    printf("\n****\n");                                                      \
    return ret;                                                              \
  }


#define BYTEPAGER_GENERATE_ENUM(ENUM) ENUM,
#define BYTEPAGER_GENERATE_STRING(STRING) #STRING,

#endif
