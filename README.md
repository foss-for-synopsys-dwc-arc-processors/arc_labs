# arc_labs

[![Build Status](https://travis-ci.org/foss-for-synopsys-dwc-arc-processors/arc_labs.svg?branch=master)](https://travis-ci.org/foss-for-synopsys-dwc-arc-processors/arc_labs)

The labs of ARC university courses

## Build documentation locally

### Installation

#### Prerequisite

- **Python** - Install Sphinx, either from a distribution package or from PyPI. And install it from PyPI is the easier way. 
-  **Git** - You need to clone this repository by git. 

#### Install necessary python libraries
```
pip install Sphinx 
pip install breathe
pip install recommonmark 
pip install sphinx_rtd_theme 
```
### Build the documentation
1. First to fetch the code from git. Then edit the files under the `doc/documents/`. If it is the first time to edit rst file, you can learn [reStructuredText](https://github.com/ralsina/rst-cheatsheet/blob/master/rst-cheatsheet.rst) first.

2. There is a makefile in `doc`, with it you only need to run `make html` to build HTML docs in the build directory. And the following is the log:
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
3. Open the index.html with a browser in build directory to check the HTML docs.

### Generate PDF document(optional)

1. `Install TexLive`
    - Windows users can get it from [TeX Live](http://www.tug.org/texlive/), and Linux users need to run `sudo apt-get install texlive-full`.
2. `make latex`
3. `make latexpdf` 
4. `make latexpdf`



