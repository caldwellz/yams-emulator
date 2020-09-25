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

// Define the bitwidth of real memory (RAM/ROM) space
// 21 address bits == 2MB
#define MEMORY_BITS  21

// Define the debug memory address
// Any value written to this address will be output to the console
#define DBG_ADDRESS  0xDEC0DE

#endif //_YAMS_CONFIG_H_
