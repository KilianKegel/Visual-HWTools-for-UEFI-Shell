/*!
@copyright

    Copyright (c) 2020 - 2023, Kilian Kegel. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file main.c

@brief 
    This module implements the PCIESpy main program
@todo
    - add /p page-by-page
    - add capability view
    - add /wr[8][16][32] to write a PCIe header

@mainpage
    PCIESpy for BayTrail(BYT)

@section intro_sec Introduction
    This program is used to view and manipulate PCIExpress devices on\n
    the Intel BayTrail(BYT) - Platform.\n

@subsection ref_sec References
    @note <a href="https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf">atom-e3800-family-datasheet-1522396.pdf</a>\n
    download BayTrail specification in external browser\n
    @par
    <a href="http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf">PCI 2.2 specification</a>\n
    <a href="https://cds.cern.ch/record/551427/files/cer-2308933.pdf">PCI-to-PCI Bridge Architecture Specification</a>\n
    <a href="http://pciids.sourceforge.net/v2.2/pci.ids">List of PCI ID's</a>\n
    @image html PCIExCover.png

@subsection Parm_sec Command line parameters
    1. no parameter: list all devices, show device class and vendor\n
    2. /dump[8][16][32] [bus dev fun] [/all] [/pcionly]: 8/16/32-bit hex-dump of bus, dev, fun\n
    3. /view [bus dev fun] [/all] : view bit fields of a particular PCIe function
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BYTPCIE.h"

extern CLASSCODE ClassCodes[]; ;/*! */
extern VENDORID VendorID[];

extern void PCIEView(int bus, int dev, int fun, PCIEVIEWPARM *pDumpFun);
//
// global variables
//
char gfALL = 0; /*!< all PCIe devices   */
char gfPCI = 0; /*!< PCI 256 header only*/
char gfPAGE = 0;/*!< page wise output   */

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
int chkcmdln(int argc, char **argv) {
    int nRet = 0;
    int i,j;
    int ihlp;
    static char *helpstr[] = {"/h","/help","/hlp","-h","-help","--h","--help", "/?","-?","--?" };

    for (i = 0, ihlp = 0 ; ihlp == 0 && i < argc ; i++)
        for(j = 0 ; ihlp == 0 && j < ELC(helpstr); j++)
            ihlp = (0 == strcmp(argv[i], helpstr[j]) ? i : 0);

    if(0 != ihlp)
    {
        printf( "    BayTrailPCIESpy w/o parameter : list all devices, show device class and vendor\n");
        printf( "    BayTrailPCIESpy /dump[8][16][32] [bus dev fun] : 8/16/32-bit hex-dump of a particular PCIe function\n" );
        printf( "    BayTrailPCIESpy /view [bus dev fun] : view bit fields of a particular PCIe function\n" );
        printf( "        additional /pcionly and /all can be used to limit to 256 headersize only\n        and to deal with all PCI devices.\n\n" );

        nRet = 1;
    }

    for (i = 0; i < argc; i++) 
        gfALL |= !strcmp("/all", argv[i]);
    for (i = 0; i < argc; i++) 
        gfPCI |= !strcmp("/pcionly", argv[i]);

    return nRet;
}


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
unsigned WriteString(IN char *pszLineOfText) 
{

    printf(pszLineOfText);

    return 0;
};

/*! 
    @fn int pciscan(void*pciebase,void (*pfnHandler)(int bus, int dev, int fun, void *pHandlerParm), void *pHandlerParm)

    @brief Scans the entire pci bus and invokes the collback function for each PCI function found

    @details 
        Only PCI functions behind root complex 0 is considered in that ipmlementation
    
    @param[in] *pciebase : PCIE base
    @param[in] pfnHandler : callback function
    @param[in] pHandlerParm : parameter pointer for the callback

    @return 0
*/
int pciscan(void*pciebase,void (*pfnHandler)(int bus, int dev, int fun, void *pHandlerParm), void *pHandlerParm) {
    int bus, dev, fun;
    
    for (bus = 0; bus < 256; bus++) {
        for (dev = 0; dev < 32; dev++) {
            for (fun = 0; fun < 8; fun++) {
                unsigned HeaderType;
                unsigned *pPCIEReg32 = (unsigned *)((unsigned)pciebase + (bus << 20) + (dev << 15) + (fun << 12) + 0);

                if ((unsigned)-1 == *pPCIEReg32)           // continue when no device found (0xFFFFFFFF)
                    continue;

                (*pfnHandler)(bus, dev, fun, pHandlerParm);  // invoke external handler 

                HeaderType = pPCIEReg32[3] >> 16;						// check header type ...

                if (fun == 0 && !(HeaderType & 0x80/*multi fun bit*/))		// ... if function 0 to be a multifuction device
                    break;//for(fun = 0 ; fun < 8 ; fun ++)					// ... continue with next device if not

            }
        }
    }//for (bus = 0; bus < 256; bus++)
    return 0;
}

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
    void *pciebase=NULL;
    char fPrintAll = 0;
    int i;
    int bus,dev,fun;
    int nRet = 0;
    PCIEVIEWPARM ViewFunParm = { pciebase };
  
    do {

//
// platform check - don't run program on non-BayTrail
// 
        outpd(0xCF8, 0x80000000 + (0 << 16) + (0 << 11) + (0 << 8) + 0);// get vendor/device ID
        
        if (0x0F008086 != inpd(0xCFC)) {
            printf("non-BayTrail\n");
            nRet = 1;
            break;
        }
        else {
//            printf("It's BayTrail...\n");
        }
//!
//! get the PCIE base from the message bus port 3, register 27h (BECREG from B-Unit message register)
//!

        outpd(0xCF8, 0x80000000 + (0 << 16) + (0x0 << 11) + (0 << 8) + 0xD0);
        outpd(0xCFC, (/*rdop*/0x10 << 24) + (3 << 16) + (0x27 << 8) + /*byte enable*/0xF);
        outpd(0xCF8, 0x80000000 + (0 << 16) + (0x0 << 11) + (0 << 8) + 0xD4);
        pciebase = (void*)(~3 & inpd(0xCFC));

        if (chkcmdln(argc, argv))
            break;                                            //break on help
//
// dump specific device - /dump8 /dump16 /dump32 == /dump
//      
        if (1) {
            char fDone = 0;
            for (i = 0; i < argc && 0 == fDone ; i++) {
                static struct {
                    char* pszCmdLine;
                    char  bDumpXYSizeMinusOne;
                    void* pfnDump81632;
                }dumpparm[] = {
                    { /*CommandLineString*/"/dump8" , /*size minus one */1 - 1, /*function to get element */&GetMem8 },
                    { /*CommandLineString*/"/dump16", /*size minus one */2 - 1, /*function to get element */&GetMem16 },
                    { /*CommandLineString*/"/dump32", /*size minus one */4 - 1, /*function to get element */&GetMem32 },
                    { /*CommandLineString*/"/dump"  , /*size minus one */4 - 1, /*function to get element */&GetMem32 }
                };
                int iDump;

                for (iDump = 0; iDump < ELC(dumpparm); iDump++) {

                    if (0 == strcmp(dumpparm[iDump].pszCmdLine, argv[i])) {
                        int bus, dev, fun;
                        UNIDUMPPARM hexparms = { .reg = 0, };
                        PCIEDUMPPARM DumpFunParm = { pciebase, &hexparms, dumpparm[iDump].pfnDump81632,gfPCI ? 256 : 4096 };

                        hexparms.bit.nAddrSize = 2;
                        hexparms.bit.elmsizemin1 = dumpparm[iDump].bDumpXYSizeMinusOne;

                        if (argc < i + 1 + 3/*bus,dev,fun*/) {
                            if (gfALL) {
                                
                                DumpFunParm.pfnDump81632 = dumpparm[iDump].pfnDump81632;
                                pciscan(pciebase,PCIEDump, &DumpFunParm);

                                fDone = 1;
                            }//if (0 == strcmp("/all", argv[i + 1])) 
                            else {
                                fprintf(stderr, "Missing bus dev fun parameter after /dumpXY");
                                fprintf(stdout, "\n");// fix new line bug of the shell
                                fDone = 1;
                            }
                            break;
                        }
                        sscanf(argv[i + 1], "%x", &bus);// get bus from the commandline
                        sscanf(argv[i + 2], "%x", &dev);// get dev from the commandline
                        sscanf(argv[i + 3], "%x", &fun);// get fun from the commandline

                        //UniDump(hexparms, gfPCI ? 256 : 4096, (unsigned long long)pciebase + (bus << 20) + (dev << 15) + (fun << 12) + 0, dumpparm[iDump].pfnDump81632, WriteString);
                        PCIEDump(bus, dev, fun, &DumpFunParm);
                        fDone = 1;
                    }
                }
            }

            if (fDone)
                break;
        }

//
// view a specific device or all
//
        if (1) {
            char fDone = 0;
            PCIEVIEWPARM ViewFunParm = { pciebase };

            for (i = 0; i < argc && 0 == fDone; i++) {
                static struct {
                    char* pszCmdLine;
                    char  bDumpXYSizeMinusOne;
                    void* pfnDump81632;
                }viewparm[] = {
                    { /*CommandLineString*/"/view" , /*size minus one */0, /*function to get element */NULL},
                };
                int x;

                for (x = 0; x < ELC(viewparm); x++) {

                    if (0 == strcmp(viewparm[x].pszCmdLine, argv[i])) {
                        int bus, dev, fun;

                        if (argc < i + 1 + 3/*bus,dev,fun*/) {
                            if (gfALL) {

                                pciscan(pciebase, PCIEView, &ViewFunParm);

                                fDone = 1;
                            }//if (0 == strcmp("/all", argv[i + 1])) 
                            else {
                                fprintf(stderr, "Missing bus dev fun parameter after /view");
                                fprintf(stdout, "\n");// fix new line bug of the shell
                                fDone = 1;
                            }
                            break;
                        }
                        sscanf(argv[i + 1], "%x", &bus);// get bus from the commandline
                        sscanf(argv[i + 2], "%x", &dev);// get dev from the commandline
                        sscanf(argv[i + 3], "%x", &fun);// get fun from the commandline

                        PCIEView(bus,dev,fun, &ViewFunParm);

                        fDone = 1;
                    }
                }
            }

            if (fDone)
                break;
        }

//
// list all, if no command line parameter
//
        if (argc == 1) {
            PCIEDUMPPARM DumpFunParm = { pciebase, NULL, NULL };
            pciscan(pciebase, PCIEList, &DumpFunParm);
        }

    } while (0);

    return nRet;
}
