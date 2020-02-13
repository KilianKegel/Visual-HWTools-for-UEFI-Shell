# Visual-HWTools-for-UEFI-Shell

## Goal
Demonstration off how to implement useful software tools to access
the Intel BayTrail (BYT) platform hardware or data structures directly or
by UEFI API.

The projects are kept small and simple to introduce the UEFI shell
programming using "ANSI C", easily and quickly.

## Approach
It is intended to use Visual Studio 2019 as the only development environment.
Furthermore it is intended to use ANSI-C library functions as far as possible.

Doing so, the UEFI Shell applications can be easily debugged
on the Windows development platform, simply by building the sourcecode
as a Win64-executable (change the solution configuration from Efi64 to Win64 ).

## Projects/Tools
[BYTGPIOSpy](BYTGPIOSpy) -> GPIO Spy for Baytrail<br>
[BYTPCIESpy](BYTPCIESpy) -> PCIEx Spy for Baytrail<br>
[MEMSpy](MEMSpy) -> memory dump, write, fill... <br>
[PCISpy](PCISpy)-> PCI dump, write, decode... <br>
[Vmode](Vmode) -> video mode list, switch<br>
### simple tools / one trick ponies
[iowr16](iowr16) -> I/O write word<br>
[iowr32](iowr32) -> I/O write dword<br>
[iowr8](iowr8) -> I/O write byte<br>
[memwr16](memwr16) -> mem write word<br>
[memwr32](memwr32) -> mem write dword<br>
[memwr64](memwr64) -> mem write qword<br>
[memwr8](memwr8) -> mem write byte<br>
[iodmp16](iodmp16) -> I/O dump word<br>
[iodmp32](iodmp32) -> I/O dump dword<br>
[iodmp8](iodmp8) -> I/O dump byte<br>
[memdmp16](memdmp16) -> memory dump word<br>
[memdmp32](memdmp32) -> memory dump dword<br>
[memdmp64](memdmp64) -> memory dump qword<br>
[memdmp8](memdmp8) -> memory dump byte<br>
[rtcdmp](rtcdmp) -> RTC Real Time Clock dump<br>

## HowTo
https://github.com/KilianKegel/HowTo-setup-an-UEFI-Development-PC#howto-setup-an-uefi-development-pc

## Revision history
https://github.com/KilianKegel/torito-C-Library#revision-history

### 20200213
* add simple tools for memory and I/O access + RTC
### 20200210
* add PCISPY sample
* update various document links
### 20200204/R154
* Update to torito-C 20200204/R154
* adjust solution configurations
* update copyright
### 20201224/R152
* Update to torito-C 20191126/R152
* add VMODE tool, to list GOP video modes and to change video mode
* update to VS2019 ver 16.4.2
### 20191018/R141
* update Torito C Library https://github.com/KilianKegel/torito-C-Library#20191017r141
### 20190929
* update to Torito C Library ver. R138
* update copyright

### 20190917
* update to VS2019 Version 16.2.4 (Spectre Support)
* allow build in all 3 solution configurations: Efi, Win64(Torito C) and Wind64(Microsoft)

### 20190624
* add MEMSpy
* update Torito C Library to version 20190621/R133

### 20190213/2 - bugfix, update
* add missing include file
* add HowTo
* update to latest Windows 10 SDK 10.0.17763.0

### 20190213 - initial revision
* BayTrailGPIOSpy
* BayTrailPCIESpy
