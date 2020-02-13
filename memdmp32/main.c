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
    This module implements the MEMORY DUMP 32/byte main program
@todo

@mainpage
    MEMORY DUMP for all

@section intro_sec Introduction
    This program is used to dump MEMORY ranges

@subsection Parm_sec Command line parameters
    1. memdmp32 <base> <end>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(int argc, char** argv);		// prototype for help()

#define TYPE long
#define TYPESIZE sizeof(TYPE)
#define TYPEMASK (0xFFFFFFFF)

#define FORMATW_ADDR "%016llX: %08X%s"
#define FORMATWOADDR "%s%08X%s"

int main(int argc, char** argv) {
    unsigned long long  start = 0, end = 0, i;

    help(argc, argv);  // check command line parameter

    sscanf(argv[1], "%llx", &start);
    if (argc > 2)
        sscanf(argv[2], "%llx", &end);
    else
        end = start + 256;

    for (i = 0; i < (end - start) / TYPESIZE; i++)
        printf((i % (16 / TYPESIZE) == 0 ? FORMATW_ADDR : FORMATWOADDR), (i % (16 / TYPESIZE) == 0 ? (void*)(start + i * TYPESIZE) : ""), TYPEMASK & *((TYPE*)(start + i * TYPESIZE)), ((i + 1) % (16 / TYPESIZE)) ? (((i + 1) % (8 / TYPESIZE)) ? " " : " - ") : "\n");

}

void help(int argc, char** argv)
{
    // ----- check argument count and help request, kept very simple

    if (argc < 2 || (argc > 1 && !strcmp(argv[1], "/?")))
    {
        printf("MEMDMP32 start [end]\n");
        exit(1);
    }
}