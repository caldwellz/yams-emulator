/***************************************************
* CPU FC/address/data bus event handlers           *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "memory.h"
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


/** Dispatches reads to either memory (ROM/RAM) or peripheral space. */
unsigned int m68k_read_memory_8(unsigned int address)
{
	if (address <= YAMS_GetMaxMemAddress())
		return YAMS_ReadMemory8(address);
	else {
		// TODO: read from peripheral space
		printf("Read byte outside memory at $%06X\n", address);
	}

	return 0;
}


/** Dispatches reads to either memory (ROM/RAM) or peripheral space. */
unsigned int m68k_read_memory_16(unsigned int address)
{
	if (address <= YAMS_GetMaxMemAddress())
		return YAMS_ReadMemory16(address);
	else {
		// TODO: read from peripheral space
		printf("Read word outside memory at $%06X\n", address);
	}

    return 0;
}


/** Dispatches reads to either memory (ROM/RAM) or peripheral space. */
unsigned int m68k_read_memory_32(unsigned int address)
{
	if (address <= YAMS_GetMaxMemAddress())
		return YAMS_ReadMemory32(address);
	else {
		// TODO: read from peripheral space
		printf("Read long outside memory at $%06X\n", address);
	}

    return 0;
}


/** Dispatches writes to either memory (ROM/RAM) or peripheral space. */
void m68k_write_memory_8(unsigned int address, unsigned int value)
{
	if (address <= YAMS_GetMaxMemAddress())
		YAMS_WriteMemory8(address, value);
	else {
		// TODO: write to peripheral space
		printf("Ignored write of 0x%02X outside memory at $%06X\n", value, address);
	}
}


/** Dispatches writes to either memory (ROM/RAM) or peripheral space. */
void m68k_write_memory_16(unsigned int address, unsigned int value)
{
	if (address <= YAMS_GetMaxMemAddress())
		YAMS_WriteMemory16(address, value);
	else {
		// TODO: write to peripheral space
		printf("Ignored write of 0x%04X outside memory at $%06X\n", value, address);
	}
}


/** Dispatches writes to either memory (ROM/RAM) or peripheral space. */
void m68k_write_memory_32(unsigned int address, unsigned int value)
{
	if (address <= YAMS_GetMaxMemAddress())
		YAMS_WriteMemory32(address, value);
	else {
		// TODO: write to peripheral space
		printf("Ignored write of 0x%08X outside memory at $%06X\n", value, address);
	}
}
