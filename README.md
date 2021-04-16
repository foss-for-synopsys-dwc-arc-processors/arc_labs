# Synopsys ARC Labs University Program

[![Build Status](https://travis-ci.org/foss-for-synopsys-dwc-arc-processors/arc_labs.svg?branch=master)](https://travis-ci.org/foss-for-synopsys-dwc-arc-processors/arc_labs)

The labs of Synopsys ARC university courses.

## Build documentation locally

### Software Installation

#### Prerequisite

- **Python** - Install Sphinx, either from a distribution package or from PyPI. And install it from PyPI is the easier way. 
- **Git** - You need to clone this repository by git.
- **make** - You need to build the documentation using make.

#### Install necessary python modules
```
python -m pip install --upgrade pip
pip install Sphinx 
pip install breathe
pip install recommonmark 
pip install sphinx_rtd_theme
```

### Build the documentation
1. First to fetch the code using git. Then edit the files under the `doc/documents/`. If it is the first time to edit rst file, you can learn [reStructuredText](https://github.com/ralsina/rst-cheatsheet/blob/master/rst-cheatsheet.rst) grammar first.

2. There is a `makefile` in `doc/`, with it you only need to run `make html` in `doc/` directory to build HTML docs in the build directory. And here is sample log as follows:
```
Running Sphinx v1.7.4
making output directory...
loading pickled environment... not yet created
loading intersphinx inventory from https://docs.python.org/objects.inv...
intersphinx inventory has moved: https://docs.python.org/objects.inv -> 
...
copying static files... done
copying extra files... done
dumping search index in English (code: en) ... done
dumping object inventory... done
build succeeded.
```
3. Check the link access status by run `make linkcheck`, and please fix the broken links if exist, here is sample log as follows:
```
Running Sphinx v1.8.0
loading pickled environment... done
building [mo]: targets for 0 po files that are out of date
building [linkcheck]: targets for 20 source files that are out of date
updating environment: 0 added, 0 changed, 0 removed
looking for now-outdated files... none found
pickling environment... done
preparing documents... done
writing output... [  5%] appendix/appendix
writing output... [ 10%] getting_started/getting_started
(line   11) ok        https://www.synopsys.com/designware-ip/processor-solutions/arc-processors/arc-development-tools.html
(line   17) redirect  http://www.synopsys.com/dw/ipdir.php?ds=sw_metaware - permanently to https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware
(line   15) redirect  http://www.synopsys.com/dw/ipdir.php?ds=sw_metaware - permanently to https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware
(line   22) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/releases
(line   22) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases
(line   26) ok        http://ttssh2.osdn.jp/
(line   22) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases
(line   28) ok        http://zadig.akeo.ie
(line   26) ok        https://www.putty.org/
(line   22) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/openocd
(line   94) ok        http://embarc.org/toolchain/ide/index.html
(line   94) ok        http://embarc.org/toolchain/ide/index.html
(line   24) redirect  http://store.digilentinc.com/digilent-adept-2-download-only/ - permanently to https://store.digilentinc.com/digilent-adept-2-download-only/
(line   28) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/wiki/How-to-Use-OpenOCD-on-Windows
writing output... [ 15%] glossary
writing output... [ 20%] index
writing output... [ 25%] introduction/introduction
(line   45) redirect  http://foss-for-synopsys-dwc-arc-processors.github.io/embarc_osp - permanently to http://embarc.org/embarc_osp/
(line   53) ok        https://www.synopsys.com/dw/ipdir.php?ds=arc_em_starter_kit
(line   54) ok        https://www.synopsys.com/dw/ipdir.php?ds=arc_iot_development_kit
(line   36) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp
writing output... [ 30%] labs/labs
writing output... [ 35%] labs/level1
writing output... [ 40%] labs/level1/lab1
writing output... [ 45%] labs/level1/lab2
(line   57) ok        http://embarc.org/embarc_osp/doc/build/html/introduction/introduction.html
(line   22) ok        http://embarc.org/embarc_osp/doc/build/html/getting_started/software_requirement.html
(line   65) ok        https://www.zephyrproject.org/
(line   66) ok        https://aws.amazon.com/freertos/
(line   95) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_osp/releases
writing output... [ 50%] labs/level1/lab3
writing output... [ 55%] labs/level1/lab4
writing output... [ 60%] labs/level1/lab5.
writing output... [ 65%] labs/level1/lab6
writing output... [ 70%] labs/level2
writing output... [ 75%] labs/level2/lab10
writing output... [ 80%] labs/level2/lab7
writing output... [ 85%] labs/level2/lab8
writing output... [ 90%] labs/level2/lab9
writing output... [ 95%] labs/level3
writing output... [100%] labs/level3/lab11
(line  115) ok        http://embarc.org/pdf/embARC_appnote_how_to_use_smart_home_iot.pdf
(line  128) ok        http://embarc.org/freeboard/
(line  148) broken    https://XXXXXXXXXXXXXX.iot.us-east1.amazonaws.com/things/SmartHome/shadow - HTTPSConnectionPool(host='xxxxxxxxxxxxxx.iot.us-east1.amazonaws.com', port=443): Max retries exceeded with url: /things/SmartHome/shadow (Caused by NewConnectionError('<urllib3.connection.VerifiedHTTPSConnection object at 0x04975B50>: Failed to establish a new connection: [Errno 11001] getaddrinfo failed',))
(line   97) redirect  http://aws.amazon.com/ - permanently to https://aws.amazon.com/
(line  177) broken    https://XXXXXXXXXXXXXX.iot.us-east-1.amazonaws.com/things/SmartHome/shadow - HTTPSConnectionPool(host='xxxxxxxxxxxxxx.iot.us-east-1.amazonaws.com', port=443): Max retries exceeded with url: /things/SmartHome/shadow (Caused by NewConnectionError('<urllib3.connection.VerifiedHTTPSConnection object at 0x04975FB0>: Failed to establish a new connection: [Errno 11001] getaddrinfo failed',))
(line   23) redirect  http://store.digilentinc.com/pmod-tmp2-temperature-sensor/ - permanently to https://store.digilentinc.com/pmod-tmp2-temperature-sensor/
(line   21) redirect  http://store.digilentinc.com/pmodwifi-wifi-interface-802-11g/ - permanently to https://store.digilentinc.com/pmodwifi-wifi-interface-802-11g/
(line  120) broken    https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem/ - 404 Client Error: Not Found for url: https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem/
(line  218) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_applications/tree/master/aws_iot_smarthome

build finished with problems.
Makefile:20: recipe for target 'linkcheck' failed
make: *** [linkcheck] Error 1
```
**If all the broken links are fixed, it will output as follows:**
```
... ....
(line  120) ok        https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem
(line  128) ok        http://embarc.org/freeboard/
(line  115) ok        http://embarc.org/pdf/embARC_appnote_how_to_use_smart_home_iot.pdf
(line   97) redirect  http://aws.amazon.com/ - permanently to https://aws.amazon.com/
(line   23) redirect  http://store.digilentinc.com/pmod-tmp2-temperature-sensor/ - permanently to https://store.digilentinc.com/pmod-tmp2-temperature-sensor/
(line   21) redirect  http://store.digilentinc.com/pmodwifi-wifi-interface-802-11g/ - permanently to https://store.digilentinc.com/pmodwifi-wifi-interface-802-11g/
(line  218) ok        https://github.com/foss-for-synopsys-dwc-arc-processors/embarc_applications/tree/master/aws_iot_smarthome

build succeeded.

Look for any errors in the above output or in build\linkcheck/output.txt
```

4. Open the `doc/build/html/index.html` with a browser to check the HTML docs.

### Generate PDF document(optional)

1. `Install TexLive`
    - Windows users can get it from [TeX Live](http://www.tug.org/texlive/), and Linux users need to run `sudo apt-get install texlive-full`.
2. `make latex`
3. `make latexpdf` 
4. `make latexpdf`

## Review the existing online documentation
* Online HTML: https://foss-for-synopsys-dwc-arc-processors.github.io/arc_labs/doc/build/html/introduction/introduction.html, http://embarc.org/arc_labs
* Online PDF: https://github.com/foss-for-synopsys-dwc-arc-processors/arc_labs/blob/gh-pages/doc/build/latex/arc_labs.pdf
