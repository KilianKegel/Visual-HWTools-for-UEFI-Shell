# MEMSpy - MemorySpy

## Introduction

This program is used to dump and write/fill system memory


## References
* [atom-e3800-family-datasheet-1522396.pdf](https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf)
* [MinnowBoard Firmware](https://software.intel.com/en-us/articles/minnowboard-maxturbot-uefi-firmware)
* [PCI 2.2 specification](http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf)
* [PCI-to-PCI Bridge Architecture Specification](https://cds.cern.ch/record/551427/files/cer-2308933.pdf)
* [List of PCI ID's](http://pciids.sourceforge.net/v2.2/pci.ids)

## Command line parameters

1. /dump[8][16][32][64] hexaddress: 8/16/32/64-bit hex-dump of memory
2. /fill[8][16][32][64] hexaddress hexvalue [hexcount]: write value to memory 
