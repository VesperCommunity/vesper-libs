/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined SPHTP_H_INCLUDED
#define SPHTP_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/* only export API functions prefixed with SPHTP_API */
#if defined _WIN32
  #if defined SPHTP_BUILD_API
    /* build dll */
    #define SPHTP_API __declspec(dllexport)
  #else
    /* use dll */
    #define SPHTP_API __declspec(dllimport)
  #endif /* defined SPHTP_BUILD_API*/
#else
  #if __GNUC__ >= 4
    #define SPHTP_API __attribute__((visibility("default")))
  #else
    #define SPHTP_API
  #endif
#endif /* defined _WIN32 */



#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined SPHTP_H_INCLUDED */
