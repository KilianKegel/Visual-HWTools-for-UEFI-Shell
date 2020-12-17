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
    This module implements the NVRAMSpy main program
@todo
    - add /p page-by-page

@mainpage
    NVRAMSpy for all

@section intro_sec Introduction
    This program is used to list and dump NVRAM\n

@subsection Parm_sec Command line parameters
        NVRAMSpy w/o parameter      : list all variables\n
        NVRAMSpy /dump /id:<ddd>    : hex-dump of a particular NVRAM variable by ID\n
        NVRAMSpy /dump /all         : hex-dump of a all  NVRAM variable\n
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "..\includes\UniDump.h"
#undef NULL
#include <uefi.h>

extern char* strefierror(EFI_STATUS errcode);
#define ELC(x) (sizeof(x) / sizeof(x[0]))   /* element count */

//
// global variables
//
char gfNoParm = 1;  // flag, no parameter in command line
char gfAll = 0;     // flag, do it for all
char gfDmp = 0;     // flag, dump command
int  gID   = 0;     // IDentifier, shown at /list


/*! 
    @fn unsigned long long GetMem8(void *pAddr)

    @brief read a BYTE from a given memory location

    @details
    
    @param[in] *pAddr

    @return byte read 
*/
unsigned long long GetMem8(void *pAddr)
{
    unsigned char nRet,*p = (unsigned char*) pAddr;
    nRet = 0xFF & *p;
    return nRet;

}

/*! 
    @fn static unsigned WriteString(IN char *pszLineOfText) 

    @brief print a text line

    @details
    
    @param[in] *pszLineOfText : pointer to ZERO terminated text line

    @return 0
*/
unsigned WriteString(char *pszLineOfText) 
{

    printf(pszLineOfText);

    return 0;
};

/*!
    @fn int chkcmdln(int argc, char **argv)

    @brief checks the command line for /help and for "/all" parameter

    @details
            The function checks command line for helprequest (and returns 1
            in theat case) or for additional, global parameters like "/all" or
            "/pcionly" (to display only 256 byte header for each PCIE function

    @param[in] argc : argument count
    @param[in] argv : argument vector

    @return 1 : helptext was shown
    @return 0 : otherwise

*/
int chkcmdln(int argc, char** argv) {
    int nRet = 0;
    int i, j;
    int ihlp = 0, iid = 0;
    char fCmdErr = 0;
    static char* helpstr[] = { "/h","/help","/hlp","-h","-help","--h","--help", "/?","-?","--?" };

    for (i = 0; i < argc; i++) {
        int tok;
        int id;

        for (j = 0; ihlp == 0 && j < ELC(helpstr); j++)
            ihlp |= (0 == strcmp(argv[i], helpstr[j]) ? i : 0);

        gfAll |= !strcmp("/all", argv[i]);
        gfDmp |= !strcmp("/dump", argv[i]);
        
        if (0 == strncmp("/id:", argv[i], sizeof("/id:") - 1))
        {
            iid = i;
            tok = sscanf(argv[i], "/id:%d", &id);
            if (1 != tok)
                fprintf(stderr, "Command line prameter \"%s\" unknown\n", argv[i]);
            
            if (1 == tok)
                gID = id;
            
            //printf("-> ID %d\n", gID);
        }
    }

    gfNoParm = 1 == argc;

    if (0 != ihlp)
    {
        printf("    NVRAMSpy w/o parameter      : list all variables\n");
        printf("    NVRAMSpy /dump /id:<ddd>    : hex-dump of a particular NVRAM variable by ID\n");
        printf("    NVRAMSpy /dump /all         : hex-dump of a all  NVRAM variable\n");
        nRet = 1;
    }

    if (!(gfDmp && (gfAll || gID)))  // validate "/dump" parameter to include "/all" or "id:<ddd>"
    {
        fprintf(stderr, "Command line parameter wrong or missing\n");
        fprintf(stderr, "Invoke NVRAMSpy /help\n");
    }

    return nRet;
}

/*! 
    @fn int main(int argc, char **argv)

    @brief The NVRAMSpy main

    @details
    
    @param[in] argc
    @param[in] argv

    @return 0  : success
    @return !0 : failure
*/
int main(int argc, char **argv)
{
    EFI_SYSTEM_TABLE* SystemTable = (EFI_SYSTEM_TABLE*)(argv[-1]);      //SystemTable is passed in argv[-1]
    EFI_HANDLE ImageHandle = (void*)(argv[-2]);                         //ImageHandle is passed in argv[-2]

    void *pStart = NULL;                        // start / end memory location
    int nLength = 256, nNumberOfElements = 1;   // length = default length, number of elements
    int nRet = EXIT_FAILURE;
    int i,j;
    long long qwValue = (long long)-1;
    static char *helpstr[] = {"/h","/help","/hlp","-h","-help","--h","--help", "/?","-?","--?" };

    do {
        //
        // help
        //
        if (1 == chkcmdln(argc, argv)) 
        {
            nRet = EXIT_SUCCESS;
            break;
        }

        //
        // list
        //
        if (gfNoParm)
        {
            EFI_STATUS Status = EFI_SUCCESS;
            wchar_t VarName[128], *pwcsVarName = memset(&VarName,0,sizeof(VarName));
            unsigned long long VarNameSize = sizeof(VarName);
            EFI_GUID VarGuid, *pVarGuid = memset(&VarGuid, 0, sizeof(VarGuid));
            uint32_t VarAttr;
            uint64_t VarSize;
            static char VarBuf[65536 * 4];

            int i = 1;
            do 
            {
                UNIDUMPPARM hexparms = { .reg = 0, .bit.elmsizemin1 = 0, .bit.fBaseOfs = 0 };
                VarNameSize = sizeof(VarName);

                Status = SystemTable->RuntimeServices->GetNextVariableName(&VarNameSize, &VarName[0], &VarGuid);

                if (EFI_SUCCESS != Status && EFI_NOT_FOUND != Status) {
                    fprintf(stderr, "-> %3d %d: %s\n", i, __LINE__, strefierror(Status));
                    break;
                }


                VarSize = sizeof(VarBuf);
                VarAttr = 0;
                Status = SystemTable->RuntimeServices->GetVariable(&VarName[0], &VarGuid, &VarAttr, &VarSize, &VarBuf[0]);

                if (EFI_SUCCESS != Status && EFI_NOT_FOUND != Status) {
                    fprintf(stderr, "-> %3d %d: VarSize %llX %s\n", i, __LINE__, VarSize, strefierror(Status));
                    break;
                }

                printf("id:%d %-40ls%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X size 0x%zX\n",
                    i,
                    &VarName,
                    VarGuid.Data1, VarGuid.Data2, VarGuid.Data3, VarGuid.Data4[0], VarGuid.Data4[1], VarGuid.Data4[2], VarGuid.Data4[3], VarGuid.Data4[4], VarGuid.Data4[5], VarGuid.Data4[6], VarGuid.Data4[7],
                    VarSize
                );

                //UniDump(hexparms, VarSize, (unsigned long long)&VarBuf[0], GetMem8, WriteString);

                i++;
            } while (EFI_SUCCESS == Status);
        }

        //
        // /dump
        //
        if (gfDmp)
        {
            EFI_STATUS Status = EFI_SUCCESS;
            wchar_t VarName[128], * pwcsVarName = memset(&VarName, 0, sizeof(VarName));
            unsigned long long VarNameSize = sizeof(VarName);
            EFI_GUID VarGuid, * pVarGuid = memset(&VarGuid, 0, sizeof(VarGuid));
            uint32_t VarAttr;
            uint64_t VarSize;
            static char VarBuf[65536 * 4];

            int i = 1;
            do
            {
                UNIDUMPPARM hexparms = { .reg = 0, .bit.elmsizemin1 = 0, .bit.fBaseOfs = 0 };
                VarNameSize = sizeof(VarName);

                Status = SystemTable->RuntimeServices->GetNextVariableName(&VarNameSize, &VarName[0], &VarGuid);

                if (EFI_SUCCESS != Status && EFI_NOT_FOUND != Status) {
                    fprintf(stderr, "-> %3d %d: %s\n", i, __LINE__, strefierror(Status));
                    break;
                }


                VarSize = sizeof(VarBuf);
                VarAttr = 0;
                Status = SystemTable->RuntimeServices->GetVariable(&VarName[0], &VarGuid, &VarAttr, &VarSize, &VarBuf[0]);

                if (EFI_SUCCESS != Status && EFI_NOT_FOUND != Status) {
                    fprintf(stderr, "-> %3d %d: VarSize %llX %s\n", i, __LINE__, VarSize, strefierror(Status));
                    break;
                }

                if (i == gID || 1 == gfAll)
                {
                    printf("id:%d %-40ls%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X size 0x%zX\n",
                        i,
                        &VarName,
                        VarGuid.Data1, VarGuid.Data2, VarGuid.Data3, VarGuid.Data4[0], VarGuid.Data4[1], VarGuid.Data4[2], VarGuid.Data4[3], VarGuid.Data4[4], VarGuid.Data4[5], VarGuid.Data4[6], VarGuid.Data4[7],
                        VarSize
                    );

                    UniDump(hexparms, VarSize, (unsigned long long) & VarBuf[0], GetMem8, WriteString);
                }

                i++;
            } while (EFI_SUCCESS == Status);
        }
    } while (nRet = EXIT_SUCCESS);

    return nRet;
}
