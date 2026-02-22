/**************************************************************************/
/*  pch.h                                                                 */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             IW1X-Server-K                              */
/*              https://gitlab.com/kazam0180/iw1x-server-k/               */
/**************************************************************************/
/* See AUTHORS.md                                                         */
/*                                                                        */
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>. */
/**************************************************************************/

#ifndef PCH_H
#define PCH_H

// Linux
#include <unistd.h>       // access
#include <arpa/inet.h>    // sockaddr_in, inet_pton
#include <execinfo.h>     // backtrace
#include <dlfcn.h>        // dlsym
#include <sys/time.h>     // gettimeofday
#include <linux/limits.h> // PATH_MAX
#include <signal.h>       // signal

// C++
#include <array>
#include <cmath>   // fabs, sqrt
#include <cstdarg> // va_start, va_end
#include <cstdio>  // printf, snprintf
#include <cstdint> // uintptr_t
#include <cstring> // strcasecmp, strlen, strcmp, strerror, strncpy...
#include <filesystem>
#include <map>     // make_tuple, get, array
#include <sstream> // ostringstream
#include <string>
#include <vector>

#endif
