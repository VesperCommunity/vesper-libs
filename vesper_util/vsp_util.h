/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_UTIL_H_INCLUDED
#define VSP_UTIL_H_INCLUDED

/* only export API functions prefixed with VESPER_API */
#if defined _WIN32
  #if defined VESPER_BUILD_API
    /* build dll */
    #define VESPER_API __declspec(dllexport)
  #else
    /* use dll */
    #define VESPER_API __declspec(dllimport)
  #endif /* defined VESPER_BUILD_API*/
#else
  #if __GNUC__ >= 4
    #define VESPER_API __attribute__((visibility("default")))
  #else
    #define VESPER_API
  #endif
#endif /* defined _WIN32 */

#endif /* !defined VSP_UTIL_H_INCLUDED */
