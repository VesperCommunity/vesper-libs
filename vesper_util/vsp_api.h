/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_API_H_INCLUDED
#define VSP_API_H_INCLUDED

/**
 * Shared library export marker.
 * Defined to be `__declspec(dllexport)` or `__declspec(dllimport)` on Windows
 * and `__attribute__((visibility("default")))` on GNU platforms.
 */
#if defined _WIN32
  #if defined VSP_BUILD_API
    /* build dll */
    #define VSP_API __declspec(dllexport)
  #else
    /* use dll */
    #define VSP_API __declspec(dllimport)
  #endif /* defined VSP_BUILD_API*/
#else
  #if __GNUC__ >= 4
    #define VSP_API __attribute__((visibility("default")))
  #else
    #define VSP_API
  #endif
#endif /* defined _WIN32 */

#endif /* !defined VSP_API_H_INCLUDED */
