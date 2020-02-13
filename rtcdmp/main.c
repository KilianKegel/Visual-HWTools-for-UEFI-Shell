/*!
@copyright

    Copyright (c) 2020, Kilian Kegel. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file main.c

@brief 
    This module implements the RTC DUMP 8/byte main program
@todo

@mainpage
    RTC DUMP for all

@section intro_sec Introduction
    This program is used to dump RTC at I/O 0x70/0x71

    @subsection ref_sec References
    @note <a href="https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf#page=4540">RTC</a>\n

@subsection Parm_sec Command line parameters
    1. RTCDMP
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(int argc, char** argv);		// prototype for help()

#define TYPE char
#define TYPESIZE sizeof(TYPE)
#define TYPEMASK ((1ULL << TYPESIZE * 8)-1)

#define FORMATW_ADDR "%016X: %02X%s"
#define FORMATWOADDR "%s%02X%s"

unsigned rtcrd(int i) {
    outp(0x70, i);
    return (inp(0x71));
}
int main(int argc, char** argv) {
    int i;

    help(argc, argv);  // check command line parameter

    for (i = 0; i < 128 / TYPESIZE; i++)
        printf((i % (16 / TYPESIZE) == 0 ? FORMATW_ADDR : FORMATWOADDR), (i % (16 / TYPESIZE) == 0 ? (void*)(i * TYPESIZE) : ""), TYPEMASK & rtcrd(i * TYPESIZE), ((i + 1) % (16 / TYPESIZE)) ? (((i + 1) % (8 / TYPESIZE)) ? " " : " - ") : "\n");

}

void help(int argc, char** argv)
{
    // ----- check argument count and help request, kept very simple

    if (argc < 1 || (argc > 1 && !strcmp(argv[1], "/?")))
    {
        printf("REAL TIME CLOCK(MC146818) DUMP\nRTCDMP [noparmrequired]\n");
        exit(1);
    }
}