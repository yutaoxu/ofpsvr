/*
 * OF P.S.V.R
 * Copyright (c) 2015 P.S.V.R
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ofpsvr.h"

static void ofpsvr__unexplained_fatal(int error_number)
{
        fprintf(stderr, "[OFPSVR ERROR] ");
        fprintf(stderr, "Unexplained fatal error %d.\n", error_number);
}

static void ofpsvr__explain_error(int error_number)
{
        assert(error_number < 0);
        switch (error_number) {
#define XX(code, msg)                                                         \
        case code:                                                            \
                fprintf(stderr, "[OFPSVR ERROR] %s;\n", msg);                 \
                break;

                OFPSVR_ERRNO_MAP(XX)
#undef XX
        default:
                ofpsvr__unexplained_fatal(error_number);
        }
}

void ofpsvr_fatal(int error_number)
{
        ofpsvr__explain_error(error_number);
        exit(error_number);
}

void ofpsvr_error(int error_number)
{
        ofpsvr__explain_error(error_number);
}

void ofpsvr_location_stderr(const char *file, int line)
{
        fprintf(stderr, "[OFPSVR DEBUG] ");
        fprintf(stderr, "On line %d of file %s;\n", line, file);
}
