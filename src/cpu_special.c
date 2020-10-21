/***************************************************
* Special CPU event handlers                       *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "config.h"
#include "musashi/m68k.h"

/** Illegal instruction handler */
int m68k_on_illegal_instr(int opcode)
{
    LogError("Tried to process illegal opcode 0x%04X at $%06X\n", opcode, m68k_get_reg(NULL, M68K_REG_PC));
    return 1; // 1 to cancel illegal-instruction exception, 0 to continue it
}


/** Breakpoint instruction handler */
void m68k_on_breakpoint(unsigned int data)
{
    LogDebug("Hit breakpoint at $%06X\n", m68k_get_reg(NULL, M68K_REG_PC));
}


/** RESET instruction handler */
void m68k_on_reset()
{
    SDL_Log("Processor has been reset\n");
}
