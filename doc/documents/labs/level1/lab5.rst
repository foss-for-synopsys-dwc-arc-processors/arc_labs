.. _lab5:

How to use ARC board
#######################

Purpose
=======
- To get familiar with the usage of ARC board and on-board peripherals
- To know how to program and debug the ARC board and on-board peripherals

Requirements
============

The following hardware and tools are required:

* PC host
* |arcgnu| / |mwdt|
* ARC board (|emsk| / |iotdk|)
* ``embarc_osp/arc_labs/labs/lab5_emsk`` / ``embarc_osp/arc_labs/labs/lab5_iotdk``

Content
========

- A brief introduction of ARC board and on-board peripherals
- Based on |embarc|, program the GPIO to control some on-board peripherals

.. note::
    About the detailed usage of |embarc|，please refer to `How to use embARC OSP <http://embarc.org/arc_labs/doc/build/html/labs/level1/lab2.html>`__

Principles
==========

|emsk|
*******

About the brief introduction of |emsk|, please refer to `embARC OSP Documentation <http://embarc.org/embarc_osp/doc/build/html/board/emsk.html>`__

There are LEDs, DIP switches and buttons on |emsk|, this lab will show
how to program the GPIO to control these on-board peripherals of |emsk|.
The code for this lab is located in ``embarc_osp/arc_labs/labs/lab5_emsk``. In the code, the on-board buttons and DIP switches' values
are read, and whether LEDs are on or off depend on the value of the buttons and DIP switches.



|iotdk|
*******

About the brief introduction of |iotdk|, please refer to `embARC OSP Documentation <http://embarc.org/embarc_osp/doc/build/html/board/iotdk.html>`__

As there are no LED or other easy-to-use peripherals on |iotdk|, this lab will show how to control a LED through the arduino interface of |iotdk|. 
The code for this lab is located in ``embarc_osp/arc_labs/labs/lab5_iotdk``. In the code, the external connected LED blinks periodically.

Steps
=====

|emsk|
******

1. Connect |emsk| to PC, select **em7d** configuration and open UART terminal.

2. Compile and run the ``embarc_osp/arc_labs/lab5_emsk`` example with the following cmds.

.. code-block:: console

   cd /arc_labs/lab5_emsk
   make run

3. Press the buttons and toggle the DIP switches, then check the result in UART terminal, and watch the changes of on-board LEDs.

|figure1| 

|iotdk|
*******

|iotdk| has an arduino interface, here select arduino digital pinout **ARDUINO_PIN_0(iotdk gpio4b_2[0])** to control LED.

1. Find a LED, connect the LED anode pin to **ARDUINO_PIN_0**, connect the LED cathode pin to **GND** of |iotdk|.

2. Compile and run the ``embarc_osp/arc_labs/lab5_iotdk`` example with the following cmds.

.. code-block:: console

   cd /arc_labs/lab5_iotdk
   make run

3. Watch the changes of external connected LED.

|figure2|

.. note::
    The connection between LED and |iotdk| is just for test.
    A 1kΩ resistor should be added in series connection to limited the current and prevent damage to I/O pin.

Exercises
=========

Try to create you own application to control the peripherals of ARC board

.. |figure1| image:: /img/lab5_emsk.png
   :alt: lab5_emsk
   :width: 400


.. |figure2| image:: /img/lab5_iotdk_pin_connect.png
   :alt: lab5_iotdk_pin_connect
   :width: 400