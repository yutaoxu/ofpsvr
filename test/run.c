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

int main()
{
        int n;
        SRunner *sr;

        sr = srunner_create(NULL);
        srunner_set_fork_status(sr, CK_FORK);

        srunner_add_suite(sr, ofpsvr_test_errors());

        srunner_run_all(sr, CK_VERBOSE);
        n = srunner_ntests_failed(sr);
        srunner_free(sr);

        return (n == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
