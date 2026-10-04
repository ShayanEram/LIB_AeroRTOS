#pragma once

#include "types.h"
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*error_callback_t)(partition_t*, const char* msg, RETURN_CODE_TYPE code);

/**
 * Associates a callback function with a given partition.
 */
void set_partition_error_handler(partition_t *p, error_callback_t cb);

/**
 * If the partition has a registered callback, it’s invoked.
 * Or a diagnostic line is printed to stderr.
 */
void report_error(partition_t *p, const char *msg, RETURN_CODE_TYPE code);

#ifdef __cplusplus
}
#endif