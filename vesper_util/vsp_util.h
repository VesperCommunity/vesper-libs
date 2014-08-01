/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_UTIL_H_INCLUDED
#define VSP_UTIL_H_INCLUDED

#include <assert.h>
#include <errno.h>

#if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
  /* define "inline" keyword for pre-C99 C standard */
  #define inline
#endif

/** Try to allocate memory, check result and react in case of failure. */
#define VSP_ALLOC(ptr, type, failure_action) do { \
    /* allocate memory */ \
    ptr = malloc(sizeof(type)); \
    if (ptr == NULL) { \
        /* allocation failed */ \
        vsp_error_set_num(ENOMEM); \
        failure_action; \
    } \
} while (0)

/** Free memory and set `ptr` to `NULL`. */
#define VSP_FREE(ptr) do { \
    /* free memory */ \
    free(ptr); \
    ptr = NULL; \
} while (0)

/** Assert condition, set error number and react in case of failure. */
#if !defined(NDEBUG)
  #define VSP_ASSERT(condition, failure_action) assert(condition)
#else
  #define VSP_ASSERT(condition, failure_action) do { \
      /* check condition */ \
      if (!(condition)) { \
          /* condition failed */ \
          failure_action; \
      } \
  } while (0)
#endif /* !defined(NDEBUG) */

#endif /* !defined VSP_UTIL_H_INCLUDED */
