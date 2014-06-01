/**
 * Copyright (c) 2014, Max Mertens. All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "vsp_error.h"

#if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
  /* define "inline" keyword for pre-C99 C standard */
  #define inline
#endif
#include <errno.h>
#include <nanomsg/nn.h>

int vsp_error_num(void)
{
    return nn_errno();
}

void vsp_error_set_num(int error_num)
{
    errno = error_num;
}

const char* vsp_error_str(int error_num)
{
    /* use nanomsg error messages */
    return nn_strerror(error_num);
}
