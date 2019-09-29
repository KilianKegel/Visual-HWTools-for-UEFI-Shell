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

@file 
    PCIEList.h

@brief 
    PCIEList specific header file
@todo
*/
#ifndef _PCIE_LIST_H_
#define _PCIE_LIST_H_

typedef struct _PCIELISTPARM {
    void* pciebase;
}PCIELISTPARM;

void PCIEList(int bus, int dev, int fun, PCIELISTPARM *pPcieList);

#endif//_PCIE_LIST_H_
