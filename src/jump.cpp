/**************************************************************************/
/*  jump.cpp                                                              */
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

/*
Linux inline asm notes

- __attribute__ ((naked)):  no prologue/epilogue
- extern "C":               no name mangling
- asm volatile:             no optimizaion/reordering

- pushal:   save general-purpose registers
- popal:    restore general-purpose registers

Can add a suffix to an instruction to indicate the size/type of the operand:
- b: byte
- w: word
- l: long

asm volatile (
    // Instructions
    : // Output operands
    : // Input operands (m = memory, r = register)
    : // Clobber list
);
*/

#include "shared.h"

// Custom cvars
extern cvar_t* jump_height;

// Game lib objects
extern pmove_t** pm;

float getJumpHeight()
{
    int clientNum = (*pm)->ps->clientNum;

    if (customPlayerState[clientNum].overrideJumpHeight || customPlayerState[clientNum].overrideJumpHeight_air)
        return customPlayerState[clientNum].jumpHeight;
    return jump_height->value;
}

//// Override jump height
// Update ps->velocity[2]
__attribute__((naked)) void hook_Jump_Check_Naked()
{
    asm volatile("push %%eax\n"
                 "call setJumpHeight\n"
                 "pop %%eax\n"
                 "jmp *%0\n"
                 :
                 : "r"(resume_addr_Jump_Check)
                 :);
}
extern "C" void setJumpHeight()
{
    float height = getJumpHeight() * 2;
    asm volatile("fmuls %0\n" : : "m"(height) :);
}

// Update ps->jumpTime
/*
Had to:
- start at the mov instruction
- add eax to the clobber list
not to prevent landing faster when jumping on objects.
*/
__attribute__((naked)) void hook_Jump_Check_Naked_2()
{
    asm volatile("mov (%%ebx), %%eax\n"
                 "flds 0x1C(%%eax)\n"

                 "pushal\n"
                 "call setJumpHeight_2\n"
                 "popal\n"

                 "jmp *%0\n"
                 :
                 : "r"(resume_addr_Jump_Check_2)
                 : "%eax");
}
extern "C" void setJumpHeight_2()
{
    float height = getJumpHeight();
    asm volatile("fadds %0\n" : : "m"(height) :);
}
////
