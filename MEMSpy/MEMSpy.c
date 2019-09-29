/*!
@copyright

    Copyright (c) 2019, Kilian Kegel. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file main.c

@brief 
    This module implements the MEMSpy main program
@todo
    - add /p page-by-page
    - add /wr[8][16][32][64] to write a memory region

@mainpage
    MEMSpy for all

@section intro_sec Introduction
    This program is used to dump and write/fill system memory\n

@subsection Parm_sec Command line parameters
    1. /dump[8][16][32][64] hexaddress: 8/16/32/64-bit hex-dump of memory\n
    2. /fill[8][16][32][64] hexaddress hexvalue [hexcount]: write value to memory
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\includes\UniDump.h"

#define ELC(x) (sizeof(x) / sizeof(x[0]))   /* element count */

//
// global variables
//

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
    @fn unsigned long long GetMem16(void *pAddr)

    @brief read a WORD from a given memory location

    @details
    
    @param[in] *pAddr

    @return word read 
*/
unsigned long long GetMem16(void *pAddr)
{
    unsigned short  nRet, *p = (unsigned short*)pAddr;
    nRet = 0xFFFF & *p;
    return nRet;

}

/*! 
    @fn unsigned long long GetMem32(void *pAddr)

    @brief read a DWORD from a given memory location

    @details
    
    @param[in] *pAddr

    @return dword read 
*/
unsigned long long GetMem32(void *pAddr)
{
    unsigned int  nRet, *p = (unsigned int*)pAddr;
    nRet = 0xFFFFFFFF & *p;
    return nRet;

}

/*! 
    @fn unsigned long long GetMem64(void *pAddr)

    @brief read a QWORD from a given memory location

    @details
    
    @param[in] *pAddr

    @return qword read 
*/
unsigned long long GetMem64(void *pAddr)
{
    unsigned long long  nRet, *p = (unsigned long long *)pAddr;
    nRet = 0xFFFFFFFFFFFFFFFFLL & *p;
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
    @fn int main(int argc, char **argv)

    @brief The PCIESpy main

    @details
    
    @param[in] argc
    @param[in] argv

    @return 0  : success
    @return !0 : failure
*/
int main(int argc, char **argv)
{
    void *pStart = NULL;                        // start / end memory location
    int nLength = 256, nNumberOfElements = 1;   // length = default length, number of elements
    int nRet = 0;
    int i,j;
    int ihlp,idmp,ifll;
    long long qwValue = (long long)-1;
    static char *helpstr[] = {"/h","/help","/hlp","-h","-help","--h","--help", "/?","-?","--?" };

    do {
        //
        // help
        //
        for (i = 0, ihlp = 0; ihlp == 0 && i < argc; i++)
            for (j = 0; ihlp == 0 && j < ELC(helpstr); j++)
                ihlp = (0 == strcmp(argv[i], helpstr[j]) ? i : 0);

        if (0 != ihlp || 1 == argc)
        {
            printf("    MEMSpy w/o parameter : help screen\n");
            printf("    MEMSpy /dump[8][16][32][64] hexaddress [hexlength]: 8 / 16 / 32 / 64 - bit hex - dump of memory\n");
            printf("    /fill[8][16][32][64] hexaddress hexvalue [hexcount]: write value to memory\n");
            nRet = 1;
            break;//do{}while(0)
        }

        //
        // /dump
        //
        if(1)
        {
            static struct {
                char* pszCmdLine;
                char  bWidth;
                void* pfn81632;
            }dumpparm[] = {
                { /*CommandLineString*/"/dump8" , /*size minus one */1 - 1, /*function to get element */&GetMem8    },
                { /*CommandLineString*/"/dump16", /*size minus one */2 - 1, /*function to get element */&GetMem16   },
                { /*CommandLineString*/"/dump32", /*size minus one */4 - 1, /*function to get element */&GetMem32   },
                { /*CommandLineString*/"/dump64", /*size minus one */8 - 1, /*function to get element */&GetMem64   },
                { /*CommandLineString*/"/dump"  , /*size minus one */1 - 1, /*function to get element */&GetMem8    }
            };

            for (i = 1, idmp = -1; idmp == -1 && i < argc; i++)
                for (j = 0; idmp == -1 && j < ELC(dumpparm); j++) {
                    //printf("%d/%d: %s\n", i, j, argv[i]);
                    idmp = (0 == strcmp(argv[i], dumpparm[j].pszCmdLine) ? j : -1);
                }
            
            if (-1 != idmp) {
                UNIDUMPPARM hexparms = { .reg = 0, .bit.elmsizemin1 = dumpparm[idmp].bWidth, .bit.fBaseOfs = 1 };

                i--;
                if (!(argc > i + 1)) {
                    fprintf(stderr, "missing address parameter\n");
                    nRet = 1;
                    break;
                }
                    sscanf(argv[i + 1], "%llx", &((unsigned __int64)pStart));
                if (argc > i + 2)
                    sscanf(argv[i + 2], "%x", &nLength);
                
                fprintf(stderr,"%p\n", pStart);
                UniDump(hexparms, nLength, (unsigned long long)pStart, dumpparm[idmp].pfn81632, WriteString);
                break;
            }
            //else
            //    fprintf(stderr, "%s(%d): fail\n", __FILE__, __LINE__);
        }

        //
        // /fill
        //
        if (1)
        {
            int         x = 0;
            char        *p8;
            short       *p16;
            int         *p32;
            long long   *p64;

            static struct {
                char* pszCmdLine;
                char  bWidth;
            }fillparm[] = {
                { /*CommandLineString*/"/fill8" , /*size minus one */1 - 1 },
                { /*CommandLineString*/"/fill16", /*size minus one */2 - 1 },
                { /*CommandLineString*/"/fill32", /*size minus one */4 - 1 },
                { /*CommandLineString*/"/fill64", /*size minus one */8 - 1 },
                { /*CommandLineString*/"/fill"  , /*size minus one */1 - 1 }
            };         

            for (i = 1, ifll = -1; ifll == -1 && i < argc; i++)
                for (j = 0; ifll == -1 && j < ELC(fillparm); j++) {
                    //printf("%d/%d: %s\n", i, j, argv[i]);
                    ifll = (0 == strcmp(argv[i], fillparm[j].pszCmdLine) ? j : -1);
                }

            if (-1 != ifll) {

                i--;
                if (argc <= i + 2) {
                    fprintf(stderr, "missing parameter /fill pattern\n");
                    nRet = 1;
                    break;
                }
                sscanf(argv[i + 1], "%llx", &((unsigned __int64)pStart));
                sscanf(argv[i + 2], "%llx", &qwValue);

                if (argc > i + 3)
                    sscanf(argv[i + 3], "%x", &nNumberOfElements);
                
                    //printf("BWidth == %d, where -> %p, nNumberOfElements == %d, pattern == %llX\n", fillparm[ifll].bWidth, pStart, nNumberOfElements, qwValue);
  
                switch (fillparm[ifll].bWidth) {
                case 0:
                    p8 = pStart;
                    while (x++ < nNumberOfElements)
                        *p8++ = (char)qwValue;
                    break;
                case 1:
                    p16 = pStart;
                    while (x++ < nNumberOfElements)
                        *p16++ = (short)qwValue;
                    break;
                case 3:
                    p32 = pStart;
                    while (x++ < nNumberOfElements)
                        *p32++ = (int)qwValue;
                    break;
                case 7:
                    p64 = pStart;
                    while (x++ < nNumberOfElements)
                        *p64++ = (long long)qwValue;
                    break;
                }
            }
        }

    } while (0);
    return nRet;
}
