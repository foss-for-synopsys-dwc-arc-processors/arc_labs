.. _getting_started:

Getting Started
===============

Use this guide to get started with your ARC labs development.

Software Requirement
####################
* `ARC Development Tools <https://www.synopsys.com/designware-ip/processor-solutions/arc-processors/arc-development-tools.html>`_
    Select **|mwdt|** or **|arcgnu|** from the following list according to your requirement.

  * |mwdt|

    * `Premium MetaWare Development Toolkit (2018.06) <https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware>`_.
      The DesignWare ARC MetaWare Development Toolkit builds upon a 25-year legacy of industry-leading compiler and debugger products. It is a complete solution that contains all the components needed to support the development, debugging, and tuning of embedded applications for the DesignWare ARC processors.
    * `DesignWare ARC MetaWare Toolkit Lite (2018.06) <https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware>`_.
      A demonstration or evaluation version of the MetaWare Development Toolkit is available for free from the Synopsys website. MetaWare Lite is a functioning demonstration of the MetaWare Development Toolkit with restrictions such as code-size limit of 32 Kilobytes and no runtime library sources. It is available for Microsoft Windows only.

  * |arcgnu|

    * `Open Source ARC GNU IDE (2018.03) <https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases>`_.
      The |arcgnu| offers all of the benefits of open source tools such as complete source code and a large install base. The ARC GNU IDE Installer consists of Eclipse IDE with `ARC GNU plugin for Eclipse <https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/releases>`_, `ARC GNU prebuilt toolchain <https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases>`_, and `OpenOCD for ARC <https://github.com/foss-for-synopsys-dwc-arc-processors/openocd>`_
* `Digilent Adept Software <https://store.digilentinc.com/digilent-adept-2-download-only/>`_ for Digilent JTAG-USB cable driver. All the supported boards are equipped with on board USB-JTAG debugger. One USB cable is required and external debugger is not required.

* `Tera Term <http://ttssh2.osdn.jp/>`_ or `PuTTY <https://www.putty.org/>`_ for serial terminal connection. The serial configurations are 115200 baud, 8 bits data, 1 stop bit, and no parity (115200-8-N-1) by default.

.. note:: If using embARC with GNU toolchain on Windows, install `Zadig <http://zadig.akeo.ie>`_ to replace FTDI driver with WinUSB driver. See `How to Use OpenOCD on Windows <https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/wiki/How-to-Use-OpenOCD-on-Windows>`_ for more information. If you want to switch back to Metaware toolchain, make sure you switch back the usb-jtag driver from WinUSB to FTDI driver.

Install Software Tools
######################

Install Metaware Toolkit
************************

Installing MetaWare Development Toolkit (2017.09).

1. Double click the ``mw_dekit_arc_i_2017_09_win_install.exe`` and click **Next**.

.. image:: /img/mwdt_1.png

2. Select I accept and click **Next**.

.. image:: /img/mwdt_2.png

3. Select Typical installation and click **Next**.

.. image:: /img/mwdt_3.png

4. Set the install path (make sure you use English letters without any space) and
   click **Next** until the installation is complete.

.. image:: /img/mwdt_4.png

5. Set the license file (SNPSLMD_LICENSE_FILE) for MetaWare Development
   Toolkit. It can be a real file containing license or a license server.

* For Windows, go to **Computer** > **Properties** > **Advanced** > **Environment Variables** > **System Variables** > **New**.

.. image:: /img/mwdt_5.png

* For Linux, add SNPSLMD_LICENSE_FILE into your system variables.

6. Test the MetaWare Development Toolkit and the license

At the command prompt, compile and link in one step.

For example, find the queens.c in the demos folder of MetaWare Development Toolkit installation directory.

 .. code-block:: console

     # On Windows
     cd  C:\ARC\MetaWare\arc\demos
     ccac queens.c

If you get the following message without any error, then the MetaWare Development Toolkit is successfully installed.

.. code-block:: console

    MetaWare C Compiler N-2017.09 (build 005)       Serial 1-799999.
    (c) Copyright 1987-2017, Synopsys, Inc.
    MetaWare ARC Assembler N-2017.09 (build 005)
    (c) Copyright 1996-2017, Synopsys, Inc.
    MetaWare Linker (ELF/ARCompact) N-2017.09 (build 005)
    (c) Copyright 1995-2017, Synopsys, Inc.


Install ARC GNU Toolchain
*************************

Click (https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases) to get the latest version of
|arcgnu|.

To use and install |arcgnu|, see (http://embarc.org/toolchain/ide/index.html).

It is recommended to install |arcgnu| in the path (windows: ``C:\arc_gnu\``, linux: ``~/arc_gnu/``) and add ``arc_gnu/bin`` into $PATH variable.

Install embARC OSP
******************

The embARC OSP source code is hosted in a GitHub repository that supports
cloning through git. There are scripts in this repo that you are need to set
up your development environment, and Git is used to get this repo. If you do
not have Git installed, see the beginning of the OS-specific instructions
below for help.

Using Git to clone the repository anonymously

.. code-block:: console

   # On Windows
   cd %userprofile%
   # On Linux
   cd ~

   git clone https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp.git embarc_osp

You have successfully checked out a copy of the source code to your local machine.

Install ARC labs code
*********************

The source codes of ARC labs are assumed to work with embARC OSP. You need to
use git to clone or download the ARC labs to the root folder of embARC OSP. If
the download is successful, the following folder structure is displayed:

.. code-block:: console

   cd path/to/embarc_osp
   git clone https://github.com/foss-for-synopsys-dwc-arc-processors/arc_labs.git arc_labs


.. code-block:: console

    embarc_osp
    ├── arc
    ├── board
    ├── device
    ├── doc
    ├── example
    ├── arc_labs
    ├── inc
    ├── library
    ├── middleware
    ├── options
    └── os



Final Check
###########

Check the following items and set development environment.

* Make sure the paths of |mwdt| or |arcgnu| are added to the system variable **PATH** in your environment variables.

* It is recommended to install |arcgnu| to default location. Otherwise, you need to make additional changes as described.

  * If running and debugging embARC applications using **arc-elf32-gdb** and `OpenOCD for ARC <https://github.com/foss-for-synopsys-dwc-arc-processors/openocd>`_, make sure the path of **OpenOCD** is added to the **PATH** in your environment variables and modify **OPENOCD_SCRIPT_ROOT variable** in *<embARC>/options/toolchain/toolchain_gnu.mk* to your **OpenOCD** root path.
  * If running GNU program with using the GNU toolchain on Linux, modify the **OpenOCD** configuration file as Linux format with LF line terminators. **dos2unix** can be used to convert it.

.. note:: Check the version of your toolchain. The embARC OSP software build system is makefile-based. *make/gmake* is provided in the |mwdt| (gmake) and |arcgnu| (make)


Learn More
##########

For more details about |embarc|, see
`online docs <http://embarc.org/embarc_osp/>`__

