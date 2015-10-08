/*
 * OF P.S.V.R
 * Copyright (C) 2009-2015  P.S.V.R
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
