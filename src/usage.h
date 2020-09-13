/***************************************************
* Argument parsing and usage/header printing       *
* Copyright (C) 2020 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#ifndef _YAMS_USAGE_H_
#define _YAMS_USAGE_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

typedef struct {
    char* ROMfn;
} YAMS_params;

void YAMS_PrintHeader();
void YAMS_PrintUsage();
YAMS_params* YAMS_ParseArgs(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //_YAMS_USAGE_H_
