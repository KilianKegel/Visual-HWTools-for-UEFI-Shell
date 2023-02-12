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

@file ClassCodes.c

@brief 
    This module implements the ClassCode to string translation table
@todo
*/
#include <stdio.h>
#include <stdlib.h>
#include "BYTPCIE.h"
//
//https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf
//http://pciids.sourceforge.net/v2.2/pci.ids
//http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf
//

CLASSCODE ClassCodes[] = {
    { 0,0x00,  -1,"Unclassified","Non-VGA-comp. devices", NULL },
    { 0,0x01,  -1,"Unclassified","VGA-comp. Dev", NULL },
    { 1,0x00,  -1,"Mass Storage Ctrl","SCSI Bus Ctrl", NULL },
    { 1,0x01,0x00,"Mass Storage Ctrl","IDE Ctrl ", "ISA comp mode - only controller" },
    { 1,0x01,0x05,"Mass Storage Ctrl","IDE Ctrl ", "PCI native mode - only controller" },
    { 1,0x01,0x0A,"Mass Storage Ctrl","IDE Ctrl ", "ISA comp mode controller, supports both channels switched to PCI native mode" },
    { 1,0x01,0x0F,"Mass Storage Ctrl","IDE Ctrl ", "PCI native mode controller, supports both channels switched to ISA compatibility mode" },
    { 1,0x01,0x80,"Mass Storage Ctrl","IDE Ctrl ", "ISA comp mode - only controller, supports bus mastering" },
    { 1,0x01,0x85,"Mass Storage Ctrl","IDE Ctrl ", "PCI native mode - only controller, supports bus mastering" },
    { 1,0x01,0x8A,"Mass Storage Ctrl","IDE Ctrl ", "ISA comp mode controller, supports both channels switched to PCI native mode, supports bus mastering" },
    { 1,0x01,0x8F,"Mass Storage Ctrl","IDE Ctrl ", "PCI native mode controller, supports both channels switched to ISA compatibility mode, supports bus mastering" },
    { 1,0x02,  -1,"Mass Storage Ctrl","Floppy Disk Ctrl",NULL },
    { 1,0x03,  -1,"Mass Storage Ctrl","IPI Bus Ctrl",NULL },
    { 1,0x04,  -1,"Mass Storage Ctrl","RAID Ctrl",NULL },
    { 1,0x05,0x20,"Mass Storage Ctrl","ATA Ctrl","Single DMA" },
    { 1,0x05,0x20,"Mass Storage Ctrl","ATA Ctrl","Chained DMA" },
    { 1,0x06,0x00,"Mass Storage Ctrl","Ser.ATA","Vendor Specific Interface" },
    { 1,0x06,0x01,"Mass Storage Ctrl","Ser.ATA","AHCI 1.0" },
    { 1,0x06,0x02,"Mass Storage Ctrl","Ser.ATA","Ser.Storage Bus" },
    { 1,0x07,0x00,"Mass Storage Ctrl","Ser.Attached SCSI","SAS" },
    { 1,0x07,0x01,"Mass Storage Ctrl","Ser.Attached SCSI","Ser.Storage Bus" },
    { 1,0x08,0x01,"Mass Storage Ctrl","Non-Volatile Memory Ctrl", "NVMHCI" },
    { 1,0x08,0x02,"Mass Storage Ctrl","Non-Volatile Memory Ctrl", "NVM Express" },
    { 1,0x80,  -1,"Mass Storage Ctrl","Non-Volatile Memory Ctrl", "NVM Express" },
    { 2,0x00,  -1,"Network Ctrl","Ethernet Ctrl",NULL },
    { 2,0x01,  -1,"Network Ctrl","Token Ring Ctrl",NULL },
    { 2,0x02,  -1,"Network Ctrl","FDDI Ctrl",NULL },
    { 2,0x03,  -1,"Network Ctrl","ATM Ctrl",NULL },
    { 2,0x04,  -1,"Network Ctrl","ISDN Ctrl",NULL },
    { 2,0x05,  -1,"Network Ctrl","WorldFip Ctrl",NULL },
    { 2,0x06,  -1,"Network Ctrl","PICMG 2.14 Multi Computing",NULL },
    { 2,0x07,  -1,"Network Ctrl","Infiniband Ctrl",NULL },
    { 2,0x08,  -1,"Network Ctrl","Fabric Ctrl",NULL },
    { 2,0x80,  -1,"Network Ctrl","Other Network Ctrl",NULL },
    { 3,0x00,0x00,"Display Ctrl","VGA comp. Ctrl","VGA Ctrl" },
    { 3,0x00,0x01,"Display Ctrl","VGA comp. Ctrl","8514 - comp. Ctrl" },
    { 3,0x01,  -1,"Display Ctrl","XGA Ctrl",NULL },
    { 3,0x02,  -1,"Display Ctrl","3D Ctrl(Not VGA - comp.)",NULL },
    { 3,0x80,  -1,"Display Ctrl","Other Display Ctrl",NULL },
    { 4,0x00,  -1,"Multimedia Ctrl","Multimedia Video Ctrl",NULL },
    { 4,0x01,  -1,"Multimedia Ctrl","Multimedia Audio Ctrl",NULL },
    { 4,0x02,  -1,"Multimedia Ctrl","Computer Telephony Dev",NULL },
    { 4,0x03,  -1,"Multimedia Ctrl","Audio Dev",NULL },
    { 4,0x80,  -1,"Multimedia Ctrl","Other Multimedia Ctrl",NULL },
    { 5,0x00,  -1,"Memory Ctrl","RAM Ctrl",NULL },
    { 5,0x01,  -1,"Memory Ctrl","Flash Ctrl",NULL },
    { 5,0x80,  -1,"Memory Ctrl","Other Memory Ctrl",NULL },
    { 6,0x00,  -1,"Bridge Dev","Host Bridge",NULL },
    { 6,0x01,  -1,"Bridge Dev","ISA Bridge",NULL },
    { 6,0x02,  -1,"Bridge Dev","EISA Bridge",NULL },
    { 6,0x03,  -1,"Bridge Dev","MCA Bridge",NULL },
    { 6,0x04,0x00,"Bridge Dev","PCI2PCI Bridge","Positive Decode" },
    { 6,0x04,0x01,"Bridge Dev","PCI2PCI Bridge","Subtractive Decode" },
    { 6,0x05,  -1,"Bridge Dev","PCMCIA",NULL },
    { 6,0x06,  -1,"Bridge Dev","NuBus Bridge",NULL },
    { 6,0x07,  -1,"Bridge Dev","CardBus Bridge",NULL },
    { 6,0x08,0x00,"Bridge Dev","RACEway Bridge","Transparent Mode" },
    { 6,0x08,0x01,"Bridge Dev","RACEway Bridge","Endpoint Mode" },
    { 6,0x09,0x40,"Bridge Dev","PCI2PCI Bridge","Semi-Transparent, Primary bus towards host CPU" },
    { 6,0x09,0x80,"Bridge Dev","PCI2PCI Bridge","Semi-Transparent, Secondary bus towards host CPU" },
    { 6,0x0A,  -1,"Bridge Dev"," InfiniBand-to-PCI Host Bridge",NULL },
    { 6,0x80,  -1,"Bridge Dev","Other Bridge Dev",NULL },
    { 7,0x00,0x00,"Simple Comm Ctrl","Ser.Ctrl","8250" },
    { 7,0x00,0x01,"Simple Comm Ctrl","Ser.Ctrl","16450" },
    { 7,0x00,0x02,"Simple Comm Ctrl","Ser.Ctrl","16550" },
    { 7,0x00,0x03,"Simple Comm Ctrl","Ser.Ctrl","16650" },
    { 7,0x00,0x04,"Simple Comm Ctrl","Ser.Ctrl","16750" },
    { 7,0x00,0x05,"Simple Comm Ctrl","Ser.Ctrl","16850" },
    { 7,0x00,0x06,"Simple Comm Ctrl","Ser.Ctrl","16950" },
    { 7,0x01,0x00,"Simple Comm Ctrl","Par. Ctrl","Standard Par. Port" },
    { 7,0x01,0x01,"Simple Comm Ctrl","Par. Ctrl","Bi - Directional Par. Port" },
    { 7,0x01,0x02,"Simple Comm Ctrl","Par. Ctrl","ECP 1.X Compliant Par. Port" },
    { 7,0x01,0x03,"Simple Comm Ctrl","Par. Ctrl","IEEE 1284 Ctrl" },
    { 7,0x01,0xFE,"Simple Comm Ctrl","Par. Ctrl","IEEE 1284 Target Dev" },
    { 7,0x02,  -1,"Simple Comm Ctrl","Multiport Ser.Ctrl",NULL },
    { 7,0x03,0x00,"Simple Comm Ctrl","Modem""Generic Modem" },
    { 7,0x03,0x01,"Simple Comm Ctrl","Modem""Hayes 16450" },
    { 7,0x03,0x02,"Simple Comm Ctrl","Modem""Hayes 16550" },
    { 7,0x03,0x03,"Simple Comm Ctrl","Modem""Hayes 16650" },
    { 7,0x03,0x04,"Simple Comm Ctrl","Modem""Hayes 16750" },
    { 7,0x04,  -1,"Simple Comm Ctrl","IEEE 488.1/2 (GPIB) Ctrl",NULL },
    { 7,0x05,  -1,"Simple Comm Ctrl","Smart Card",NULL },
    { 7,0x80,  -1,"Simple Comm Ctrl","Other Simple Comm Ctrl",NULL },
    { 8,0x00,0x00,"Base System Periph.","PIC","Generic 8259 - comp." },
    { 8,0x00,0x01,"Base System Periph.","PIC","ISA - comp." },
    { 8,0x00,0x02,"Base System Periph.","PIC","EISA - comp." },
    { 8,0x00,0x10,"Base System Periph.","PIC","I / O APIC Interrupt Ctrl" },
    { 8,0x00,0x20,"Base System Periph.","PIC","I / O(x) APIC Interrupt Ctrl" },
    { 8,0x01,0x00,"Base System Periph.","DMA","Generic 8237 - comp." },
    { 8,0x01,0x01,"Base System Periph.","DMA","ISA - comp." },
    { 8,0x01,0x02,"Base System Periph.","DMA","EISA - comp." },
    { 8,0x02,0x00,"Base System Periph.","Timer","Generic 8254 - comp." },
    { 8,0x02,0x01,"Base System Periph.","Timer","ISA - comp." },
    { 8,0x02,0x02,"Base System Periph.","Timer","EISA - comp." },
    { 8,0x02,0x03,"Base System Periph.","Timer","HPET" },
    { 8,0x03,0x00,"Base System Periph.","RTC","Generic RTC" },
    { 8,0x03,0x01,"Base System Periph.","RTC","ISA - comp." },
    { 8,0x04,  -1,"Base System Periph.","PCI Hot - Plug Ctrl",NULL },
    { 8,0x05,  -1,"Base System Periph.","SD Host controller",NULL },
    { 8,0x06,  -1,"Base System Periph.","IOMMU",NULL },
    { 8,0x80,  -1,"Base System Periph.","Other Base System Periph.",NULL },
    { 9,0x00,  -1,"Input Dev Ctrl","Keyboard Ctrl",NULL },
    { 9,0x01,  -1,"Input Dev Ctrl","Digitizer Pen",NULL },
    { 9,0x02,  -1,"Input Dev Ctrl","Mouse Ctrl",NULL },
    { 9,0x03,  -1,"Input Dev Ctrl","Scanner Ctrl",NULL },
    { 9,0x04,0x00,"Input Dev Ctrl","Gameport Ctrl","Generic" },
    { 9,0x04,0x10,"Input Dev Ctrl","Gameport Ctrl","Extended" },
    { 9,0x80,  -1,"Input Dev Ctrl","Other Input Dev Ctrl",NULL },
    { 10,0x00,  -1,"Docking Station","Generic",NULL },
    { 10,0x80,  -1,"Docking Station","Other Docking Station",NULL },
    { 11,0x00,  -1,"CPU","386",NULL },
    { 11,0x01,  -1,"CPU","486",NULL },
    { 11,0x02,  -1,"CPU","Pentium",NULL },
    { 11,0x10,  -1,"CPU","Alpha",NULL },
    { 11,0x20,  -1,"CPU","PowerPC",NULL },
    { 11,0x30,  -1,"CPU","MIPS",NULL },
    { 11,0x40,  -1,"CPU","Co - Processor",NULL },
    { 12,0x00,0x00,"Ser.Bus Ctrl","IEEE 1394","Generic" },
    { 12,0x00,0x01,"Ser.Bus Ctrl","IEEE 1394","OHCI" },
    { 12,0x01,  -1,"Ser.Bus Ctrl","ACCESS Bus",NULL },
    { 12,0x02,  -1,"Ser.Bus Ctrl","SSA",NULL },
    { 12,0x03,0x00,"Ser.Bus Ctrl","USB","UHCI Ctrl" },
    { 12,0x03,0x10,"Ser.Bus Ctrl","USB","OHCI Ctrl" },
    { 12,0x03,0x20,"Ser.Bus Ctrl","USB","EHCI(USB2) Ctrl" },
    { 12,0x03,0x30,"Ser.Bus Ctrl","USB","XHCI(USB3) Ctrl" },
    { 12,0x03,0x80,"Ser.Bus Ctrl","USB","Unspecified" },
    { 12,0x03,0xFE,"Ser.Bus Ctrl","USB","USB Dev(Not a host controller)" },
    { 12,0x04,  -1,"Ser.Bus Ctrl","Fibre Channel",NULL },
    { 12,0x05,  -1,"Ser.Bus Ctrl","SMBus",NULL },
    { 12,0x06,  -1,"Ser.Bus Ctrl","InfiniBand",NULL },
    { 12,0x07,0x00,"Ser.Bus Ctrl","IPMI Interface","SMIC" },
    { 12,0x07,0x01,"Ser.Bus Ctrl","IPMI Interface","Keyboard Ctrl Style" },
    { 12,0x07,0x02,"Ser.Bus Ctrl","IPMI Interface","Block Transfer" },
    { 12,0x08,  -1,"Ser.Bus Ctrl","SERCOS Interface (IEC 61491) ",NULL },
    { 12,0x09,  -1,"Ser.Bus Ctrl","CAN Bus",NULL },
    { 13,0x00,  -1,"Wireless Ctrl","iRDA comp. Ctrl",NULL },
    { 13,0x01,  -1,"Wireless Ctrl","Consumer IR Ctrl",NULL },
    { 13,0x10,  -1,"Wireless Ctrl","RF Ctrl",NULL },
    { 13,0x11,  -1,"Wireless Ctrl","Bluetooth Ctrl",NULL },
    { 13,0x12,  -1,"Wireless Ctrl","Broadband Ctrl",NULL },
    { 13,0x20,  -1,"Wireless Ctrl","Ethernet Ctrl(802.1a)",NULL },
    { 13,0x21,  -1,"Wireless Ctrl","Ethernet Ctrl(802.1b)",NULL },
    { 13,0x80,  -1,"Wireless Ctrl","Other Wireless Ctrl",NULL },
    { 14,0x00,  -1,"Intelligent Ctrl","I2O",NULL },
    { 15,0x01,  -1,"Sattelite Comm Ctrl","Satellite TV Ctrl",NULL },
    { 15,0x02,  -1,"Sattelite Comm Ctrl","Satellite Audio Ctrl",NULL },
    { 15,0x03,  -1,"Sattelite Comm Ctrl","Satellite Voice Ctrl",NULL },
    { 15,0x04,  -1,"Sattelite Comm Ctrl","Satellite Data Ctrl",NULL },
    { 16,0x00,  -1,"Enc.Ctrl","Network and Computing Encrpytion / Decryption",NULL },
    { 16,0x10,  -1,"Enc.Ctrl","Entertainment Enc./ Decryption",NULL },
    { 16,0x80,  -1,"Enc.Ctrl","Other Enc./ Decryption",NULL },
    { 17,0x00,  -1,"DSP","DPIO Modules",NULL },
    { 17,0x01,  -1,"DSP","Performance Counters",NULL },
    { 17,0x10,  -1,"DSP","Comm Synchronizer",NULL },
    { 17,0x20,  -1,"DSP","Signal Processing Management",NULL },
    { 17,0x80,  -1,"DSP","Other DSP",NULL },
    { 0x12,  -1,  -1,"Processing Accelerator",NULL,NULL },
    { 0x13,  -1,  -1,"Non - Essential Instrumentation",NULL,NULL },
    { 0x40,  -1,  -1,"Co - Processor",NULL,NULL },
    { 0xFF,  -1,  -1,"Unassigned Class",NULL,NULL },
    {   -1,  -1,  -1,NULL,NULL,NULL },
};