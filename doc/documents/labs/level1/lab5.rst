.. _lab5:

How to use ARC board
####################

Purpose
=======
1. To get familiar with ARC board and on-board peripheral
2. To how to use ARC board and on-board peripherals
3. To how to debug the ARC board and on-board peripherals

Equipment
=========
* PC host
* |arcgnu| / |mwdt|
* ARC board (|emsk| / |iotdk|)
* ``embarc_osp/arc_labs/labs/lab5_emsk`` / ``embarc_osp/arc_labs/lab5_iotdk``

Content
========

1. Board introduction.

Through the user manual, get a brief knowLEDge of ARC board and what peripherals are on it.

2. Board programming.

Based on |embarc|, program the on board peripherals.

Principles
==========

1. |emsk|

For the basic introduction of |emsk|, please go `here <http://embarc.org/embarc_osp/doc/build/html/board/emsk.html>`__

There are on board LEDs, DIP switchs and button on |emsk|, this lab will show
how to program theses on-board peripherals of |emsk|.

The code for |emsk| is located in ``embarc_osp/arc_labs/labs/lab5_emsk``. In the code, the button and DIP switch values
of |emsk| are read and LED blinks periodically.



2. |iotdk|

For the basic introduction of |iotdk|, please go `here <http://embarc.org/embarc_osp/doc/build/html/board/iotdk.html>`__

As there are no easy-to-use on board peripherals like LEDs on |emsk|, this lab will show how to control a LED through the arduino interface of |iotdk|.

Steps
=====

|emsk|
******

1. Connect |emsk| to PC, select **em7d** configuration and open UART terminal.

2. Compile and run the ``embarc_osp/arc_labs/lab5_emsk`` example with the following cmds.

.. code-block:: console

   cd /arc_labs/lab5_emsk
   make TOOLCHAIN=gnu BOARD=emsk BD_VER=22 CUR_CORE=em7d run

3. Watch the changes of LED, press the button or operate the DIP switch, then watch the result in UART terminal.



|iotdk|
*******

|iotdk has a arduino interface, here select arduino digital pinout ARDUINO_PIN_0(iotdk gpio4b_2[0]) to control LED.

1. find a LED, connect the LED anode pin to ARDUINO_PIN_0, connect the LED cathode pin to GND of |iotdk|.

2. compile and run the ``embarc_osp/arc_labs/lab5_iotdk`` example.

.. image:: /img/lab5_iotdk_pin_connect.png
    :alt: lab5_iotdk_pin_connect

.. note::
    the connect between LED and |iotdk| is just for test.
    a 1kΩ resistor should be added to limited the current.

Exercises
=========

Try to create you own application to program the peripherals of ARC board
