/***************************************************
* CPU FC/address/data bus event handlers           *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "musashi/m68k.h"
#include <stdio.h>

// CPU function codes (address spaces) table
const char* functionCodes[8] = {
    "UNDEFINED"          // 000
  , "USER DATA"          // 001
  , "USER PROGRAM"       // 010
  , "UNDEFINED"          // 011
  , "UNDEFINED"          // 100
  , "SUPERVISOR DATA"    // 101
  , "SUPERVISOR PROGRAM" // 110
  , "CPU SPACE"          // 111
};


/** Function Code handler, set on every memory access */
void m68k_set_fc(unsigned int new_fc)
{
    static unsigned int fc = 0;
    static unsigned int fc_count = 0;

    if (new_fc != fc) {
        printf("Changed function code to 0x%01X (%s); previously kept for %i accesses\n", new_fc, functionCodes[new_fc], fc_count);
        fc = new_fc;
        fc_count = 0;
    }
    else
        ++fc_count;
}


/** Dummy function that just returns 0 */
unsigned int m68k_read_memory_8(unsigned int address)
{
    printf("Reading byte from $%06X\n", address);
    return 0x00;
}


/** Dummy function that just returns NOP */
unsigned int m68k_read_memory_16(unsigned int address)
{
    printf("Reading word from $%06X\n", address);

    // No-op instruction
    return 0x4E71;
}


/** Dummy function that just returns a main init address */
unsigned int m68k_read_memory_32(unsigned int address)
{
    printf("Reading long from $%06X\n", address);
    return 0x000000C0;
}


/** Dummy function that just prints to the console */
void m68k_write_memory_8(unsigned int address, unsigned int value)
{
    printf("Writing 0x%02X to $%06X\n", value, address);
}


/** Dummy function that just prints to the console */
void m68k_write_memory_16(unsigned int address, unsigned int value)
{
    printf("Writing 0x%04X to $%06X\n", value, address);
}


/** Dummy function that just prints to the console */
void m68k_write_memory_32(unsigned int address, unsigned int value)
{
    printf("Writing 0x%08X to $%06X\n", value, address);
}
