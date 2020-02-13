# PCISpy - PCI Spy

## Introduction

This program is used to view and manipulate PCI devices on
all PC platforms.

## References
* [atom-e3800-family-datasheet-1522396.pdf](https://www.mouser.com/datasheet/2/612/atom-e3800-family-datasheet-1522396.pdf)
* [MinnowBoard Firmware](https://software.intel.com/en-us/articles/minnowboard-maxturbot-uefi-firmware)
* [PCI 2.2 specification](http://www.ics.uci.edu/~harris/ics216/pci/PCI_22.pdf)
* [PCI-to-PCI Bridge Architecture Specification](https://cds.cern.ch/record/551427/files/cer-2308933.pdf)
* [List of PCI ID's](http://pciids.sourceforge.net/v2.2/pci.ids)

## Command line parameters

1. no parameter: list all devices, show device class and vendor
2. /dump[8][16][32] [bus dev fun] [/all] [/pcionly]: 8/16/32-bit hex-dump of bus, dev, fun
3. /view [bus dev fun] [/all] : view bit fields of a particular PCIe function 

### Todo
1. add *PCI write* support