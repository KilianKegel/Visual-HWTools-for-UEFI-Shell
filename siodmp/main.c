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
    This module implements the generic SIO main program
@todo

@mainpage
    Generic SuperI/O dump

@section intro_sec Introduction
    This program is used to dump generic SuperI/O devices

@subsection Parm_sec Command line parameters
    1. siodmp <dev>
    2. siodmp /all
    3. siodmp /info

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

#define IODELAY if(1){int xx = 8;while(xx--)outp(0xED,0x55);}

unsigned siord8(int key, int cfgbase, int dev, int reg) {
#define IDX cfgbase
#define DAT (cfgbase+1)
    unsigned bRet;

    outp(IDX, key); IODELAY;
    outp(IDX, key); IODELAY;
    outp(IDX, 0x7); IODELAY;
    outp(DAT, dev); IODELAY;
    outp(IDX, reg); IODELAY;

    bRet = inp(DAT); IODELAY;

    outp(IDX, 0xAA); IODELAY;
    //printf("Base: %02X Key: %02X reg: %02X -> %02X\n", cfgbase, key, reg, bRet);
    return bRet;
}

int main(int argc, char** argv) {
    int dev = 0, devend = 0x16, cfgbase = 0, key;
    unsigned ID_H, ID_L;
    int nRet = 0;
    int i;

    help(argc, argv);  // check command line parameter

    do
    {
        for (key = 0x55; key <= 0x87; key += 0x32 /* NOTE: 0x55 + 0x32 == 0x87 */) {
            for (cfgbase = 0x2E; cfgbase <= 0x4E; cfgbase += 0x20) {

                ID_H = siord8(key, cfgbase, 0, 0x20);
                ID_L = siord8(key, cfgbase, 0, 0x21);

                if ((0xFF & ID_H) != 0xFF || (0xFF & ID_L) != 0xFF)
                    break;
            }
            if ((0xFF & ID_H) != 0xFF || (0xFF & ID_L) != 0xFF)
                break;
        }

        if (cfgbase > 0x4e) {
            nRet = 1;
            puts("SuperI/O not found\n");
            break;
        }

        if (argc < 2) {		// print help screen
            printf("    %s <dev>\n    %s /info\n    %s /all\n\n", argv[0], argv[0], argv[0]);
            break;
        }

        if (0 == strcmp(argv[1], "/info")) {
            printf("SuperI/O index/data base is 0x%02X, ID is %02X%02X\n", cfgbase, 0xFF & ID_H, 0xFF & ID_L);
            break;
        }

        if (0 != strcmp(argv[1], "/all")) {
            sscanf(argv[1], "%x", &dev);
            devend = dev + 1;
        }

        do {
            printf("device 0x%X\n", 0xFF & dev);
            for (i = 0; i < 256 / TYPESIZE; i++)
                printf((i % (16 / TYPESIZE) == 0 ? FORMATW_ADDR : FORMATWOADDR), (i % (16 / TYPESIZE) == 0 ? (void*)(i * TYPESIZE) : ""), TYPEMASK & siord8(key, cfgbase, dev, i * TYPESIZE), ((i + 1) % (16 / TYPESIZE)) ? (((i + 1) % (8 / TYPESIZE)) ? " " : " - ") : "\n");
        } while (++dev < devend);

    } while (0);

    return(nRet);
}

void help(int argc, char** argv)
{
    // ----- check argument count and help request, kept very simple

    if (argc < 2 || (argc > 1 && !strcmp(argv[1], "/?")))
    {
        printf("siodmp [/all] [/info] dev\n");
        exit(1);
    }
}