.. _lab1:

How to use ARC IDE
======================

|mwdt|
------

Purpose
^^^^^^^^

* To learn |mwdt|
* To get familiar with the basic usage of the |mwdt|
* To get familiar with the features and usage of the MetaWare Debugger (mdb)

Requirements
^^^^^^^^^^^^

The following hardware and tools are required:

* PC host
* |mwdt|
* nSIM simulator or ARC board (|emsk| / |iotdk|)
* ``embarc_osp/arc_labs/labs/lab_core_test``

Content
^^^^^^^^^

* Create a C project using the |mwdt|
* Import the code ``CoreTest.c`` from ``embarc_osp/arc_labs/labs/lab_core_test``
* Configure compilation options to compile, and generate executable files.
* Start the debugger of |mwdt| and enter debug mode.

From two different perspectives of C language and assembly language, use the methods of setting breakpoint, single-step execution, full-speed executions, etc., combined with observing PC address, register status, global variable status, and profiling performance to analyze and debug the target program.


Principles
^^^^^^^^^^^

Use the |mwdt| to create projects and load code. In the engineering unit, configure the compilation options to compile code, debug, and analyze the compiled executable file.

Routine code CoreTest.c:

.. code-block:: c

    /////////////////////////////////////////////////////////////////////////
    // This small demo program finds the data point that is the
    // minimal distance from x and y [here arbitrarily defined to be (4,5)]
    //
    // #define/undefine '_DEBUG' precompiler variable to obtain
    // desired functionality. Including _DEBUG will bring in the
    // I/O library to print results of the search.
    //
    // For purposes of simplicity, the data points used in the computations
    // are hardcoded into the POINTX and POINTY constant values below
    /////////////////////////////////////////////////////////////////////////


    #ifdef _DEBUG
    #include "stdio.h"
    #endif

    #define POINTX {1, 2, 3, 4,  5,  6,  7,  8,  9, 10}
    #define POINTY {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}
    #define POINTS 10

    #define GetError(x, y, Px, Py) \
    	( (x-Px)*(x-Px) + (y-Py)*(y-Py) )

    int main(int argc, char* argv[]) {
    	int pPointX[] = POINTX;
    	int pPointY[] = POINTY;

    	int x, y;
    	int index, error, minindex, minerror;

    	x = 4;
    	y = 5;

    	minerror = GetError(x, y, pPointX[0], pPointY[0]);
    	minindex = 0;

    	for(index = 1; index < POINTS; index++) {
		error = GetError(x, y, pPointX[index], pPointY[index]);

    		if (error < minerror) {
    			minerror = error;
    			minindex = index;
                }
            }

    #ifdef _DEBUG
    	printf("minindex = %d, minerror = %d.\n", minindex, minerror);
    	printf("The point is (%d, %d).\n", pPointX[minindex], pPointY[minindex]);
    	getchar();
    #endif

    	return 0;
        }


Steps
^^^^^^

1. Create a project

Open the |mwdt|, create an empty project called ``demo``, and select the **ARC EM Generic** processor.

|figure1|

2. Import the code file CoreTest.c to the project demo.

In the Project Explorer, click |icon1| and select **Import**.

In the Implort wizard, select **File system** from the **General** tab, then click **Next**. As shown in the following figure, in the From directory fileld, type or browse to select the directory contain the file CoreTest.c. Recent directories that have been imported from are shown on the From directory field's combo box. In the left pane, check a folder that will import its entire contents into the Workbench, and in the right pane check the file CoreTest.c. 

|figure2|

Click **Finish** when done, the file CoreTest.c is now shown in the one of the navigation views in the project ``demo``. 

3. Set compilation options

From the Project Explorer view, right-click the project ``demo`` and choose Properties. Click **C/C++ Build** > **Settings** > **Tool Settings** menu options.
The **Tool Settings** dialog opens.

|figure3|

Select **Optimization/Debugging** to set the compiler
optimization and debugging level. For example, set the optimization level to
turn off optimization, and set the debugging level to load all debugging
information.

Select **Processor/Extensions** to set the compilation options corresponding to the target processor hardware properties, such as the
version of the processor, whether to support extended instructions such as
shift, multiplication, floating-point operations, and so on whether to include
Timer0/1. As shown in the following figure, this setting indicates that the target
processor supports common extended instructions.

|figure4|

Select **MetaWare ARC EM C/C++** and check the settings compilation options. Click **OK** when done.

4. Build project

In the Project Explorer view, select project ``demo``. 
Click **Project** > **Build Project** or click the icon |icon2| on the toolbar. 
In the |mwdt| main interface, you can see in the **Console** view the output and results of the build command. Click on its tab to bring the view forward if it is not currently visible. If for some reason it's not present, you can open it by selecting **Window** > **Show View** > **Console**. When the message ``Finished building target: demo.elf`` is displayed, the compilation is successful, and the compiled executable file demo.elf can be seen in the Project Explorer.

|figure5|

5. Set debug options

Click the **Run** > **Debug Configurations...** menu option to open the **Debug Configurations** dialog.
Double-click **C/C++ Application** or right-click **New** to create a new launch configuration.

|figure6|

If a project is selected in the Project Explorer view all data is automatically entered, take a moment to verify its accuracy or change as needed. Here you do not need to make any changes, just click **Debug** to enter the debugging interface.

6. Debug executable file demo.elf

You may be prompted to switch to the **Debug** perspective. Click **Yes**.

The Debug perspective appears with the required windows open. And the windows can be source code window, assembly code window, register window, global variable window, breakpoint window, function window, and so on.

|figure7|

In the C code window, right-click the code line number on the left side of the window, select **Toggle Breakpoint** or double-click the line number to set a breakpoint on. In the assembly code window, double-click a line of code to set a breakpoint on. You'll see a blue circle there indicating the breakpoint is set.

After the breakpoint is set, click **Run** > **Resume** or you can use the **Resume** button |icon3| on the toolbar of the Debug view to run the program. The program runs directly to the nearest breakpoint. You can observe the current program execution and the relevant status information of the processor through the various windows as described in previous step. If you want to know more about the details of program execution and the instruction behavior of the processor, you can use the following three execution commands |icon4| to perform single-step debugging. The icon |icon5| can choose to step through a C language statement or an assembly instruction to match the status information of each window. It can be very convenient for program debugging. If you want to end the current debugging process, click |icon6|. If you want to return to the main |mwdt| page, click C/C++ |icon7|.

7. Code performance analysis using the debugger

Based on the previous project ``demo``, open the **Compile Options** dialog box in step 3 and set the Optimization Level to -O0 in the **Optimization/Debugging** column. Then click |icon8| to recompile the project, and click |icon9| to enter the debugging interface. Click **Debugger** in the main menu of the debugging interface, select **Disassembly** from the menu drop-down menu, open the disassembly code window, and you can see that the program is paused at the entrance of the main() function. In the same way, select **Profiling** in the **Debugger** drop-down menu, open the performance analysis window and click |icon10|.

|figure8|

The **Profiling** window displays the corresponding of the number of executed instructions of the program with each function under the current debug window. From left to right, the total number of executions of function instructions in the total number of executions of the entire program instruction, the total number of executions of the accumulated instructions, the total number of executions of the functions, the number of times the function is called, the number of including functions, the address of the function, and the name of the function. Through the relationship between the instruction information and the function in the Profiling window, it is very convenient to analyze the program efficiency and find the shortcoming of the program performance.

Use this project as an example to continue to introduce the use of the **Profiling** window. The program is paused at the entrance of the main() function and the **Profiling** window opens. The main() function is the main object of performance analysis optimization. The content displayed in the **Profiling** window is some function information initialized by the processor before the main() function is executed. Click |icon11| in the **Profiling** window to clear the current information. If you click |icon12|, nothing is displayed, and it indicates that the cleaning is successful. Set a breakpoint at the last statement of the main() function (either C statement or assembly statement), and click |icon13| in the toolbar above the debug interface to let the program run until it hits the breakpoint. Click |icon14| in the **Profiling** window, and only the information related to the main() function is displayed. Therefore, flexible setting of breakpoints, combined with the clear function, can perform performance analysis on the concerned blocks.

|figure9|

It can be seen that the multiplication library function _mw_mpy_32x32y32 in
the main() function is called 20 times, and a total of 2064 instructions are
executed, while the main() function itself executes only 326 instructions, and
the memcpy function executes 86 instructions. It can be seen that the
implementation of the multiplication function of the program consumes a large
number of instructions, and the large number of instructions means that the
processor spends a large number of computation cycles to perform
multiplication operations. Therefore, multiplication is the shortcoming of
current program performance. If you want to improve the performance of the
program, you should consider how you can use fewer instructions and
implement multiplication more efficiently.

Exercises
^^^^^^^^^^

Enable MPY extension instrctions by setting Multiply Option -Xmpy_option = wlh1 in step 3, it implements multiplication more efficiently with fewer instructions.
Redo steps 4 - 7 to analyze with the debugger's Profiling function, observe the total number of instructions consumed by the main function, and compare it with the above Profiling result.

|arcgnu|
-------------------

Purpose
^^^^^^^^^^

* Learn the |arcgnu|
* Familiar with the |arcgnu|
* Familiar with the functions and usage of the |arcgnu| debugger

Requirements
^^^^^^^^^^^^^

The following hardware and tools are required:

* PC host
* |arcgnu|
* nSIM simulator or ARC board (|emsk| / |iotdk|)
* ``embarc_osp/arc_labs/labs/lab_core_test``

Content
^^^^^^^^^^^

* Create a C project using |arcgnu|
* Import the code ``CoreTest.c`` from ``embarc_osp/arc_labs/labs/lab_core_test``
* Configure compilation options to compile, and generate executable files
* Start the |arcgnu| debugger to enter the debug mode

From two different perspectives of C language and assembly language, use the methods of setting breakpoint, single-step execution, full-speed executions, and so on combined with observing PC address, register status, global variable status, and profiling performance to analyze and debug the target program.

Principles
^^^^^^^^^^

Use the |arcgnu| integrated development environment to create projects and load routine code. In the engineering unit, configure the compile option compilation routine code to debug and analyze the compiled executable file.

Steps
^^^^^

1. Create a project

Open the |arcgnu|, create an empty project called ``core_test``, and select **ARC EM series processor**.

|figure10|

2. Import the code file CoreTest.c to the project demo

In the Project Explorer, right-click |icon15|, and select **Import**..

In the Implort wizard, select **File system** from the **General** tab, then click **Next**. As shown in the following figure, in the From directory fileld, type or browse to select the directory contain the file CoreTest.c. Recent directories that have been imported from are shown on the From directory field's combo box. In the left pane, check a folder that imports the contents into the Workbench, and in the right pane check the file CoreTest.c. 

|figure11|

Click **Finish** when done, the file CoreTest.c is now shown in the one of the navigation views in the project ``core_test``.

3. Set compilation options

From the Project Explorer view, right-click the project ``core_test`` and choose Properties. Click **C/C++ Build** > **Settings** > **Tool Settings**.
The **Tool Settings** dialog opens.

|figure12|

Select **Debugging** to set the compiler optimization
and debugging level. For example, set the optimization level to off
optimization, and the debugging level is to load all debugging information.

Select **Processor** in the current interface to set the compile options
corresponding to the target processor hardware attributes, such as the version
of the processor, whether to support extended instructions such as shift,
multiplication, floating-point operations, and so on whether to include Timer0/1.

In step 1, you built the project using the engineering template of
EMSK, the corresponding necessary options have been set by default. If
there is no special requirement, check the setting compile options in the All
options column and click **OK** when done.

4. Build project

In the Project Explorer view, select project ``core_test``.

Click **Project** > **Build Project** or click |icon16|. 
In the middle of the |arcgnu| main interface, you can see in the **Console** view the output and results of the build command. Click the tab to bring the view forward if it is not currently visible. If for some reason it is not present, you can open it by selecting **Window** > **Show View** > **Console**. When the message ``Finished building target: Core_test.elf`` is displayed, the compilation is successful, and the compiled executable file Core_test.elf can be seen in the Project Explorer.

|figure13|

5. Set debugger options

Click the **Run** > **Debug Configurations...** menu option to open the **Debug Configurations** dialog.
Double-click **C/C++ Application** or right-click **New** to create a new launch configuration.

|figure14|

If a project is selected in the Project Explorer view all data is automatically entered, take a moment to verify its accuracy or change as needed. As you use nSIM simulator to simulate EMSK development board, you need to modify the settings of Debugger, Common, and Terminal (this is because nSIM cannot be called directly in GNU IDE. Still needs GDB Server for indirect calls). The specific settings are as follows:

* Set Debugger->Gdbserver Settings

|figure15|

Select nSIM as the **ARC GDB Server**, and the default **port number** is 49105. Note that **Use TCF** is enabled. Otherwise, the nSIM cannot work normally. The TCF start file is under *nSIM/nSIM/etc/tcf/templates* (the default installation path). If you have downloaded the MetaWare IDE, the default nSIM path is *C:/ARC/nSIM/nSIM/etc/tcf/templates*, and you can select a TCF file from this folder (depending on the version of the board you are simulating and the kernel model), as shown earlier.

* Pay attention to Debug in Common

|figure16|

* Terminal settings

If you are using the |emsk|, the terminal automatically selects the correct port number, and if you are using the emulator without a port, uncheck it as shown in the following figure.

|figure17|

When you are done, click **Debug** to enter the debugging interface.

6. Debug executable file core_test.elf

You may be prompted to switch to the **Debug** perspective. Click **Yes**.

The Debug perspective appears with the source code window, assembly code window, register window, global variable window, breakpoint window, function window, and so on.

|figure18|

In the C code window, right-click the code line number on the left side of the window, select **Toggle Breakpoint** or double-click the line number to set a breakpoint on. In the assembly code window, double-click a line of code to set a breakpoint on. A blue circle is seen indicating the breakpoint is set.

After the breakpoint is set, click **Run** > **Resume** or you can use the **Resume** button |icon3| on the toolbar of the Debug view to run the program. The program runs directly to the nearest breakpoint. You can observe the current program execution and the relevant status information of the processor through the various windows as described in previous step. If you want to know more about the details of program execution and the instruction behavior of the processor, you can use the following three execution commands |icon4| to perform single-step debugging. The icon |icon5| can choose to step through a C language statement or an assembly instruction to match the status information of each window. It can be very convenient for program debugging. If you want to end the current debugging process, click |icon6|. If you want to return to the main |arcgnu| page, click C/C++ |icon7|.

7. Code performance analysis using the debugger

Same as the code performance analysis method of |mwdt|.

For the use of these two IDEs, you can refer to the Help documentation in the respective IDE, or you can view the on-line documentation provided by Synopsys.

.. |figure1| image:: /img/lab1_figure1.png
.. |figure2| image:: /img/lab1_figure2.png
.. |figure3| image:: /img/lab1_figure3.png
.. |figure4| image:: /img/lab1_figure4.png
.. |figure5| image:: /img/lab1_figure5.png
.. |figure6| image:: /img/lab1_figure6.png
.. |figure7| image:: /img/lab1_figure7.png
.. |figure8| image:: /img/lab1_figure8.png
.. |figure9| image:: /img/lab1_figure9.png
.. |figure10| image:: /img/lab1_figure10.png
.. |figure11| image:: /img/lab1_figure11.png
.. |figure12| image:: /img/lab1_figure12.png
.. |figure13| image:: /img/lab1_figure13.png
.. |figure14| image:: /img/lab1_figure14.png
.. |figure15| image:: /img/lab1_figure15.png
.. |figure16| image:: /img/lab1_figure16.png
.. |figure17| image:: /img/lab1_figure17.png
.. |figure18| image:: /img/lab1_figure18.png

.. |icon1| image:: /img/lab1_icon1.png
.. |icon2| image:: /img/lab1_icon2.png
.. |icon3| image:: /img/lab1_icon3.png
.. |icon4| image:: /img/lab1_icon4.png
.. |icon5| image:: /img/lab1_icon5.png
.. |icon6| image:: /img/lab1_icon6.png
.. |icon7| image:: /img/lab1_icon7.png
.. |icon8| image:: /img/lab1_icon8.png
.. |icon9| image:: /img/lab1_icon9.png
.. |icon10| image:: /img/lab1_icon10.png
.. |icon11| image:: /img/lab1_icon11.png
.. |icon12| image:: /img/lab1_icon12.png
.. |icon13| image:: /img/lab1_icon13.png
.. |icon14| image:: /img/lab1_icon14.png
.. |icon15| image:: /img/lab1_icon15.png
.. |icon16| image:: /img/lab1_icon16.png
.. |icon17| image:: /img/lab1_icon17.png
.. |icon18| image:: /img/lab1_icon18.png
.. |icon19| image:: /img/lab1_icon19.png
.. |icon20| image:: /img/lab1_icon20.png
.. |icon21| image:: /img/lab1_icon21.png
