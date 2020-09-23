/***************************************************
* Memory functions (i.e. ROM/RAM, not peripherals) *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "memory.h"

/** Must be called first to allocate the memory map. */
int YAMS_InitMemoryMap(unsigned int addrBits)
{
    
}


/** Load a ROM image from a file and mark its space read-only internally. */
int YAMS_LoadROMImage(const char* filename, unsigned int base)
{
    
}


/** Get the highest address at which ROM or RAM may be found. */
unsigned int YAMS_GetMaxMemAddress()
{
    
}


/** Read an 8-bit value from memory. */
unsigned int YAMS_ReadMemory8(unsigned int address)
{
    
}


/** Read a 16-bit value from memory. */
unsigned int YAMS_ReadMemory16(unsigned int address)
{
    
}


/** Read a 32-bit value from memory. */
unsigned int YAMS_ReadMemory32(unsigned int address)
{
    
}


/** Write an 8-bit value to memory, or print an error if in ROM space. */
void YAMS_WriteMemory8(unsigned int address, unsigned int value)
{
    
}


/** Write a 16-bit value to memory, or print an error if in ROM space. */
void YAMS_WriteMemory16(unsigned int address, unsigned int value)
{
    
}


/** Write a 32-bit value to memory, or print an error if in ROM space. */
void YAMS_WriteMemory32(unsigned int address, unsigned int value)
{
    
}
