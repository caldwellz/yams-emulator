/***************************************************
* YAMS-Emu Main Entry Point                        *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "config.h"
#include "memory.h"
#include "usage.h"
#include "musashi/m68k.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

static const Uint32 updateInterval = 1000 / SIM_REFRESH_HZ;
static const Uint32 updateCycles = CPU_CLOCK_HZ / SIM_REFRESH_HZ;

// Callback to run the CPU every update interval.
// Runs in a separate thread, so must be careful not to touch the
// memory or CPU internals from the main thread after starting.
Uint32 ExecutionCallback(Uint32 interval, void *param)
{
	m68k_execute(updateCycles);
	return interval;
}


// Still using just the console for now, so temporarily revert SDL_main trickery
#undef main
int main(int argc, char* argv[])
{
    YAMS_PrintHeader();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Set up memory map and ROM image
    YAMS_params* params = YAMS_ParseArgs(argc, argv);
	if (!YAMS_InitMemoryMap(MEMORY_BITS)) {
		printf("Failed to allocate memory map\n");
		return -1;
	}
    if (!YAMS_LoadROMImage(params->ROMfn, 0)) {
		printf("Failed to load ROM image\n");
		return -1;
	}

	// Start the CPU emulation loop
    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68010);
    m68k_pulse_reset();
	SDL_TimerID CPUTimer = SDL_AddTimer(updateInterval, ExecutionCallback, NULL);

	// Handle any events that come up, and hang this thread in the background otherwise
    SDL_Event evt;
	while (1) {
		if (SDL_PollEvent(&evt)) {
			// Need to keep this event type outside a switch
			// so we can break out of the while loop
			if (evt.type == SDL_QUIT) {
				SDL_RemoveTimer(CPUTimer);
				SDL_Delay(updateInterval);
				break;
			}
		}
		else
			SDL_Delay(updateInterval);
	}

	// Clean up
	YAMS_FreeMemoryMap();
    free(params);
	SDL_Quit();
    printf("End of simulation");

    return 0;
}
