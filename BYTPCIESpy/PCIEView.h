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

@file 
    PCIEView.h

@brief 
    PCIEView specific header file
@todo
*/
#ifndef _PCIE_VIEW_H_
#define _PCIE_VIEW_H_

typedef struct _PCIEVIEWPARM {
    void* pciebase;
}PCIEVIEWPARM;

//typedef struct _REGDESC {
//    int nFldPos;
//    int nFldSize;
//    char *pszFldTitle;
//    char *rgszDesc[32];
//}REGDESC;


#endif//_PCIE_VIEW_H_
