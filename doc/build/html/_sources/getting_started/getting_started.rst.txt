.. _getting_started:

Getting Started
===============

Use this guide to get started with your ARC labs development.

Software Requirement
####################
* `ARC Development Tools <https://www.synopsys.com/designware-ip/processor-solutions/arc-processors/arc-development-tools.html>`_
    Choose **MetaWare Toolkit** and/or **ARC GNU Toolchain** from the following list according to your requirement.

  * MetaWare Toolkit

    * `Premium MetaWare Development Toolkit (2018.06) <https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware>`_
      The DesignWare ARC MetaWare Development Toolkit builds upon a 25-year legacy of industry-leading compiler and debugger products. It is a complete solution that contains all the components needed to support the development, debugging and tuning of embedded applications for the DesignWare ARC processors.
    * `DesignWare ARC MetaWare Toolkit Lite (2018.06) <https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware>`_
      A demonstration/evaluation version of the MetaWare Development Toolkit is available for free from the Synopsys website. MetaWare Lite is a functioning demonstration of the MetaWare Development Toolkit, but has a number of restrictions, including a code-size limit of 32 Kilobytes and no runtime library sources. It is available for Microsoft Windows only.

  * ARC GNU Toolchain

    * `Open Source ARC GNU IDE (2018.03) <https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases>`_
      The ARC GNU Toolchain offers all of the benefits of open source tools, including complete source code and a large install base. The ARC GNU IDE Installer consists of Eclipse IDE with `ARC GNU plugin for Eclipse <https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/releases>`_, `ARC GNU prebuilt toolchain <https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases>`_ and `OpenOCD for ARC <https://github.com/foss-for-synopsys-dwc-arc-processors/openocd>`_
* `Digilent Adept Software <https://store.digilentinc.com/digilent-adept-2-download-only/>`_ for Digilent JTAG-USB cable driver. All the supported boards are equipped with on board USB-JTAG debugger, so just one USB cable is required, no need for external debugger.

* `Tera Term <http://ttssh2.osdn.jp/>`_ or `PuTTY <https://www.putty.org/>`_ for serial terminal connection, 115200 baud, 8 bits data, 1 stop bit and no parity (115200-8-N-1) by default.

.. note:: If using embARC with GNU toolchain on Windows, install `Zadig <http://zadig.akeo.ie>`_ to replace FTDI driver with WinUSB driver. See `How to Use OpenOCD on Windows <https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/wiki/How-to-Use-OpenOCD-on-Windows>`_ for more information. If you wanto switch back to Metaware toolchain,  you should also switch back the usb-jtag driver from WinUSB to FTDI driver.

Install Software Tools
######################

Install Metaware Toolkit
************************

Here we will start install MetaWare Development Toolkit (2017.09).

1. Double click the **mw_dekit_arc_i_2017_09_win_install.exe**, it will show

.. image:: /img/mwdt_1.png

2. Click next, choose I accept, continue to click next

.. image:: /img/mwdt_2.png

3. Choose Typical installation, then click next

.. image:: /img/mwdt_3.png

4. Set the install path (please use English letters only and no space), then
   click next until the installation is finished

.. image:: /img/mwdt_4.png

5. Set the license file (SNPSLMD_LICENSE_FILE) for MetaWare Development
   Toolkit. It can be a real file containing license, also can be a license server

* For Windows, go to Computer->property->Advanced->Environment Variables->System Variables->New to  Set

.. image:: /img/mwdt_5.png

* For Linux, please add SNPSLMD_LICENSE_FILE into your system variables

6. Test the MetaWare Development Toolkit and its license

Open cmd.exe in Windows and find the queens.c in the installation folder of
MetaWare Development Toolkit, e.g., **C:\\ARC\\MetaWare\\arc\\demos\\queen.c**. Type the following commands in cmd

 .. code-block:: console

     # On Windows
     cd  C:\ARC\MetaWare\arc\demos
     ccac queens.c

If you get the following message and no error, it means MetaWare Development
Toolkit is successfully installed and  license is ok.

.. code-block:: console

    MetaWare C Compiler N-2017.09 (build 005)       Serial 1-799999.
    (c) Copyright 1987-2017, Synopsys, Inc.
    MetaWare ARC Assembler N-2017.09 (build 005)
    (c) Copyright 1996-2017, Synopsys, Inc.
    MetaWare Linker (ELF/ARCompact) N-2017.09 (build 005)
    (c) Copyright 1995-2017, Synopsys, Inc.


Install ARC GNU Toolchain
*************************

Please go `here <https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases>`__ (https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases) to get the latest version of
ARC GNU toolchain.

To use and install ARC GNU toolchain, you can refer `this <http://embarc.org/toolchain/ide/index.html>`__ (http://embarc.org/toolchain/ide/index.html), where has detailed instructions.

It's recommended to install ARC GNU toolchain in the path (windows: ``C:\arc_gnu\``, linux: ``~/arc_gnu/``) and add ``arc_gnu/bin`` into $PATH variable.

Install embARC OSP
******************

The embARC OSP source code is hosted in a GitHub repository that supports
cloning via git. There are scripts and such in this repo that you'll need to set up your development environment, and we'll be using Git to get this repo. If you don't have Git installed, see the beginning of the OS-specific instructions below for help.

We'll begin by using Git to clone the repository anonymously.

.. code-block:: console

   # On Windows
   cd %userprofile%
   # On Linux
   cd ~

   git clone https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp.git embarc_osp

You have successfully checked out a copy of the source code to your local
machine.

Install ARC labs code
*********************

The source codes of ARC labs are assumed to work with embARC OSP. You need to use git to clone or download the ARC labs first, then copy the ``labs`` folder to the root folder of embARC OSP. You will get the following folder structure:

.. code-block:: console

    embarc_osp
    ├── arc
    ├── board
    ├── device
    ├── doc
    ├── example
    ├── labs
    ├── inc
    ├── library
    ├── middleware
    ├── options
    └── os



Final Check
###########

Check the following items and set development environment.

* Make sure the paths of the above required tools for the MetaWare toolkit and ARC GNU toolchain are added to the system variable **PATH** in your environment variables.

* We recommend users to install ARC GNU IDE to default location. Otherwise you need to make additional changes as below.

  * If running and debugging embARC applications using **arc-elf32-gdb** and `OpenOCD for ARC <https://github.com/foss-for-synopsys-dwc-arc-processors/openocd>`_, make sure 1) the path of **OpenOCD** is added to the **PATH** in your environment variables, and 2) modify **OPENOCD_SCRIPT_ROOT variable** in *<embARC>/options/toolchain/toolchain_gnu.mk* according to your **OpenOCD** root path.
  * If running GNU program with using the GNU toolchain on Linux, modify the **OpenOCD** configuration file as Linux format with LF line terminators. **dos2unix** can be used to convert it.

.. note:: Check the version of your toolchain. The embARC OSP software build system is purely makefile-based. *make/gmake* is provided in the MetaWare toolkit (gmake) and ARC GNU toolchain (make)


