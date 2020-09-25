/***************************************************
* Memory functions (i.e. ROM/RAM, not peripherals) *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "memory.h"
#include <SDL2/SDL_endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// We're currently assuming the system only has a 24-bit address space
static unsigned int memMax = 0, lowROMBound = 0x1000001, highROMBound = 0;
static char* memory = NULL;

/** Must be called first to allocate the memory map. */
int YAMS_InitMemoryMap(unsigned int addrBits)
{
    if (addrBits > 24)
        printf("Warning: Initializing an unusually large (> 24-bit) memory map.\n");

    unsigned int memBytes = 1 << addrBits;
    memory = malloc(memBytes);
    if (memory) {
        memset(memory, 0, memBytes);
        memMax = memBytes - 1;
        return 1;
    }

    return 0;
}


/** Destroy and free the memory map. */
void YAMS_FreeMemoryMap()
{
    if (memory) {
        free(memory);
        memory = NULL;
    }
}


/** Load a ROM image from a file and mark its space read-only internally. */
int YAMS_LoadROMImage(const char* filename, unsigned int base)
{
    // Open the ROM file
    FILE* inFile = fopen(filename, "rb");
    if (inFile == NULL) {
        printf("Unable to open file '%s'\n", filename);
        return 0;
    }

    // Read the ROM file
    unsigned int bytesRead = 0, addr = base;
    char c = fgetc(inFile);
    while (c != EOF) {
        if (addr > memMax) {
            printf("ROM at base $%06X exceeded memory bounds after loading %i bytes.\n", base, bytesRead);
            return 0;
        }
        memory[addr++] = c;
        bytesRead++;
        c = fgetc(inFile);
    }
    fclose(inFile);

    // Update the read-only bounds
    if (base < lowROMBound)
        lowROMBound = base;
    if (--addr > highROMBound)
        highROMBound = addr;

    printf("Loaded %i-byte ROM at base $%06X.\nRead-only bounds are now $%06X to $%06X.\n", bytesRead, base, lowROMBound, highROMBound);
    return 1;
}


/** Get the highest address at which ROM or RAM may be found. */
unsigned int YAMS_GetMaxMemAddress()
{
    return memMax;
}


/** Read an 8-bit value from memory. */
unsigned int YAMS_ReadMemory8(unsigned int address)
{
    if (memory)
        return memory[address];

    return 0;
}


/** Read a 16-bit value from memory. */
unsigned int YAMS_ReadMemory16(unsigned int address)
{
    if (memory) {
        // Convert data from big-endian, and absolute address to size-relative
        Uint16* memPtr = (Uint16*) memory;
        unsigned int value = SDL_SwapBE16(memPtr[address / 2]);
        return value;
    }

    return 0;
}


/** Read a 32-bit value from memory. */
unsigned int YAMS_ReadMemory32(unsigned int address)
{
    if (memory) {
        // Word/long addresses are always divisible by 2, but not
        // always by 4, so we'll use some pointer black magic here...
        char* memPtr = memory + address;
        unsigned int value = SDL_SwapBE32(*((Uint32*) memPtr));
        return value;
    }

    return 0;
}


/** Write an 8-bit value to memory, or print an error if in ROM space. */
void YAMS_WriteMemory8(unsigned int address, unsigned int value)
{
    if ((address >= lowROMBound) && (address <= highROMBound))
        printf("Ignored write of 0x%02X to ROM space at $%06X\n", value, address);
    else {
        if (memory)
            memory[address] = (char) value;
    }
}


/** Write a 16-bit value to memory, or print an error if in ROM space. */
void YAMS_WriteMemory16(unsigned int address, unsigned int value)
{
    if ((address >= lowROMBound) && (address <= highROMBound))
        printf("Ignored write of 0x%04X to ROM space at $%06X\n", value, address);
    else {
        // Everything has to be stored in big-endian format,
        // since we don't know in what size it will be read back out.
        if (memory) {
            Uint16* memPtr = (Uint16*) memory;
            memPtr[address / 2] = SDL_SwapBE16((Uint16) value);
        }
    }
}


/** Write a 32-bit value to memory, or print an error if in ROM space. */
void YAMS_WriteMemory32(unsigned int address, unsigned int value)
{
    if ((address >= lowROMBound) && (address <= highROMBound))
        printf("Ignored write of 0x%08X to ROM space at $%06X\n", value, address);
    else {
        // Everything has to be stored in big-endian format,
        // since we don't know in what size it will be read back out.
        if (memory) {
            Uint32* memPtr = (Uint32*) memory;
            memPtr[address / 4] = SDL_SwapBE32((Uint32) value);
        }
    }
}
