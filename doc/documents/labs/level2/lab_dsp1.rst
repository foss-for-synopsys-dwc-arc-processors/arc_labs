.. _lab_dsp1:

ARC DSP: Compiler Optimizations
====================================

Purpose
---------------------------

- To understand Metaware compiler DSP extension options and optimization level
- To learn how to use Metaware compiler to optimize regular C code with DSP instructions

Requirements
-----------------------------
The following hardware and tools are required:

* PC host
* |mwdt|
* ARC board (|emsk| / |iotdk|)
* ``embarc_osp/arc_labs/labs/dsp_lab_compiler_opt``

Content
-----------------------------

An example code below contains a function "test" which contains a 20 step for loop and a multiply accumulate operation done manually.

.. code-block:: c

    #include <stdio.h>

    short test(short *a, short *b) {
    	int i;

    	long acc = 0;
    	for(i = 0; i < 10; i++)
    		acc += ( ((long)(*a++)) * *b++) <<1 ;

    	return (short) (acc);
    }

    short a[] = {1,2,3,4,5, 6,7,8,9,10};
    short b[] = {11,12,13,14,15, 16,17,18,19,20};

    int main(int argc, char *argv[]) {

    	short c = test(a,b);

    	printf("result=%d",c);

    	return 0;
    }

Use Metaware compiler to optimize the C code with and without DSP extension options, and analyze the assembly code.

Principles
------------------------------------

This section describes compiler options in MetaWare used in this lab.

To optimize code with DSP extensions, two sets of compiler options are used throughout the lab: DSP Extensions options and optimization level.

DSP Extensions Options
^^^^^^^^^^^^^^^^^^^^^^^^^^

Use |embarc| build system to build tool. The details can be found in |embarc| document page. Here is the example command. You can pass extra compiler/linker options by ADT_COPT/ADT_LOPT.

.. code-block:: console

  gmake BOARD=emsk BD_VER=23 CUR_CORE=arcem9d TOOLCHAIN=mw gui ADT_COPT="-Hfxapi -Xdsp2" OLEVEL=O2

Options that are used in the lab are:

* ``-Xdsp[1/2]``:

  Enable DSP instructions

* ``-Xdsp_complex, -Xdsp_divsqrt``:

  Enable complex arithmetic DSP, divide, and sqrt instructions

* ``-Xdsp_ctrl[=up|convergent,noguard|guard, preshift|postshift]``:

  Fine-tune the compiler's assumptions about the rounding, guard-bit, and fractional product shift behavior

* ``-Hdsplib``: Link in the DSP library

  For programming ARC fixed-point DSP in C and C++

  Contains functions to carry out DSP algorithms such as filtering and transforms

* ``-Hfxapi``: Use the Fixed Point API support library

  Used with ``-Xdsp``. Provides low level intrinsic support for ARC EM DSP instructions.

  Programs written using this API execute natively on an ARC EM processor with DSP extensions and can also be emulated on x86 Windows hosts

* ``-Xxy``: Specifies that XY memory is available

  Used with ``-Xdsp2``. Enables optimization for XY memory

* ``-Xagu_small, -Xagu_medium, -Xagu_large``:

  Enables AGU, and specifies its size. Note, IOTDK has small AGU

.. note::

    Because ARC is configurable processor, different cores can contain different extensions on hardware level. Therefore, options set for compiler should match underlying hardware. On the other hand, if specific hardware feature is present in the core but compiler option is not set, it cannot be used effectively, if used at all. IOTDK Core default options are presented in Appendix A.

Optimization level
^^^^^^^^^^^^^^^^^^^^

MetaWare compiler has different optimization levels, which enables or disables various optimization techniques included in the compiler. You can pass the optimization option to gmake by "OLEVEL=O2".

The lowest level is the default -O0, which does little optimization to the compiled assembly code, which can be used for debugging, because in un-optimized assembly code all source code commands have 1:1 representation. On the other hand, -O3 highest level optimization highly modifies output assembly code to make it smaller and fast, but debugging such a code is harder, because it is not close match with source code. Also, high level of optimization requires longer compilation time, which for large project can be significant, if many compilation iterations are to be made.

Optimization for DSP extensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A regular code without direct usage of DSP extensions can be optimized to use DSP extensions wherever applicable, which compiler can do automatically with DSP extension options corresponding to hardware are set and high-level of optimization is selected.

Steps
--------------------------

Step 1. Compiling without DSP extensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set optimization level "-O0", and no DSP extensions (unchecking -Xdsp1, -Xdsp2).

After compilation, open disassembly window and check assembly code for function "test".

Below is the list of options used when launching gmake:

``OLEVEL=O0  ADT_COPT="-arcv2em -core1 -Xlib -Xtimer0 -Xtimer1"``

You can use the following command to generate disassembly code:

``elfdump -T -S <your_working_directory>/obj_iotdk_10/mw_arcem9d/dsp_lab1_mw_arcem9d.elf``

Notice assembly code in the disassembled output. See how many assembly instruction are used for each line. For example, for loop spends several instruction to calculate loop variable value and check whether to stop.

|dsp_figure_1.1|

Step 2. Compiling without DSP extensions, with -O2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Compile with:

``OLEVEL=O2  ADT_COPT="-arcv2em -core1 -Xlib -Xtimer0 -Xtimer1"``

Adding optimization level -O2, optimizes out many of the instructions:

|dsp_figure_1.2|

In this code it is easy to find zero-delay loop ("lp" command) which acts as for loop. Note that multiply-accumulate is done with separate "mpyw_s" and "add1_s" instructions.

Step 3. Compiling with DSP extensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Compile with:

``OLEVEL=O3  ADT_COPT="-arcv2em -core1 -Xlib -Xtimer0 -Xtimer1 -Xdsp1"``

Adding -Xdsp1 (optimization level changed to -O3) helps compiler to optimize away "mpyw_s" and "add1_s" instructions and replace them with hardware dual-16bit SIMD multilication "vmpy2h". Notice the loop count is now 5.

|dsp_figure_1.3|

Exercises
-----------------------------------------------

Remove "<<1" from test function and see changes in the output instructions.

.. |dsp_figure_1.1| image:: /img/dsp_figure_1.1.png
.. |dsp_figure_1.2| image:: /img/dsp_figure_1.2.png
.. |dsp_figure_1.3| image:: /img/dsp_figure_1.3.png
