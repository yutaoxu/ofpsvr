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

#include "run.h"

START_TEST(ofpsvr_fatal_test_911)
{
        ofpsvr_fatal(911);
}

END_TEST START_TEST(ofpsvr_fatal_test_mem)
{
        ofpsvr_fatal(-1);
}

END_TEST Suite *ofpsvr_test_errors()
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Error handling");
        tc_core = tcase_create("Core");

        suite_add_tcase(s, tc_core);
        tcase_add_exit_test(tc_core, ofpsvr_fatal_test_911, 911);
        tcase_add_exit_test(tc_core, ofpsvr_fatal_test_mem, -1);

        return s;
}
