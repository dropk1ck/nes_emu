#ifndef __LOG_H
#define __LOG_H

#include <cstdio>

#define log_error(fmt, args...) \
    fprintf(stderr, "[ERROR] %s(%d): " fmt "\n", __FILE__, __LINE__, ##args);

#define log_warning(fmt, args...) \
    fprintf(stderr, "[WARNING] %s(%d): " fmt "\n", __FILE__, __LINE__, ##args);

#ifdef DEBUG_BUILD
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define log_debug(fmt, args...) \
    do { if (DEBUG) fprintf(stdout, "[DEBUG] %s(%d): " fmt "\n", __FILE__, __LINE__, ##args); \
    } while (0)

#define log_info(fmt, args...) \
    fprintf(stdout, "%s(%d): " fmt "\n", __FILE__, __LINE__, ##args);
#endif
