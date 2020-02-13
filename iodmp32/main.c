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
    This module implements the I/O DUMP 32/dword main program
@todo

@mainpage
    I/O DUMP for all

@section intro_sec Introduction
    This program is used to dump I/O ranges

@subsection Parm_sec Command line parameters
    1. iodmp32 <base> <end>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(int argc, char** argv);		// prototype for help()

#define TYPE long
#define TYPESIZE sizeof(TYPE)
#define TYPEMASK ((1ULL << TYPESIZE * 8)-1)

#define FORMATW_ADDR "%016X: %08X%s"
#define FORMATWOADDR "%s%08X%s"

int main(int argc, char** argv) {
    int start = 0, end = 0, i;

    help(argc, argv);  // check command line parameter

    sscanf(argv[1], "%x", &start);
    if (argc > 2)
        sscanf(argv[2], "%x", &end);
    else
        end = start + 16;

    for (i = 0; i < (end - start) / TYPESIZE; i++)
        printf((i % (16 / TYPESIZE) == 0 ? FORMATW_ADDR : FORMATWOADDR), (i % (16 / TYPESIZE) == 0 ? (void*)(start + i * TYPESIZE) : ""), TYPEMASK & inpd(start + i * TYPESIZE), ((i + 1) % (16 / TYPESIZE)) ? (((i + 1) % (8 / TYPESIZE)) ? " " : " - ") : "\n");

}

void help(int argc, char** argv)
{
    // ----- check argument count and help request, kept very simple

    if (argc < 2 || (argc > 1 && !strcmp(argv[1], "/?")))
    {
        printf("IODMP32 start [end]\n");
        exit(1);
    }
}