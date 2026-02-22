/**************************************************************************/
/*  shared.h                                                              */
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

#ifndef SHARED_H
#define SHARED_H

#include "pch.h"

#include "types.h"
#include "functions.h"

extern uintptr_t resume_addr_Jump_Check;
extern uintptr_t resume_addr_Jump_Check_2;

extern customPlayerState_t customPlayerState[MAX_CLIENTS];

__attribute__((naked)) void hook_Jump_Check_Naked();
__attribute__((naked)) void hook_Jump_Check_Naked_2();

xfunction_t Scr_GetCustomFunction(const char** fname, qboolean* fdev);
xmethod_t Scr_GetCustomMethod(const char** fname, qboolean* fdev);

void Scr_CodeCallback_Error(qboolean terminal, qboolean emit, const char* internal_function, char* message);

void free_sqlite_db_stores_and_tasks();

#endif
