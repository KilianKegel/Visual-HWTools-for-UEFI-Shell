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

@file _UniDump.c

@brief 
    This module implements the universal dump routine
@todo
    implement pitch support
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "..\includes\UniDump.h"

static const char szTwoSpaces[] = { 0x20,'\0' };
static const char szOneSpace [] = { 0x20,'\0' };

/*! 
    @fn static int PrintAscii(char *pBuffer, unsigned elmsize, unsigned cToPrint,unsigned char *pTextLineBuf)

    @brief prints the ASCII interpretation binary byte/word/dword/qword

    @details Features:
    
    @param[in] *pBuffer : pointer to binary buffer
    @param[in] elmsize : element size
    @param[in] cToPrint : count to print
    @param[in] *pTextLineBuf : pointer to text buffer

    @return 0
*/
static int PrintAscii(char *pBuffer, unsigned elmsize, unsigned cToPrint,unsigned char *pTextLineBuf) {
    unsigned char      *pb  = (unsigned char*) &pBuffer[0];
    unsigned short     *pw  = (unsigned short*)&pBuffer[0];
    unsigned int       *pdw = (unsigned int*)  &pBuffer[0];
    unsigned long long *pqw = (unsigned long long*)&pBuffer[0];
    unsigned long long qwLit2Big;/*!< little endian to big endian translation buffer*/
    unsigned char *pLit2Big = (unsigned char*)&qwLit2Big;
    unsigned j;

    #define PRINTREVERSE for (k = elmsize - 1 ; k != (unsigned)-1 ; k--){\
                             sprintf(&pTextLineBuf[strlen(pTextLineBuf)],"%c", isalnum(pLit2Big[k]) ? 0xFF & pLit2Big[k] : '.'); \
                         }\
                         if (elmsize - 1){/*!< add space between ASCII char, except in 8-bit format*/\
                             sprintf(&pTextLineBuf[strlen(pTextLineBuf)]," ");\
                         }// END PRINTREVERSE

                switch(elmsize){
                    unsigned k;
                    case sizeof(char):
                        for (j = 0; j < cToPrint; j += elmsize) {
                            *((unsigned char*)pLit2Big) = 0xFF & pb[j / elmsize];
                            PRINTREVERSE;
                        }
                        break;

                    case sizeof(short) :
                        for (j = 0; j < cToPrint; j += elmsize) {
                            *((unsigned short*)pLit2Big) = 0xFFFF & pw[j / elmsize];
                            PRINTREVERSE;
                        }
                        break;

                    case sizeof(int) :
                        for (j = 0; j < cToPrint; j += elmsize) {
                            *((unsigned int*)pLit2Big) = 0xFFFFFFFF & pdw[j / elmsize];
                            PRINTREVERSE;
                        }
                        break;

                    case sizeof(long long) :
                        for (j = 0; j < cToPrint; j += elmsize) {
                            *((unsigned long long*)pLit2Big) = 0xFFFFFFFFFFFFFFFFLL & pqw[j / elmsize];
                            PRINTREVERSE;
                        }
                        break;
                }
    return 0;
}

/*! 
    @fn int UniDump(UNIDUMPPARM ctrl, unsigned elmcount, unsigned long long startaddr, unsigned long long(*pfnGetElm)(unsigned long long qwAddr),unsigned (*pfnWriteStr)(char *szLine))

    @brief dump an addressrange, highly configurable

    @details Features:
        1. w/ or w/o appended ASCII translation -> UNIDUMPPARM.bit.fNoAscii
        2. byte/word/dword and qword support    -> UNIDUMPPARM.bit.elmsize
        3. configurable/enabe/disable address size printed at begin of each line -> UNIDUMPPARM.bit.nAddrSize
        4. configurable bytes per lane + 1, until 128 -> UNIDUMPPARM.bit.nBytesPerLine
        5. configurable base and offset only print    -> UNIDUMPPARM.bit.fBaseOfs
        6. configurable dash character "-" at half of the line -> UNIDUMPPARM.bit.fNoDash
        7. configurable pitch to next character -> UNIDUMPPARM.bit.pitch
    
    @param[in] ctrl : control word
    @param[in] elmcount : element count
    @param[in] startaddr : start address
    @param[in] pfnGetElm : get element routine
    @param[in] pfnWriteStr : call back routine to print a string
    
    @return 0
*/
int UniDump(UNIDUMPPARM ctrl, unsigned elmcount, unsigned long long startaddr, unsigned long long(*pfnGetElm)(unsigned long long qwAddr),unsigned (*pfnWriteStr)(char *szLine))
{

    unsigned elmsize = 1 + ctrl.bit.elmsizemin1;
    unsigned u/*<unsigned index*/;
    unsigned nLineLength = ctrl.bit.nBytesPerLine ? 1 + ctrl.bit.nBytesPerLine : 16;
    unsigned nLineLengthHalf = nLineLength/2;
    unsigned char *pBuffer = malloc(128);
    unsigned char *pTextLineBuf = malloc(18/*max. AddressSize*/ + 128/*max. characters*/*4 + 5/*Dash + szTwoSpaces*/);
    unsigned char      *pb  = (unsigned char*)     &pBuffer[0];
    unsigned short     *pw  = (unsigned short*)    &pBuffer[0];
    unsigned int       *pdw = (unsigned int*)      &pBuffer[0];
    unsigned long long *pqw = (unsigned long long*)&pBuffer[0];
    char *rgszAddrXX[] = { { "%016llX: " },{ "%08llX: " },{ "%04llX: " },{ "%02llX: " },{ "" } };/*<address field size strings*/
    char *pAddrXX = rgszAddrXX[ctrl.bit.nAddrSize];

    pTextLineBuf[0] = '\0';

    for (u = 0; u < elmcount; u += elmsize) {
        
        if(0 == ctrl.bit.fNoDash)
            if (0 == ((u) % nLineLengthHalf) && 0 != ((u) % nLineLength))
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)],"- ");
        
        if (0 == (u % nLineLength))
            sprintf(&pTextLineBuf[strlen(pTextLineBuf)], pAddrXX, u + (1 == ctrl.bit.fBaseOfs ? startaddr : 0LL));
        
        switch (elmsize) {
            case 1: pb [(u % nLineLength) / 1] = (unsigned char)     (*pfnGetElm)(startaddr + u); 
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "%02X ", 0xFF & pb[(u % nLineLength) / 1]);
                break;
            case 2: pw [(u % nLineLength) / 2] = (unsigned short)    (*pfnGetElm)(startaddr + u); 
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "%04X ", 0xFFFF & pw[(u % nLineLength) / 2]);
                break;
            case 4: pdw[(u % nLineLength) / 4] = (unsigned int)      (*pfnGetElm)(startaddr + u); 
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "%08X ", 0xFFFFFFFF & pdw[(u % nLineLength) / 4]);
                break;
            case 8: pqw[(u % nLineLength) / 8] = (unsigned long long)(*pfnGetElm)(startaddr + u); 
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "%016llX ", 0xFFFFFFFFFFFFFFFFLL & pqw[(u % nLineLength) / 8]);
                break;
        }

        if (0 == ((u + elmsize) % nLineLength)) {
//
// print ascii values
//
            if(0 == ctrl.bit.fNoAscii){
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)], szTwoSpaces);
                PrintAscii(&pBuffer[0],elmsize, nLineLength, &pTextLineBuf[strlen(pTextLineBuf)]);
            }
            sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "\n");
            pfnWriteStr(pTextLineBuf);
            pTextLineBuf[0] = '\0';
        }
    }
//
// after glow - print remaining ASCII chars
//
    if (1) {
        unsigned rem = u % nLineLength/*remining hex numbers (filled w/ space)*/;
        unsigned asc = nLineLength - rem/*ASCII characters not yet printed*/;
        unsigned hex = asc / elmsize/*HEX numbers not yet printed == asc / elmsize*/;
        unsigned cSpaces = hex * elmsize * 2 + hex/*count spaces between the single numbers, depending on printsize*/;
        unsigned cDashSpace = ctrl.bit.fNoDash ? 0 : (rem > nLineLengthHalf ? 0 : 2);/*count dash and space 0 / 2, depending on HEXDUMPPARMS.bit.fNoDash*/


        if(0 != rem && 1 == ctrl.bit.fNoAscii)
            sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "\n");

        if (0 == ctrl.bit.fNoAscii){
            if (rem) {
                unsigned x;
                for (x = 0; x < cSpaces + cDashSpace; x++) {
                    sprintf(&pTextLineBuf[strlen(pTextLineBuf)], szOneSpace);
                }
                sprintf(&pTextLineBuf[strlen(pTextLineBuf)], szTwoSpaces);
            }

            PrintAscii(&pBuffer[0], elmsize,rem, &pTextLineBuf[strlen(pTextLineBuf)]);

            sprintf(&pTextLineBuf[strlen(pTextLineBuf)], "\n");
            pfnWriteStr(pTextLineBuf);
            pTextLineBuf[0] = '\0';
        }
    }
    
    free(pTextLineBuf);
    free(pBuffer);

    return 0;
}