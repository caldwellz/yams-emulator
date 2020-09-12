/***************************************************
* YAMS-Emu Main Entry Point                        *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "version.h"
#include "musashi/m68k.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    printf("YAMS (Yet Another M68k System) Emulator\nVersion %s-%s (%s-%s)\nCopyright (C) 2020 Zach Caldwell\n\n", YAMS_VERSION, YAMS_REVISION, YAMS_COMPILER, YAMS_COMPILER_VERSION);

    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68010);
    m68k_pulse_reset();
    m68k_execute(50);

    printf("End of simulation");
    return 0;
}
