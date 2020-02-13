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
    This module implements the Vmode main program
@todo

@mainpage
    Vmode for all

@section intro_sec Introduction
    This program is used to list available video modes and to change them\n

@subsection Parm_sec Command line parameters
    1. vmode w/o parameter: list modes\n
    2. vmode <modenum>: change to mode modenum
*/
#pragma warning(disable:4189)   // local variable is initialized but not referenced
#pragma warning(disable:4101)   // unreferenced local variable
#pragma warning(disable:4706)   // assignment within conditional expression
#pragma warning(disable:4804)   // '/': unsafe use of type 'bool' in operatio
#pragma warning(disable:4162)   // '_ReturnAddress': no function with C linkage found
#pragma warning(disable:4005)   // 'NULL': macro redefinition
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <uefi.h>
#include <protocol\GraphicsOutput.h>

extern char* strefierror(EFI_STATUS errcode);

int main(int argc, char** argv) {
    int nRet = 1;
    EFI_SYSTEM_TABLE* SystemTable = (EFI_SYSTEM_TABLE*)(argv[-1]);      //SystemTable is passed in argv[-1]
    EFI_HANDLE ImageHandle = (void*)(argv[-2]);                         //ImageHandle is passed in argv[-2]

    static EFI_GUID guidSTOP = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;
    static EFI_GUID guidGOP = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* pSTOP;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* pGOP;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN ModeNumber = argc > 1 ? atoi(argv[1]) : ULLONG_MAX, CurrentModeNumber, Columns = 0, Rows = 0;
    unsigned u, count;

    typedef struct tagVIDMOD {
        int mode;
        int horpix;
        int verpix;
        int horchar;    //columns
        int verchar;    //rows
    }VIDMOD;
    VIDMOD* pModes = (VIDMOD*)malloc(0);

    do {

        Status = SystemTable->BootServices->LocateProtocol(&guidGOP, NULL, (void**)&pGOP);

        if (EFI_SUCCESS != Status) {
            fprintf(stderr, "%s(%d)/%s() Status -> %s\n", __FILE__, __LINE__, __FUNCTION__, strefierror(Status));
            nRet = 1;
            break;
        }

        Status = SystemTable->BootServices->LocateProtocol(&guidSTOP, NULL, (void**)&pSTOP);

        if (EFI_SUCCESS != Status) {
            fprintf(stderr, "%s(%d)/%s Status -> %s\n", __FILE__, __LINE__, __FUNCTION__, strefierror(Status));
            return 1;
        }


        CurrentModeNumber = pSTOP->Mode->Mode;

        if (ULLONG_MAX == ModeNumber) {
            for (u = 0, count = 0; u < pGOP->Mode->MaxMode; u++) {

                Status = pSTOP->SetMode(pSTOP, u);

                if (EFI_SUCCESS != Status)                      // mode not supported
                    continue;
                count++;

                pModes = (VIDMOD*)realloc(pModes, count * sizeof(VIDMOD));

                Status = pSTOP->QueryMode(pSTOP, u, &Columns, &Rows);

                pModes[count - 1].mode = (int)u;
                pModes[count - 1].horchar = (int)Columns;
                pModes[count - 1].verchar = (int)Rows;
                pModes[count - 1].horpix = (int)pGOP->Mode->Info->HorizontalResolution;
                pModes[count - 1].verpix = (int)pGOP->Mode->Info->VerticalResolution;
            }

            Status = pSTOP->SetMode(pSTOP, CurrentModeNumber);

            printf("Current mode: %d\nMaxMode %d\n", (int)CurrentModeNumber, (int)pGOP->Mode->MaxMode);
            for (u = 0; u < count; u++)
                printf("Mode %d: %d*%d, %d*%d\n", pModes[u].mode, pModes[u].horpix, pModes[u].verpix, pModes[u].horchar, pModes[u].verchar);
        }
        else
        {
            Status = pSTOP->SetMode(pSTOP, ModeNumber);

            if (EFI_SUCCESS != Status) {                      // mode not supported
                //fprintf(stdout, "Mode %d is not supported\n", (int)ModeNumber);
                fprintf(stderr, "Mode %d is not supported\n", (int)ModeNumber);
            }

        }
        nRet = 0;
    } while (0);

    return nRet;
}
