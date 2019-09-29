# Visual-HWTools-for-UEFI-Shell

## Goal
Demonstration off how to implement useful software tools to access
the Intel BayTrail (BYT) platform hardware or data structures directly or
by UEFI API.

The projects are kept small and simple to introduce the UEFI shell
programming using "ANSI C", easily and quickly.

## Approach
It is intended to use Visual Studio 2017 as the only development environment.
Furthermore it is intended to use ANSI-C library functions as far as possible.

Doing so, the UEFI Shell applications can be easily debugged
on the Windows development platform, simply by building the sourcecode
as a Win64-executable (change the solution configuration from Efi64 to Win64 ).

## HowTo
https://github.com/KilianKegel/HowTo-setup-an-UEFI-Development-PC#howto-setup-an-uefi-development-pc

## Revision history
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
