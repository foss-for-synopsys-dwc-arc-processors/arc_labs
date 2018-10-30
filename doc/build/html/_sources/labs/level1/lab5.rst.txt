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

1. Board introduction
2. Board programming

Principles
==========

1. |emsk|

For the basic introduction of |emsk|, please go `here <http://embarc.org/embarc_osp/doc/build/html/board/emsk.html>`__

There are on board LEDs, DIP switchs and button on |emsk|, this lab will show
how to program theses on-board peripherals of |emsk|.

2. |iotdk|

For the basic introduction of |iotdk|, please go `here <http://embarc.org/embarc_osp/doc/build/html/board/iotdk.html>`__

As there are no easy-to-use on board peripherals like LEDs on |emsk|, this lab will show how to control a LED through the arduino inteface of |iotdk|.

Steps
=====

iotdk board has a arduino inteface, wo choose arduino digital pinout ARDUINO_PIN_0(iotdk gpio4b_2[0]) to control LED.

1. find a led, connect the led anode pin to ARDUINO_PIN_0, connect the led cathode pin to iotdk onboard gnd.

2. compile and run the ``embarc_osp/arc_labs/lab5_iotdk`` example.

.. image:: /img/lab5_iotdk_pin_connect.png
    :alt: lab5_iotdk_pin_connect

.. note::
    the connect between led and iotdk board is just for test.
    a 1kΩ resistor should be added to limited the electric current.

Exercises
=========
