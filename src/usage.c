/***************************************************
* Argument parsing and usage/header printing       *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "usage.h"
#include "version.h"
#include <SDL2/SDL_log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void YAMS_PrintHeader()
{
    // SDL logs print an annoying priority string before the log message, so
    // the header and usage are the two things we still print directly to stdout.
    const char* header = "YAMS (Yet Another M68k System) Emulator (%s-%s [%s-%s])\nCopyright (C) 2020 Zach Caldwell\n\n";
    printf(header, YAMS_VERSION, YAMS_REVISION, YAMS_COMPILER, YAMS_COMPILER_VERSION);
}


void YAMS_PrintUsage()
{
    printf("Usage: yams-emu [options] <ROM file>\n\
Options:\n\
  -h, --help    Display this usage message and exit.");
}


void usage_error(const char* msg)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg);
    YAMS_PrintUsage();
    exit(1);
}


YAMS_params* YAMS_ParseArgs(int argc, char* argv[])
{
    if (argc && argv) {
        if (argc >= 2) { // Minimum is standard arg0 + ROM filename
            YAMS_params* params = malloc(sizeof(YAMS_params));
            if (params == NULL) {
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Can't allocate memory for parameter structure");
                exit(-1);
            }

            // Parse the arguments in order
            for (int i = 1; i < argc; ++i) {
                if (strcmp(argv[i], "-h") == 0
                  || strcmp(argv[i], "--help") == 0)
                {
                    YAMS_PrintUsage();
                    free(params);
                    exit(0);
                }
            }

            // If we're still running at this point,
            // the ROM file should be the last argument
            params->ROMfn = argv[argc - 1];
            return params;
        }
        else
            usage_error("No ROM filename specified.\n");
    }
    else
        usage_error("No command-line arguments given! Possibly running in an environment that doesn't support them?\n");

    return NULL;
}
