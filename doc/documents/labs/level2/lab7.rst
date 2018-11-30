.. _lab7:

BLE Communication
###################

Purpose
=======
- To get familiar with the wireless communication in IoT
- To get familiar with the usage of RN4020 BLE module on |iotdk|
- To learn the usage of APIs of RN4020 driver in |embarc|


Requirements
============
The following hardware and tools are required:

* PC host
* A smartphone which supports BLE
* ARC GNU toolchain/MetaWare Development Toolkit
* ARC board (|iotdk|)
* |embarc| package
* ``embarc_osp/arc_labs/labs/lab6_ble_rn4020``

Content
========
The Communication between smartphone and |iotdk| board with RN4020 BLE module.

- Setup RN4020 BLE module by using API of RN4020 driver.
- Connect smartphone and RN4020 by BLE, and check the data send by |iotdk| in smartphone.
- Send data from smartphone to |iotdk| board, and print this data value in terminal.


Principles
==========
RN4020 BLE module is controlled by the user through input/output lines (that is physical device pins) and an UART interface.
The UART Interface supports ASCII commands to control/configure the RN4020 modules for any specific requirement based on the application.


Setup
-----
Before connecting an RN4020 module to a smartphone device, you might need to set up the RN4020 module as follows.

1. Configure UART which is connected to RN4020 with these parameters: **Baud rate - 115200, Data bits - 8, Parity - None, Stop bits - 1**

2. Set the **WAKE_SW** pin high to enter command mode

3. Run the command **SF, 1** to reset to the factory default configuration

4. Run the command **SN, IoT DK** to set the device name to be "IoT DK"

5. Run the command **SS, C0000001** to enable support of the Device Information, Battery Service, and User-Defined Private Service

6. Run the command **SR, 00002000** to set the RN4020 module as a server

7. Run the command **PZ** to clear all settings of the private service and the private characteristics

8. Run the command **PS, 11223344556677889900AABBCCDDEEFF** to set the UUID of user-defined private service to be 0x11223344556677889900AABBCCDDEEFF

9. Run the command **PC, 010203040506070809000A0B0C0D0E0F, 18, 06** to add private characteristic 0x010203040506070809000A0B0C0D0E0F to current private service. The property of this characteristic is 0x18 (writable and could notify) and has a maximum data size of 6 bytes.

10. Run the command **R, 1** to reboot the RN4020 module and to make the new settings effective

11. Run the command **LS** to display the services

The source code using the API of RN4020 driver in |embarc| as follows.

.. code-block:: console

	rn4020_setup(rn4020_ble);
	rn4020_reset_to_factory(rn4020_ble);

	/* Set device Name */
	rn4020_set_dev_name(rn4020_ble, "IoT DK");

	/* Set device services */
	rn4020_set_services(rn4020_ble, RN4020_SERVICE_DEVICE_INFORMATION |
	                                RN4020_SERVICE_BATTERY |
	                                RN4020_SERVICE_USER_DEFINED);

	rn4020_set_features(rn4020_ble, RN4020_FEATURE_SERVER_ONLY);
	rn4020_clear_private(rn4020_ble);

	/* Set private service UUID and private characteristic */
	rn4020_set_prv_uuid(rn4020_ble, RN4020_PRV_SERV_HIGH_UUID, RN4020_PRV_SERV_LOW_UUID);
	rn4020_set_prv_char(rn4020_ble, RN4020_PRV_CHAR_HIGH_UUID, RN4020_PRV_CHAR_LOW_UUID, 0x18, 0x06, RN4020_PRIVATE_CHAR_SEC_NONE);

	/* Reboot RN4020 to make changes effective */
	rn4020_reset(rn4020_ble);

	rn4020_refresh_handle_uuid_table(rn4020_ble);


Advertise
---------

Run the command **A** to start advertisement.
The source code using the API of RN4020 driver in |embarc| as follows.

.. code-block:: console

	rn4020_advertise(rn4020_ble);


Send data
---------

Run the command **SUW, 2A19, value** to set the level of Battery.
The source code using the API of RN4020 driver in |embarc| as follows.

.. code-block:: console

	while (1) {

		rn4020_battery_set_level(rn4020_ble, battery--);

		board_delay_ms(1000, 0);
		if (battery < 30) {
			battery = 100;
		}
	}

.. note::
	About detailed usage of RN4020 BLE module, see RN4020 Bluetooth Low Energy Module User's Guide

Steps
=====

Run project
-----------

Open the serial terminal emulator in PC (for example, Tera Term), set as **115200 baud, 8 bits data, 1 stop bit and no parity**, and connect to the |iotdk| board.

Open ``cmd`` from the folder *embarc_osp/arc_labs/labs/lab6_ble_rn4020*, input the command as follow

.. code-block:: console

    make run

Then the output is displayed in the serial terminal.
|figure1|

Connection
----------

Open the BLE browser APP in smartphone (for example, LightBlue in IOS), and scan for BLE peripherals, connect the "IoT DK" device.
Then the output is displayed in the serial terminal.
|figure2|

And the device information in displayed BLE browser APP.

|figure3|

Communication
-------------
Read the data of Battery services in BLE browser APP. Check whether the data decreases gradually.

|figure4|

Write data in BLE browser APP. Check the received data in PC serial terminal.

|figure5|

|figure6|

Exercises
=========
Try to use the received data in |iotdk| board, and do some control by using GPIO. (for example, LED on/off)

.. |figure1| image:: /img/lab7_figure1.png
   :width: 550
.. |figure2| image:: /img/lab7_figure2.png
   :width: 550
.. |figure3| image:: /img/lab7_figure3.png
   :width: 300
.. |figure4| image:: /img/lab7_figure4.png
   :width: 300
.. |figure5| image:: /img/lab7_figure5.png
   :width: 300
.. |figure6| image:: /img/lab7_figure6.png
   :width: 550
