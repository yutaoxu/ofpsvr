#!/bin/sh

# P.S.V.R 的软件实验室
# 版权所有 (C) 2009-2015  P.S.V.R
# 
# 本程序为自由软件；您可依据自由软件基金会所发表的 GNU 通用公共授权条款，对本程序进行
# 再发布和/或修改；无论您依据的是本授权的第三版，还是（您可选的）任一日后发行的版本。
# 
# 本程序是基于实用的目的而加以发布的，然而并不承担任何担保责任；亦不对适售性或特定目的
# 的适用性做出默示性担保。详情请参照 GNU 通用公共授权。
# 
# 您应该已经收到了附随于本程序的 GNU 通用公共授权的副本；如果没有，请参照
# <http://www.gnu.org/licenses/>.
# 
# OF P.S.V.R
# Copyright (C) 2009-2015  P.S.V.R
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cd `dirname "$0"`

if [ "$LIBTOOLIZE" = "" ] && [ "`uname`" = "Darwin" ]; then
  LIBTOOLIZE=glibtoolize
fi

ACLOCAL=${ACLOCAL:-aclocal}
AUTOCONF=${AUTOCONF:-autoconf}
AUTOHEADER=${AUTOHEADER:-autoheader}
AUTOMAKE=${AUTOMAKE:-automake}
LIBTOOLIZE=${LIBTOOLIZE:-libtoolize}

set -ex
"$LIBTOOLIZE"
"$ACLOCAL" -I m4
"$AUTOCONF"
"$AUTOHEADER"
"$AUTOMAKE" --add-missing --copy
