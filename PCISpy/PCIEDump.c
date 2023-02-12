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

@file PCIEDump.c

@brief
    This module implements the PCI Header information in dump format
@todo
*/
#include <stdio.h>
#include <stdlib.h>
#include "..\includes\UniDump.h"
#include "BYTPCIE.h"

//
//https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf
//http://pciids.sourceforge.net/v2.2/pci.ids
//http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf
//

extern CLASSCODE ClassCodes[]; ;/*! */
extern VENDORID VendorID[];
extern unsigned WriteString(IN char *pszLineOfText);

/*! 
    @fn void PCIEDump(int bus, int dev, int fun, PCIEDUMPPARM *pDumpFun)

    @brief function dumps the entire PCIE function

    @details
    
    @param[in] bus
    @param[in] dev
    @param[in] fun
    @param[in] *pDumpFun

    @return
*/
void PCIEDump(int bus, int dev, int fun, PCIEDUMPPARM *pDumpFun) {

    printf("Bus 0x%X, dev 0x%X, fun 0x%X\n", bus, dev, fun);
    UniDump(*pDumpFun->pHexParms, pDumpFun->nElmCount, (unsigned long long)pDumpFun->pciebase + (bus << 20) + (dev << 15) + (fun << 12) + 0, pDumpFun->pfnDump81632, WriteString);

}

