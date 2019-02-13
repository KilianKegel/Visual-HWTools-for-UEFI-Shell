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

@file PCIEView.c

@brief This module implements the PCI Header information translated for human readability

@details    NOTE: This modul is written quickly and is not deeply tested.
    

@todo
    add full 64 bit BAR support, don't just skip the [63:32] part
*/
#include <stdio.h>
#include <stdlib.h>
#include "BYTPCIE.h"
#include "PCIEList.h"
//
//https://www.intel.com/content/www/us/en/embedded/products/bay-trail/atom-e3800-family-datasheet.html
//http://pciids.sourceforge.net/v2.2/pci.ids
//http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf
//https://cds.cern.ch/record/551427/files/cer-2308933.pdf
//

extern CLASSCODE ClassCodes[]; ;/*! */
extern VENDORID VendorID[];

/*!
    @fn void PCIEDump(int bus, int dev, int fun, PCIEDUMPPARM *pPcieView)

    @brief function to translate PCIE function header to human readable information

    @details

    @param[in] bus
    @param[in] dev
    @param[in] fun
    @param[in] *pPcieView

    @return
*/
void PCIEView( int bus, int dev, int fun, PCIEVIEWPARM *pPcieView ) {

    volatile unsigned *pPCIEReg32 = (unsigned *)( (unsigned)pPcieView->pciebase + ( bus << 20 ) + ( dev << 15 ) + ( fun << 12 ) + 0 );
    PCIELISTPARM PcieListParm;

    PcieListParm.pciebase = pPcieView->pciebase;

    PCIEList( bus, dev, fun, &PcieListParm );//print device type and vendor

    if ( 1 ) {
        /*!
            vendor device ID, offset 0 DWORD 0 [31:0]
        */
        PCIELISTPARM ListFunParm ={ pPcieView->pciebase };
        int v;
        for ( v = 0; NULL != VendorID[v].szVendor; v++ )
        {
            if ( (unsigned)( pPCIEReg32[0] & 0xFFFF ) == (unsigned)VendorID[v].wVendorID )
                break;
        }
        printf( "Vendor ID: %04X (%s) Device ID: %04X\n", (unsigned)( pPCIEReg32[0] & 0xFFFF ), \
                NULL != VendorID[v].szVendor ? VendorID[v].szVendor : "unknown device vendor", \
                (unsigned)( pPCIEReg32[0] >> 16 ) );

    }


    if ( 2 ) {
        /*!
            CommandReg, offset 4, DWORD 1 [15:0]
        */
        int i;
        unsigned cmdreg = pPCIEReg32[1] & 0xFFFF;
        unsigned mask;
        unsigned fld;

        static REGDESC CommandReg[32] ={
            { 0,1,"    I/O Address Space Enable",{/*0*/"I/O decoder is disabled",/*1*/"I/O decoder is enabled" } },
            { 1,1,"    Mem Address Space Enable",{/*0*/"Mem decoder is disabled",/*1*/"Memdecoder is enabled" } },
            { 2,1,"    Bus Master Enable",{/*0*/"disabled",/*1*/"enabled" } },
            { 3,1,"    Special cycle Enable",{/*0*/"disabled",/*1*/"enabled" } },
            { 4,1,"    Mem write and Invalidate",{/*0*/"disabled",/*1*/"enabled" } },
            { 5,1,"    VGA Palette Snoop",{/*0*/"disabled",/*1*/"enabled" } },
            { 6,1,"    Parity Error Response",{/*0*/"disabled",/*1*/"enabled" } },
            { 7,1,"    IDSEL Stepping",{/*0*/"disabled",/*1*/"enabled" } },
            { 8,1,"    SERR Enable",{/*0*/"disabled",/*1*/"enabled" } },
            { 9,1,"    Fast Back-to-Back Enable",{/*0*/"disabled",/*1*/"enabled" } },
            { 10,1,"    Interrupt Disable",{/*0*/"enabled to generate INTx interrupt messages",/*1*/"disabled to generate INTx interrupt messages" } },
            { 0,0,NULL, },

        };
        printf( "CommandReg, offset 4, DWORD 1 [15:0]: 0x%04X\n", cmdreg );
        for ( i = 0; i < ELC( CommandReg ) && NULL != CommandReg[i].pszFldTitle; i++ ) {

            mask = 1 << CommandReg[i].nFldSize;
            mask--;
            fld = cmdreg >> CommandReg[i].nFldPos;
            fld &= mask;

            printf( "%s: %s\n", CommandReg[i].pszFldTitle, CommandReg[i].rgszDesc[fld] );

        }
    }

    if ( 3 ) {
        /*!
            StatusReg, offset 4, DWORD 1 [31:16]
        */
        int i;
        unsigned cmdreg = ( pPCIEReg32[1] >> 16 ) & 0xFFFF;
        unsigned mask;
        unsigned fld;

        static REGDESC StatusReg[32] ={  /*! Page 788 */
            { 3,1,"    Interrupt Status",{/*0*/"not active",/*1*/"active" } },
            { 4,1,"    Capability list",{/*0*/"N/A",/*1*/"available" } },
            { 5,1,"    66MHz-capable",{/*0*/"0",/*1*/"1" } },
            { 7,1,"    Fast Back-to-Back enable",{/*0*/"0",/*1*/"1" } },
            { 8,1,"    Master Data Parity Error",{/*0*/"0",/*1*/"1" } },
            { 9,2,"    DEVSEL Timing",{/*0*/"00",/*1*/"01","10","11" } },
            {11,1,"    Signaled abort",{/*0*/"0",/*1*/"1" } },
            {12,1,"    Received Target Abort",{/*0*/"0",/*1*/"1" } },
            {13,1,"    Received Master Abort",{/*0*/"0",/*1*/"1" } },
            {14,1,"    Signaled System Error (SERR)",{/*0*/"0",/*1*/"1" } },
            {15,1,"    Detected Parity Error",{/*0*/"0",/*1*/"1" } },
            {  0,0,NULL, },

        };
        printf( "StatusReg, offset 4, DWORD 1 [31:16]: 0x%04X\n", cmdreg );
        for ( i = 0; i < ELC( StatusReg ) && NULL != StatusReg[i].pszFldTitle; i++ ) {

            mask = 1 << StatusReg[i].nFldSize;
            mask--;
            fld = cmdreg >> StatusReg[i].nFldPos;
            fld &= mask;

            printf( "%s: %s\n", StatusReg[i].pszFldTitle, StatusReg[i].rgszDesc[fld] );

        }
    }
    printf( "Revision ID 0x%02X\n", pPCIEReg32[2] & 0xFF );        // page 771
    printf( "Cache Line Size 0x%02X\n", pPCIEReg32[3] & 0xFF );    // page 771
    printf( "Latency Timer 0x%02X\n", pPCIEReg32[3] >> 8 & 0xFF ); // page 771
    printf( "Header Type 0x%02X\n", pPCIEReg32[3] >> 16 & 0xFF );  // page 771
    printf( "BIST 0x%02X\n", pPCIEReg32[3] >> 20 & 0xFF );         // page 771

    printf( "Interrupt Pin: %d\n", pPCIEReg32[15] >> 8 & 0xFF );
    printf( 0xFF ==  (pPCIEReg32[15] >> 0 & 0xFF) ? "Interrupt Line: not assigned\n" : "Interrupt Line: %d\n", pPCIEReg32[15] >> 0 & 0xFF );

    if ( !( ( 3 << 16 ) & pPCIEReg32[3] ) )// Min_Gnt/Max_Gnt
    {
        printf( "Min_Gnt: %d\n", pPCIEReg32[15] >> 16 & 0xFF );
        printf( "Max_Gnt: %d\n", pPCIEReg32[15] >> 20 & 0xFF );
    }

    if ( 1 == ( ( 3 << 16 ) & pPCIEReg32[3] ) ){//bridge control
            /*!
                BridgeCtrlReg, DWORD 15 [31:16]
            */
            int i;
            unsigned cmdreg = ( pPCIEReg32[15] >> 16 ) & 0xFFFF;
            unsigned mask;
            unsigned fld;

            static REGDESC StatusReg[32] ={  /*! Page 835 */
                { 0,1,"    Parity Error Response",{/*0*/"0",/*1*/"1" } },
                { 1,1,"    SERR# (StatusSignaled System Error)Enable",{/*0*/"N/A",/*1*/"available" } },
                { 2,1,"    ISA enable in PCI",{/*0*/"0",/*1*/"1" } },
                { 3,1,"    VGA enable in PCI",{/*0*/"0",/*1*/"1" } },
                { 5,1,"    Master abort in PCI",{/*0*/"0",/*1*/"1" } },
                { 6,1,"    Secondary Bus Reset",{/*0*/"0",/*1*/"1"} },
                { 7,1,"    Fast Back-to-Back Enable PCI",{/*0*/"0",/*1*/"1" } },
                { 8,1,"    Primary Discard Timer PCI",{/*0*/"0",/*1*/"1" } },
                { 9,1,"    Secondary Discard Timer PCI",{/*0*/"0",/*1*/"1" } },
                { 10,1,"    Discard Timer PCI",{/*0*/"0",/*1*/"1" } },
                { 11,1,"    Discard Timer SERR# Enable PCI",{/*0*/"0",/*1*/"1" } },
                { 0,0,NULL, },
            };
            printf( "BridgeCtrlReg, DWORD 15 [31:16]: 0x%04X\n", cmdreg );
            for ( i = 0; i < ELC( StatusReg ) && NULL != StatusReg[i].pszFldTitle; i++ ) {

                mask = 1 << StatusReg[i].nFldSize;
                mask--;
                fld = cmdreg >> StatusReg[i].nFldPos;
                fld &= mask;

                printf( "%s: %s\n", StatusReg[i].pszFldTitle, StatusReg[i].rgszDesc[fld] );

            }
        }

    if ( !( ( 3 << 16 ) & pPCIEReg32[3] ) )// SubSys/Vendor only av. in headertype 0
    {
        int i;
        printf( "Subvendor ID: 0x%04X, Subsytem ID: 0x%04X\n",
                pPCIEReg32[11] & 0xFFFF,
                pPCIEReg32[11] >> 16 & 0xFFFF );                        // page 771

         /*!
             explore the 6 BARs
         */
        for ( i = 0; i < 6; i++ ) {
            unsigned dwAddress, dwSize, dwSizeKB, dwSizeMB;
            char fIOBar = 1 & pPCIEReg32[i + 4];
            char f64BitBar = 4 == ( 6 & pPCIEReg32[i + 4] );
            char fPrefetchBar = 8 == ( 8 & pPCIEReg32[i + 4] );
            unsigned Mask = ( fIOBar ? ~0x3 : ~0x7F );
            unsigned nMask = 0xFF & ~Mask;

            dwAddress = Mask & pPCIEReg32[i + 4];    // get address and mask non-address bits

            pPCIEReg32[i + 4] = (unsigned)-1;        // detct BAR ...

            dwSize=1 + ( ~Mask | ~pPCIEReg32[i + 4] );
            dwSize &= fIOBar ? 0xFFFF : (unsigned)-1;
            dwSizeKB = dwSize / 1024;
            dwSizeMB = dwSizeKB / 1024;

            pPCIEReg32[i + 4] = dwAddress;            //restore address
            if ( 1| dwAddress ) {
                printf( "BAR%d: Size 0x%08X(%u %sByte), Address 0x%08X %s%s%s\n",
                        i, dwSize,
                        dwSizeMB ? dwSizeMB : ( dwSizeKB ? dwSizeKB : dwSize ),
                        dwSizeMB ? "M" : ( dwSizeKB ? "k" : "" ),
                        dwAddress,
                        fIOBar ? " I/O" : "", f64BitBar ? " 64BitBar" : "", fPrefetchBar ? " Prefetch" : "" );
            }

            if ( f64BitBar )//just skip [63:32] of the 64Bit BAR
                i++;

        }

    }
    
    if ( 1 == ( ( 3 ) & pPCIEReg32[3] >> 16 ) )// explore the 2 bridge BARs
    {
        int i;
         /*!
             explore the 2 BARs
         */
        for ( i = 0; i < 2; i++ ) {
            unsigned dwAddress, dwSize, dwSizeKB, dwSizeMB;
            char fIOBar = 1 & pPCIEReg32[i + 4];
            char f64BitBar = 4 == ( 6 & pPCIEReg32[i + 4] );
            char fPrefetchBar = 8 == ( 8 & pPCIEReg32[i + 4] );
            unsigned Mask = ( fIOBar ? ~0x3 : ~0x7F );
            unsigned nMask = 0xFF & ~Mask;

            dwAddress = Mask & pPCIEReg32[i + 4];    // get address and mask non-address bits

            pPCIEReg32[i + 4] = (unsigned)-1;        // detct BAR ...

            dwSize=1 + ( ~Mask | ~pPCIEReg32[i + 4] );
            dwSize &= fIOBar ? 0xFFFF : (unsigned)-1;
            dwSizeKB = dwSize / 1024;
            dwSizeMB = dwSizeKB / 1024;

            pPCIEReg32[i + 4] = dwAddress;            //restore address
            if ( 1 | dwAddress ) {
                printf( "BAR%d: Size 0x%08X(%u%sByte), Address 0x%08X %s%s%s\n",
                        i, dwSize,
                        dwSizeMB ? dwSizeMB : ( dwSizeKB ? dwSizeKB : dwSize ),
                        dwSizeMB ? "M" : ( dwSizeKB ? "k" : "" ),
                        dwAddress,
                        fIOBar ? " I/O" : "", f64BitBar ? " 64BitBar" : "", fPrefetchBar ? " Prefetch" : "" );
            }

            if ( f64BitBar )//just skip [63:32] of the 64Bit BAR
                i++;

        }


    }
    
    if ( 1 == ( ( 3 ) & pPCIEReg32[3] >> 16 ) )// explore io/mem/prefetch base/limit registers
    {
        /*!
            explore io/mem/prefetch base/limit registers
        */
        int i;
        unsigned short IOBase, IOLimit, IOSize;
        unsigned MEMBase, MEMLimit, MEMSize, MEMSizeKB, MEMSizeMB;
        unsigned PREBase, PRELimit, PRESize, PRESizeKB, PRESizeMB;
                
        IOBase  = (pPCIEReg32[7] >>  0 & ~0xF) << 8;
        IOLimit = (pPCIEReg32[7] >>  8 & ~0xF) << 8;
        if ( IOBase > IOLimit )
            IOBase = IOLimit = IOSize = 0;
        else
            IOSize = ( IOLimit | 0xFFF ) - IOBase + 1;
        
        MEMBase = (pPCIEReg32[8] >>  0 & ~0xF) << 16;
        MEMLimit= (pPCIEReg32[8] >> 16 & ~0xF) << 16;
        if ( MEMBase > MEMLimit )
            MEMBase = MEMLimit = MEMSize = 0;
        else
            MEMSize = ( MEMLimit | 0xFFFFF ) - MEMBase + 1;

        PREBase = (pPCIEReg32[9] >>  0 & ~0xF) << 16;
        PRELimit= (pPCIEReg32[9] >> 16 & ~0xF) << 16;
        if ( PREBase > PRELimit )
            PREBase = PRELimit = PRESize = 0;
        else
            PRESize = ( PRELimit | 0xFFFFF ) - PREBase + 1;
        
        MEMSizeKB = MEMSize / 1024;
        MEMSizeMB = MEMSizeKB / 1024;

        PRESizeKB = PRESize / 1024;
        PRESizeMB = PRESizeKB / 1024;

        //printf( "IOBase  =%04X, Size %04X(%d)\n", IOBase, ( IOLimit | 0xFFF ) - IOBase + 1 );
        ////printf( "IOLimit =%04X\n", IOLimit);
        //printf( "MEMBase =%08X, Size %08X\n", MEMBase, ( MEMLimit | 0xFFFFF ) - MEMBase + 1 );
        ////printf( "MEMLimit=%08X\n", MEMLimit);
        //printf( "PREBase =%08X, Size %08X\n", PREBase, ( PRELimit | 0xFFFFF ) - PREBase + 1 );
        ////printf( "PRELimit=%08X\n", PRELimit);

        printf( "IOBase : Size 0x%08X(%uByte), Address 0x%08X\n", IOSize, IOSize, IOBase );
        printf( "MEMBase: Size 0x%08X(%u%sByte), Address 0x%08X\n", MEMSize,
                MEMSizeMB ? MEMSizeMB: ( MEMSizeKB ? MEMSizeKB : MEMSize ),
                MEMSizeMB ? "M" : ( MEMSizeKB ? "k" : "" ),
                MEMBase );
        printf( "PREMEMBase: Size 0x%08X(%u%sByte), Address 0x%08X\n", PRESize,
                PRESizeMB ? PRESizeMB: ( PRESizeKB ? PRESizeKB : PRESize ),
                PRESizeMB ? "M" : ( PRESizeKB ? "k" : "" ),
                PREBase );



    }
    printf( "\n" );
}
