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
