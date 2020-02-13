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
    This module implements the I/O write 16/word main program
@todo

@mainpage
    I/O write for all

@section intro_sec Introduction
    This program is used to write I/O ranges

@subsection Parm_sec Command line parameters
    1. iowr16 <address> <val>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void help(int argc, char** argv);		// prototype for help()

int main(int argc, char** argv) {
    int p, v;

    help(argc, argv);  // check command line parameter

    sscanf(argv[1], "%x", &p);
    sscanf(argv[2], "%x", &v);

    outpw(p, v);
}

void help(int argc, char** argv)
{
    // ----- check argument count and help request, kept very simple

    if (argc < 3 || (argc > 1 && !strcmp(argv[1], "/?")))
    {
        printf("IOWR8 ioaddr val\n");
        exit(1);
    }
}