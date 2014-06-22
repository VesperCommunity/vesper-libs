/**
 * \file
 * \authors Max Mertens
 *
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#if !defined VSP_ERROR_H_INCLUDED
#define VSP_ERROR_H_INCLUDED

#include <vesper_util/vsp_util.h>

#if defined __cplusplus
extern "C" {
#endif /* defined __cplusplus */

/** Return current error number. */
VSP_API int vsp_error_num(void);

/** Set current error number. */
VSP_API void vsp_error_set_num(int error_num);

/** Return error string for any error number. \see vsp_error_num() */
VSP_API const char* vsp_error_str(int error_num);

#if defined __cplusplus
}
#endif /* defined __cplusplus */

#endif /* !defined VSP_ERROR_H_INCLUDED */
