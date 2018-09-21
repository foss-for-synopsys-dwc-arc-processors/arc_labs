.. _lab8:

Memory map and linker
#####################
Purpose
=======
- To get familiar with the memory mapping in the compile process
- To learn how to use the linker

Equipment
=========
PC, MetaWare Development Toolkit, nsim simulator, example \\labs\\lab8_linker in ARC labs

Content
========
Customizing your program with **compiler pragmas**.
At first, using "pragma code" to specify a new name of section in which the code of function reside.
Then mapping this code section into specified memory location with linker.
Finally, checking the location of this code section after bulid process.

Principles
==========
By default, compiler-generated code is placed in the *.text* section. The default code section name can be overridden by using the *code pragma*. After compile process, the linker will automatically map all input sections from object files to output sections in executable files. If you want to customize the mapping, you can change the default linker mapping by invoking a linker command file.

Steps
=====

Create a project and overriding code section name
---------------------------------------------------

Open the MetaWare IDE, create an empty C project called lab_linker and select ARC EM series processor. Then import the main.c and link.cmd files under *\\labs\\lab8_linker* directory into the project.

Open main.c file in MetaWare IDE, using "pragma code" to change the section in which function ``modify`` reside from *.text* to a new name "*modify_seg*".

.. code-block:: c

	#pragma Code ("modify_seg")
	void modify(int list[], int size) {
	    int out, in, temp;

	    for(out=0; out<size; out++)
	        for(in=out+1; in<size; in++)
        	    if(list[out] > list[in]) {
	                temp = list[in];
	                list[in] = list[out];
	                list[out] = temp;
        	    }
	}
	#pragma Code ()

Pragma code has two forms that must be used in pairs to bracket the affected function definitions:

.. code-block:: c

	#pragma code(Section_name)
	/* ----- Affected function definitions go here ---- */
	#pragma code() /* No parameters here */

Section_name is a constant string expression that denotes the name of the section

.. note::
	About detailed usage of the compiler pragmas, please refer to the document "MetaWare C/C++ Progarmmer's Guide for the ccac Compiler"

Edit the linker command file
----------------------------

Open the link.cmd file, there are two parts, one is for memory blocks location, the other is for sections mapping.
Add one new block named "*MyBlock*" in MEMORY, the start address is 0x00002000, and the size is 32KB. Then add one new GROUP in SECTIONS, and mapping section "*modify_seg*" into *MyBlock*.

.. code-block:: c

	MEMORY {
	    // Note: overlap of code and data spaces is not recommended since it makes
	    //       Address validity checking impossible with the debugger and simulator
	    MyBlock: ORIGIN = 0x00002000, LENGTH = 32K
	    MEMORY_BLOCK1:  ORIGIN = 0x0010000, LENGTH = 64K
	    MEMORY_BLOCK2:  ORIGIN = 0x0020000, LENGTH = 128K
	}

	SECTIONS {
	    GROUP: {
        		modify_seg: {}
        	   }>MyBlock
	......

.. note::
	About format and syntax of the linker command file, please refer to the document "MetaWare ELF Linker and Utilities User's Guide"

Add the linker command file into the project
--------------------------------------------

Right click the current project lab_linker and select Properties in the popup tab. Click C/C++ build **>>** settings **>>** Tool Settings to open the linker option settings page.

|figure1|

In the current page, select Command files to add linker.cmd file into this project.

Check the result
----------------

In linker option settings page, select Map listing to check Generate listing file(=.map)

|figure2|

Build the lab_linker project, then open the lab_linker.map file under Debug directory.

|figure3|

In this file, search SECTIONS SUMMARY, then you can check the size and location of *modify_seg* section, it resides in *MyBlock*, same as you set in the linker cmd file.

Exercises
=========

Try to check the memory mapping info of *modify_seg* section by using elfdump tool.


.. |figure1| image:: /img/lab8_figure1.png
.. |figure2| image:: /img/lab8_figure2.png
.. |figure3| image:: /img/lab8_figure3.png
