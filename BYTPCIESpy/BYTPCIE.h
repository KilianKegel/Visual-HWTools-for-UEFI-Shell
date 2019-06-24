/*!
@copyright

    Copyright (c) 2019, MinnowWare. All rights reserved.
    This program and the accompanying materials are licensed and made 
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file 
    BYTPCIE.h

@brief 
    project specific header file
@todo
*/
#ifndef _BAYTRAIL_PCIE_H_
#define _BAYTRAIL_PCIE_H_

#pragma warning( disable : 4996 4311 4312 4101)

#include "..\includes\UniDump.h"
#include "PCIEList.h"
#include "PCIEView.h"
#include "PCIEDump.h"

#define ELC(x) (sizeof(x) / sizeof(x[0]))                                /*!< element count of an array*/

#define DEADLOOP(x) if(x){volatile int o = __LINE__;while(__LINE__ == o);}

#define IN
#define OUT
#define INOUT

typedef struct _CLASSCODE {
    int nClass;
    int nSub;
    int nIfc;
    char *szBase;
    char *szSub;
    char *szIfc;
}CLASSCODE;

typedef struct _VENDORID {
    unsigned short wVendorID;
    char *szVendor;
}VENDORID;

//typedef struct _DUMPFUNPARM {
//    void* pciebase;
//    UNIDUMPPARM *pHexParms;
//    void* pfnDump81632;
//    unsigned nElmCount;
//}PCIEDUMPPARM;

#endif//_BAYTRAIL_PCIE_H_
