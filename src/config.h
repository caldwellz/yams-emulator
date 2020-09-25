/***************************************************
* Emulator build-time configuration                *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#ifndef _YAMS_CONFIG_H_
#define _YAMS_CONFIG_H_

// Define the bitwidth of real memory (RAM/ROM) space.
// 21 address bits == 2MB
#define MEMORY_BITS  21

// Define the debug memory address.
// Any value written to this address will be output to the console
#define DBG_ADDRESS  0xDEC0DE

// Define the simulation refresh speed (in Hz).
// Helps prevent visual jitter by spacing out cycle use, vs. just quickly
// burning all the cycles-per-second and delaying the rest of the second
#define SIM_REFRESH_HZ 10

// Define the emulated CPU's clock speed (in Hz).
#define CPU_CLOCK_HZ 12000000

#endif //_YAMS_CONFIG_H_
