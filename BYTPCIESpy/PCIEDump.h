/*!
@copyright

    Copyright (c) 2020-2023, Kilian Kegel. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file 
    PCIEList.h

@brief 
    PCIEList specific header file
@todo
*/
#ifndef _PCIE_DUMP_H_
#define _PCIE_DUMP_H_

typedef struct _PCIEDUMPPARM {
    void* pciebase;
    UNIDUMPPARM *pHexParms;
    void* pfnDump81632;
    unsigned nElmCount;
}PCIEDUMPPARM;

typedef struct _REGDESC {
    int nFldPos;
    int nFldSize;
    char *pszFldTitle;
    char *rgszDesc[32];
}REGDESC;

void PCIEDump(int bus, int dev, int fun, PCIEDUMPPARM *pDumpFun);

#endif//_PCIE_DUMP_H_
