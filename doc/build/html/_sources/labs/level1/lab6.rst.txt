.. _lab6:

A simple bootloader
###################

Purpose
=======
- Understand the memory map of ARC boards
- Understand the principles of bootloader and self-booting
- Understand the usage of shell commands in cmd
- Create a self-booting application


Equipment
=========
The following hardware and software tools are required:

* PC host
* ARC GNU toolchain/MetaWare Development Toolkit
* ARC board (EM Starter kit/IoT Development Kit)
* SD card
* |embarc| package
* ``example/baremetal/bootloader``

Content
========

1. Build and run the  ``example/baremetal/bootloader``
2. Download the generated ``bootloader.bin`` into flash
3. Build a self-boot applicaiton and boot it from SD card
4. Use the ntshell commands

Principles
==========

Memory Map of ARC board
-----------------------

|emsk|
**************
The available memory regions of |emsk| are shown below.

.. table:: Memory Map of |emsk|
   :widths: auto

   +------------------------+----------------------+---------------+
   |  Name                  | Start address        |  Size         |
   |                        |                      |               |
   +========================+======================+===============+
   | on-chip ICCM           | 0x00000000           |  256/128 KB   |
   +------------------------+----------------------+---------------+
   | on-chip DCCM           | 0x80000000           |  128 KB       |
   +------------------------+----------------------+---------------+
   | on-board DDR RAM       | 0x10000000           |  128 MB       |
   +------------------------+----------------------+---------------+

In this lab, the last 1 MB of DDR is reserved for the simple bootloader,
other memory regions are available for application.

|iotdk|
*****************
The available memory regions of |iotdk| are shown below.

.. table:: Memory Map of |iotdk|
   :widths: auto

   +------------------------+----------------------+-----------+
   |  Name                  | Start address        |  Size     |
   |                        |                      |           |
   +========================+======================+===========+
   | on-chip eflash         | 0x00000000           |  256 KB   |
   +------------------------+----------------------+-----------+
   | external boot SPI flash| 0x10000000           |  2 MB     |
   +------------------------+----------------------+-----------+
   | on-chip ICCM           | 0x20000000           |  256 KB   |
   +------------------------+----------------------+-----------+
   | on-chip SRAM           | 0x30000000           |  128 KB   |
   +------------------------+----------------------+-----------+
   | on-chip DCCM           | 0x80000000           |  128 KB   |
   +------------------------+----------------------+-----------+
   | on-chip XCCM           | 0xC0000000           |  32 KB    |
   +------------------------+----------------------+-----------+
   | on-chip YCCM           | 0xE0000000           |  32 KB    |
   +------------------------+----------------------+-----------+

In this lab, on-chip eflash and on-chip SRAM are reserved for the simple
bootloader, CCMs are reserved for application.

Boot of ARC board
-----------------

|emsk|
**************

The EMSK uses a Xilinx SPARTAN-6 FPGA part which can be configured to run
different members of the ARCv2 EM Processor family.  The EMSK includes a SPI
flash pre-programmed with four FPGA configurations of ARC EM cores.

When a “power on” or reset/configure is issued, the FPGA will auto-load one of
the pre-installed FPGA configurations from SPI flash. After the FPGA
configuration is loaded from the SPI flash, a simple primary bootloader is
loaded in ICCM.  Through the primary bootloader, an application can be loaded
from SPI Flash into ICCM or external DDR memory.

Considering that the SPI Flash is used to store FPGA images, the secondary
bootloader is designed based on the primary bootloader to load an application
from an SD card since it can be read and written easily. The startup sequence
is listed below:

1. Power on or reset event.

2. Load FPGA configuration from the SPI flash.

3. Run primary bootloader, which loads the secondary bootloader from the SPI Flash into main memory (DRAM).

4. Run secondary bootloader from main memory to load application from the SD card into ICCM/DRAM memory.

5. Run the application from ICCM/DRAM memory.

.. image:: /img/lab6_emsk_boot.png
    :alt: Boot sequence of EMSK


|iotdk|
*****************

|iotdk| can boot from on-chip eflash and extern boot SPI eflash, which is decided by
the FWU switch of IOTDK. When this switch is set of "off", the processor
starts executing the program stored in on-chip eflash; When this switch is set
of "on", the processor starts executing the program stored in external boot
SPI eflash;


How to flash the ARC board
--------------------------

|emsk|
**************

|iotdk|
*****************

Simple bootloader
-----------------

This simple bootloader is designed to work as a secondary/simple bootloader
for embARC, it will load boot.hex or boot.bin on SDCard and run that program.
And this example itself can be used as ntshell application.

The following features are provided in this simple bootloader:

* Boot application from SD card
* File operations on SD card
* UART Y-modem protocol to update application
* Operations on ARC processors

Steps
=====

1. Build and run the  ``example/baremetal/bootloader``

2. Download the generated ``bootloader.bin`` into flash

3. Build a self-boot applicaiton and boot it from SD card

4. Use the ntshell commands


Exercises
=========

1. Create and build a different self-boot embARC application
2. Use the ntshell commands
3. Use the UART-ymodem to load your application
