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

@file PCIEList.c

@brief
    This module implements the PCI Header information in list format
@todo
*/
#include <stdio.h>
#include <stdlib.h>
#include "BYTPCIE.h"
#include "PCIEList.h"
//
////https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf
//http://pciids.sourceforge.net/v2.2/pci.ids
//http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf
//

extern CLASSCODE ClassCodes[]; ;/*! */
extern VENDORID VendorID[];

/*! 
    @fn void PCIEList(int bus, int dev, int fun, PCIEDUMPPARM *pDumpFun)

    @brief function list the PCIE function, bus,dev, class, subclass and device vendor

    @details
    
    @param[in] bus
    @param[in] dev
    @param[in] fun
    @param[in] *pDumpFun

    @return
*/
void PCIEList(int bus, int dev, int fun, PCIELISTPARM *pDumpFun) {

    char fFound;
    unsigned HeaderType, cls = 6/*class*/, sub = 0/*sub class*/, ifc = 0/*interface*/, c, s, i, v;
    unsigned *pPCIEReg32 = (unsigned *)((unsigned)pDumpFun->pciebase + (bus << 20) + (dev << 15) + (fun << 12) + 0);

    cls = 0xFF & pPCIEReg32[2] >> 24;
    sub = 0xFF & pPCIEReg32[2] >> 16;
    ifc = 0xFF & pPCIEReg32[2] >> 8;

    for (c = 0, fFound = 0; -1 != ClassCodes[c].nClass; c++) {

        if (cls == ClassCodes[c].nClass) {

            for (s = c; ClassCodes[c].nClass == ClassCodes[s].nClass; s++) {

                if (sub == ClassCodes[s].nSub) {

                    for (i = s; ClassCodes[s].nSub == ClassCodes[i].nSub; i++) {

                        if (ifc == ClassCodes[s].nIfc) {

                            fFound |= 4;
                        }
                        if (fFound)
                            break;
                    }
                    fFound |= 2;
                }
                if (fFound)
                    break;
            }
            fFound |= 1;
        }
        if (fFound)
            break;
    }

    for (v = 0; NULL != VendorID[v].szVendor; v++)
    {
        if ((unsigned)(pPCIEReg32[0] & 0xFFFF) == (unsigned)VendorID[v].wVendorID)
            break;
    }

    printf("Bus %02X, Dev %02X, Fun %02X: %s%s%s%s%s (%s)\n", bus, dev, fun,
           fFound & 1 ? ClassCodes[c].szBase : "unknown device",
           fFound & 2 ? "\\" : "",
           fFound & 2 ? ClassCodes[s].szSub : "",
           fFound & 4 ? "\\" : "",
           fFound & 4 ? ClassCodes[i].szIfc : "",
           VendorID[v].szVendor
    );

}
