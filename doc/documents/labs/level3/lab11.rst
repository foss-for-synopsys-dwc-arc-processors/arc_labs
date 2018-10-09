.. _lab11:

AWS IoT Smarthome
#################

Purpose
=======

- Show the smart home solution based on ARC and AWS IoT Cloud
- Learn how to use the AWS IoT Cloud
- Learn how to use the EMSK Board peripheral modules and on-board resources

Equipment
=========

Reguired Hardware
-----------------

- `[DesignWare ARC EM Starter Kit (EMSK)] <https://www.synopsys.com/dw/ipdir.php?ds=arc_em_starter_kit>`_

- `[Digilent PMOD WiFi (MRF24WG0MA)] <https://store.digilentinc.com/pmodwifi-wifi-interface-802-11g/>`_

- `[Digilent PMOD TMP2] <https://store.digilentinc.com/pmod-tmp2-temperature-sensor/>`_

- SD Card

- WiFi Hotspot (default SSID:**embARC**, Password:**qazwsxedc**, WPA/WPA2 encypted)

Required Software
-----------------

- Metaware or ARC GNU Toolset

- Serial port terminal (e.g. putty, tera-term or minicom)

Hardware Connection (EMSK Board)
--------------------------------

- Connect PMOD WiFi to J5, connect PMOD TMP2 to J2.

.. image:: /img/lab11_emsk_connections.png
    :alt: hardware connection

- Configure your hardware with proper core configuration.

- The hardware resources are described as per the table below.

==================== ==========================================================
 Hardware Resources  Represent
==================== ==========================================================
BUTTON R             Livingroom Lights Control
LED 0-1              Livingroom Lights Status (On or Off)
BUTTON L             Kitchen Lights Control
LED 2-3              Kitchen Lights Status (On or Off)
BUTTON X             Front Door Lock Control
LED 4-5              Front Door Lock Status (On or Off)
LED 7                WiFi connection status (On for connected, Off for not)
LED X                Node working status (toggling in 2s period if working well)
PMOD TMP2            Temperature Sensor
PMOD WiFi            Provide WiFi Connection
==================== ==========================================================

Content
========
This lab provides instructions on how to establish connection between the EMSK and
Amazon Web Services Internet of Things (AWS IoT) cloud with a simulated smart home application.
With the help of AWS IoT as a intermediate cloud platform, devices can securely interact with cloud
applications and other devices. AWS IoT also supports Message Queue Telemetry Transport (MQTT) and
provides authentication and end-to-end encryption.


.. image:: /img/lab11_smarthome_system.png
    :alt: smarthome system

This application is designed to show how to connect only 1 EMSK and AWS IoT Cloud
using embARC. The connection between EMSK and AWS IoT Cloud is secured by TLS.

Principles
==========

This lab demonstrates the smart home solution based on EMSK by establishing
the connection between EMSK Board and AWS IoT Cloud. The AWS IoT Device C SDK for the
embedded platform has been optimized and ported for embARC.

In this lab application, the peripheral modules and onboard resources of EMSK board are used
to simulate the objects which are controlled and monitored in smart home scenario. The AWS IoT
Cloud is used as the Cloud host and control platform that communicate with the EMSK
Board using MQTT protocol. A HTML5 Web APP is designed to provide
a dash board in order to monitor and control smart home nodes.

Steps
=====

Creating and setting smart home node
------------------------------------

1. Create an AWS account in `[here] <https://aws.amazon.com/>`__. Amazon offers various account levels,
   including a free tier for AWS IoT.

2. Login AWS console and choose AWS IoT.

   .. image:: /img/lab11_steps_1.png
        :alt: smarthome system

3. Choose an appropriate IoT server in the top right corner of the AWS IoT console page.

   .. image:: /img/lab11_steps_2.png
        :alt: smarthome system

4. Create your smart home node in the thing registry and generate X.509 certificate for the
   node. Create an AWS IoT policy. Then attach your smart home node and policy to the X.509
   certificate.

   .. note::
      for more details `[Using a Smart Home Iot Application with EMSK] <http://embarc.org/pdf/embARC_appnote_how_to_use_smart_home_iot.pdf>`_

   .. image:: /img/lab11_steps_3.png
        :alt: smarthome system

5. Download the root CA certificate from
   `[here] <https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem>`_.
   Rename it *rootCA.crt*. Copy the certificate files *cert.crt, privateKey.pem and rootCA.crt* to folder *cert/smarthome*.
   Insert the SD card to your PC, and copy the certificate folder cert to the SD Card root.

   .. image:: /img/lab11_steps_4.png
        :alt: smarthome system

6. Open the `[Web App] <http://embarc.org/freeboard/>`_ in a web browser and load the configuration file dashboard-smarthomesinglething.json
   obtained from `[embARC/example/freertos/iot/aws/smarthome_demo] <https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_applications/tree/master/aws_iot_smarthome>`_. The dashboard can be loaded automatically

   .. image:: /img/lab11_steps_5.png
        :alt: smarthome system

7. Click "ADD" to go to DATASOURCE page and fill up the forms.

  a) TYPE: Choose AWS IoT.
  b) NAME: Name is aws.

     .. image:: /img/lab11_steps_6.png
           :alt: smarthome system

  c) AWS IOT ENDPOINT: Go to AWS IoT console and click your smart home node "SmartHome". Copy the content
     ``XXXXXXXXXXXXXX.iot.us-east-1.amazonaws.com`` in REST API endpoint to AWS IOT ENDPOINT.

     .. image:: /img/lab11_steps_7.png
           :alt: smarthome system

  d) REGION: Copy the AWS region of your smart home node in REST API endpoint to REGION. For example,
     ``https://XXXXXXXXXXXXXX.iot.us-east1.amazonaws.com/things/SmartHome/shadow``. REGION is us-east-1.

  e) CLIENT ID: Leave it blank as default.

  f) ACCESS KEY and SECRET KEY: Go to AWS Services page and click "IAM".

     .. image:: /img/lab11_steps_8.png
           :alt: smarthome system

     Go to User page and click "Create New Users". Enter User Names "AWSIoTUser". Then
     download user security credentials, Access Key ID and Secret Access Key. Copy Access
     Key ID to ACCESS KEY and Secret Access Key to SECRET KEY.

     .. image:: /img/lab11_steps_9.png
           :alt: smarthome system

     Go to User page and click "AWSIoTUser". Click "Attach Policy" to attach "AWSIoTDataAccess" to "AWSIoTUser".

  g) THINGS: AWS IoT thing name "SmartHome".

     .. image:: /img/lab11_steps_10.png
           :alt: smarthome system

  h) Click "Save" to finish the setting.

Building and running AWS IoT smart home example
-----------------------------------------------

1. The AWS IoT thing SDK for C has been ported to embARC. Check the above steps in
   order for your IoT application to work smoothly. Go to *embARC/example/freertos/iot/aws/smarthome_demo*.
   Modify aws_iot_config.h to match your AWS IoT configuration. The macro **AWS_IOT_MQTT_HOST** can be copied
   from the REST API endpoint in AWS IoT console. For example,
   ``https://XXXXXXXXXXXXXX.iot.us-east-1.amazonaws.com/things/SmartHome/shadow``. **AWS_IOT_MQTT_HOST** should be
   ``XXXXXXXXXXXXXX.iot.us-east-1.amazonaws.com``.

  .. image:: /img/lab11_builds_1.png
        :alt: smarthome system

2. Use USB cable to connect the EMSK board. Set the baud rate of the terminal emulator to 115200.

3. Insert the SD Card into the EMSK board SD Card slot. Run the AWS IoT application using JTAG.
   Go to *embARC/example/freertos/iot/aws/smarthome_demo* in command line, input the compile command as follow:

   .. code-block:: console

       make TOOLCHAIN=gnu BD_VER=22 CUR_CORE=arcem7d run

4. FreeRTOS-based runtime environment can be loaded automatically. Wait for WiFi initialization and
   connection establishment (30 seconds or less) until the "WiFi connected" message is shown in the
   terminal emulator. "Network is ok" will be shown after the certificate files cert.crt, privateKey.pem
   and rootCA.crt are validated. The information in "reported": {} is the state of the EMSK-based
   smart home node. "Updated Accepted !!" means the connection works between the smart home node and AWS IoT cloud.

  .. image:: /img/lab11_builds_2.png
        :alt: smarthome system

4. Interact using EMSK and Dashboard. You can press the button L/R/X to see the led changes on board and also on dashboard web app.
   You can also click the lights of DESIRED STATUS pane on the dashboard app, and see the led changes on board and dashboard web app.

  .. image:: /img/lab11_builds_3.png
        :alt: smarthome system

Exercises
=========

This application is designed to show how to connect only 1 EMSK and AWS IoT Cloud using embARC.
Try to add more nodes and implement a Multi-nodes AWS IoT Smarthome Demo.

.. note::
    Related demo codes you can find `[here] <https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_applications/tree/master/aws_iot_smarthome>`__
