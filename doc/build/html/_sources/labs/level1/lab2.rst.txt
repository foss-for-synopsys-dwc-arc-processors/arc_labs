.. _lab2:

How to use |embarc|
#####################

Purpose
=======
* To know what |embarc| is
* To know how to run the provided examples in |embarc|
* To know how to debug the provided examples in |embarc|
* To know how to do application development in |embarc|

Equipment
=========

The following hardware and software tools are required:

* PC host
* ARC GNU toolchain/MetaWare Development Toolkit
* ARC board (EM Starter kit/IoT Development Kit)
* |embarc| packages

The detailed software requirements of |embarc| can be found `here <http://embarc.org/embar
c_osp/doc/build/html/getting_started/software_requirement.html>`__

Content
========

First, a brief introduction of |embarc| will be made and also how to get it.
Then, you will get to how to run the provided examples and debug them. Finally, you
can try to create your own embARC applications.


Principles
==========

1. IoT OS/Platform

As more and more devices are connected and become more complex, the software
running in them are becoming more and more complex.

An IoT OS is an operating system that is designed to perform within the
constraints that are particular to Internet of Things devices, including
restrictions on memory, size, power and processing capacity. IoT operating
systems are a type of embedded OS but by definition are designed to enable
data transfer over the internet and more other features.

2. |embarc|

The embARC Open Software Platform (OSP) is an open software platform to
facilitate the development of embedded systems based on |arc|.

It is designed to provide a unified platform for |arc| users by defining
consistent and simple software interfaces to the processor and peripherals,
together with ports of several well known FOSS embedded software stacks to
|arc|.

For more details, please go to |embarc| `on-line documentation <http://embar
c.org/embarc_osp/doc/build/html/introduction/introduction.html>`__


3. Other platforms

Besides |embarc|, there are also other IoT platforms:

* `Zephyr <https://www.zephyrproject.org/>`__
* `Amazon FreeRTOS <https://aws.amazon.com/freertos/>`__

Steps
=====

Get |embarc|
**************

* git

The |embarc| source code is hosted in a `GitHub repository <https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp>`__.
There are scripts and such in this repo that you'll need to set up your development environment, and we'll be using Git to get this repo. If you don't have Git installed, see the beginning of the OS-specific instructions below for help.

We'll begin by using Git to clone the repository anonymously.

.. code-block:: console

   # On Windows
   cd %userprofile%
   # On Linux
   cd ~

   git clone https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp.git embarc_osp

Then you will have checked out a copy of the source code to your local machine.

* http download

If you are not familiar with git, you can also try to get the latest release of embarc as a zip from
the repository, see `release page <https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp/releases>`__.

Run the examples
****************

The command line interface is the default interface to use |embarc|. After getting the |embarc|
package, you need to open a **cmd** console in Winodws / a **terminal** in Linux and cd to the root of embARC osp.

Here, take the **blinky** as an example.

1. go to the **blinky** example folder

.. code-block:: console

   cd example\baremetal\blinky

2. connect your board to PC host, and open the UART terminal with putty/tera term/minicom

3. build and run it with command showing below, here ARC GNU toolchain is selected

.. code-block:: console

   # For EMSK 2.3
   make TOOLCHAIN=gnu BOARD=emsk BD_VER=23 CUR_CORE=arcem11d run
   # For EMSK 2.2
   make TOOLCHAIN=gnu BOARD=emsk BD_VER=22 CUR_CORE=arcem7d run
   # For IoTDK
   make TOOLCHAIN=gnu BOARD=iotdk run

.. note:: for EMSK, please make sure the board version (BD_VER) and core configuration (CUR_CORE) match your hardware.
  You could press configure button (located above the letter “C” of the ARC logo) when bit 3 and bit 4 of SW1 switch is off to run a self-test. By doing so, board infomation will be sent by uart and shown on your uart terminal.


4. Get the results

* For EMSK, you can see the on-board leds start to blink when the download is successful.

* For IoTDK, as it doesn't have usable leds except some status leds, you will the output log from UART instead.

.. code-block:: console

    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    led out: ff00, ff
    led out: ff, ff
    .................

Debug the examples
******************

Still take the **blinky** as example, to debug it, you need to run the following commands:

.. code-block:: console

   # For emsk 2.3
   make TOOLCHAIN=gnu BOARD=emsk BD_VER=23 CUR_CORE=arcem11d gui
   # For emsk 2.2
   make TOOLCHAIN=gnu BOARD=emsk BD_VER=22 CUR_CORE=arcem7d gui
   # For IoTDK
   make TOOLCHAIN=gnu BOARD=iotdk gui

For Metaware toolchain, the mdb (MetaWare debugger) is used and it's a GUI interface.
You can refer the Metaware toolchain use manual for details.

For ARC GNU toolchain,  the command line based gdb is used. You need to have some basic knowledge of gdb
debug.


Create your own application
***************************

Here, it's your turn to create your own application in |embarc|, taking a
well-known simple ``hello world`` as an example.

* Goals

    * Baremetal application based on |embarc|
    * Hardware: EMSK 2.2 - ARC EM7D Configuration / IoTDK
    * Print "Hello world from embARC" through UART at 115200 bps
    * Use GNU toolchain to running and debugging in the command line

1. Creat a folder named ``hello_world`` under ``embarc/example/baremetal``.

2. Copy the makefile template ``example/example.makefile`` and ``main.c.tmpl``
   into ``hello_world`` folder and rename ``example.makefile`` to ``makefile``,
   rename ``main.c.tmpl`` to ``main.c``.

3. Change the configurations in makefile according to your hardware configuration and application.

    * Change the application name: change the value of ``APPL`` to ``helloworld``.

    * Change the board name: change the value of ``BOARD`` to ``emsk`` / ``iotdk``. This
      option can also be given in cmd line. If not specified, the default value
      will be ``emsk``

    * Change the board version: change the value of ``BD_VER`` to ``22`` (for emsk) or ``10`` (for iotdk).This
      option can also be given in cmd line. If not specified, the default value
      will be ``22`` for board ``emsk``.

    * Change the core configuration: change the value of **CUR_CORE** to
      **arcem7d** This option can also be given in cmd line. If not specified,
      the default value will ``arcem7d`` for board ``emsk`` and version ``22``.
      For iotdk, **CUR_CORE** can be bypassed as iotdk only has one core configuration.

    * Change the |embarc| root: change the value of ``EMBARC_ROOT`` to
      ``../../..``. ``EMBARC_ROOT`` can be relative path or an absolute path.

    * Add the middleware that you need for this application: Change the value
      of MID_SEL.

        * The value of ``MID_SEL`` must be the folder name in
          ``<embARC>/middleware``, such as ``common`` or ``lwip``.

        * If using ``lwip``, ``ntshell``, ``fatfs``, and ``common``, set
          ``MID_SEL`` to ``lwip ntshell fatfs common``.

        * Set it to ``common`` in the "HelloWorld" application.

    * Change your toolchain: change the value of ``TOOLCHAIN`` to ``gnu``.

    * Update source folders and include folder settings.

        * Update the C code folder settings: change the value of
          ``APPL_CSRC_DIR`` to ``.``. ``APPL_CSRC_DIR`` is the C code relative
          path to the application folder

        * Update the assembly source-folder settings: change the value of ``APPL_ASMSRC_DIR``.

        * Update the include-folders settings: change the value of
          ``APPL_INC_DIR`` which is the application include path to the
          application folder (-I).

        * If more than one directory is needed, use whitespace between the folder paths.

    * Set your application defined macros: Change the value of ``APPL_DEFINES``.

        * For example, if define ``APPLICATION=1``, set APPL_DEFINES to ``-DAPPLICATION=1``.

   Then makefile for ``hello world`` application will be like this

    .. code-block:: makefile

            ## embARC application makefile template ##
            ### You can copy this file to your application folder
            ### and rename it to makefile.
            ##

            ##
            # Application name
            ##
            APPL ?= helloworld

            ##
            # Extended device list
            ##
            EXT_DEV_LIST +=

            # Optimization level
            # Please refer to toolchain_xxx.mk for this option
            OLEVEL ?= O2

            ##
            # Current board and core (for emsk)
            ##
            BOARD ?= emsk
            BD_VER ?= 22
            CUR_CORE ?= arcem7d

            ##
            # Current board and core (for iotdk)
            BOARD ?= iotdk
            BD_VER ?= 10


            ##
            # Debugging JTAG
            ##
            JTAG ?= usb

            ##
            # Toolchain
            ##
            TOOLCHAIN ?= gnu

            ##
            # Uncomment following options
            # if you want to set your own heap and stack size
            # Default settings see options.mk
            ##
            #HEAPSZ ?= 8192
            #STACKSZ ?= 8192

            ##
            # Uncomment following options
            # if you want to add your own library into link process
            # For example:
            # If you want link math lib for gnu toolchain,
            # you need to set the option to -lm
            ##
            #APPL_LIBS ?=

            ##
            # Root path of embARC
            ##
            EMBARC_ROOT = ../..

            ##
            # Middleware
            ##
            MID_SEL = common

            ##
            # Application source path
            ##
            APPL_CSRC_DIR = .
            APPL_ASMSRC_DIR = .

            ##
            # Application include path
            ##
            APPL_INC_DIR = .

            ##
            # Application defines
            ##
            APPL_DEFINES =

            ##
            # Include current project makefile
            ##
            COMMON_COMPILE_PREREQUISITES += makefile

            ### Options above must be added before include options.mk ###
            # Include key embARC build system makefile
            override EMBARC_ROOT := $(strip $(subst \,/,$(EMBARC_ROOT)))
            include $(EMBARC_ROOT)/options/options.mk


 4.  run

    * Set your EMSK 2.2 hardware configuration to ARC EM7D (no need to set for iotdk), and connect it to
      your PC. Open ``PuTTY`` or ``Tera-term``, and connect to the right COM
      port. Set the baudrate to **115200 bps**.

    * Enter ``make run`` in the command line to run this application.

Exercises
=========

Create your application which is different with **blinky** and **hello_world** in |embarc|.