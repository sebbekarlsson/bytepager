#ifndef SCRATCHBUFF_MACROS_H
#define SCRATCHBUFF_MACROS_H

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

#define SCRATCHBUFF_CLI_RED "\x1B[31m"
#define SCRATCHBUFF_CLI_GREEN "\x1B[32m"
#define SCRATCHBUFF_CLI_YELLLOW "\x1B[33m"
#define SCRATCHBUFF_CLI_BLUE "\x1B[34m"
#define SCRATCHBUFF_CLI_MAGENTA "\x1B[35m"
#define SCRATCHBUFF_CLI_CYAN "\x1B[36m"
#define SCRATCHBUFF_CLI_WHITE "\x1B[37m"
#define SCRATCHBUFF_CLI_RESET "\x1B[0m"


#define SCRATCHBUFF_WARN_MSG() printf(SCRATCHBUFF_CLI_RED "(SCRATCHBUFF)(Warning)(%s): \n" SCRATCHBUFF_CLI_RESET, __func__)

#define SCRATCHBUFF_WARNING(...)                                                    \
  {                                                                          \
    SCRATCHBUFF_WARN_MSG();						\
    fprintf(__VA_ARGS__);                                                    \
  }
#define SCRATCHBUFF_WARNING_RETURN(ret, ...)                                        \
  {                                                                          \
    printf("\n****\n");                                                      \
    SCRATCHBUFF_WARN_MSG();						\
    fprintf(__VA_ARGS__);                                                    \
    printf("\n****\n");                                                      \
    return ret;                                                              \
  }


#define SCRATCHBUFF_WARNING_RETURN_NOT_INITIALIZED(ret)                                        \
  {                                                                          \
    printf("\n****\n");                                                      \
    printf(SCRATCHBUFF_CLI_RED "(SCRATCHBUFF)(Not initialized)(%s): \n" SCRATCHBUFF_CLI_RESET, __func__); \
    printf("\n****\n");                                                      \
    return ret;                                                              \
  }


#define SCRATCHBUFF_GENERATE_ENUM(ENUM) ENUM,
#define SCRATCHBUFF_GENERATE_STRING(STRING) #STRING,

#endif
