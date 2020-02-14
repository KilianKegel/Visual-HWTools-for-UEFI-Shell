# SIODMP - generic SuperI/O dump
generic SuperI/O DUMP for all

## Introduction

This program is used to dump common SuperI/O chips, that can be unlocked by

`outb(baseadr,0x87)`<br>
`outb(baseadr,0x87)`

or

`outb(baseadr,0x55)`

at base address at `0x2E` or `0x4E`

## References
* [SuperI/O access](http://support.tenasys.com/helpdesk/index.php?pg=kb.page&id=140)

## Command line parameters

1. siodmp <dev>
2. siodmp /all
3. siodmp /info
