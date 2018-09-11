# arc_labs

[![Build Status](https://travis-ci.org/foss-for-synopsys-dwc-arc-processors/arc_labs.svg?branch=master)](https://travis-ci.org/foss-for-synopsys-dwc-arc-processors/arc_labs)

The labs of ARC university courses

## Build documentation locally

### Installation

#### Prerequisite

Install Sphinx, either from a distribution package or from PyPI. And install it from PyPI is the easier way. So you should install **Python** first.

#### Install 
```
pip install Sphinx 
pip install breathe
pip install recommonmark 
pip install sphinx_rtd_theme 
```
### Build the documentation
1. Sphinx comes with a script called sphinx-quickstart that sets up a source directory and creates a default conf.py with the most useful configuration values from a few questions it asks you. Just run

```
sphinx-quickstart
```
	and answer its questions.

2. sphinx-quickstart script creates a Makefile and a make.bat which make life even easier for you: with them you only need to run
```
make html
```
	to build HTML docs in the build directory you chose.

3. Open the index.html with a browser in build directory to check the HTML docs.


### generate PDF documents(Optional)

1. `Install TexLive`, Windows users can get it from [TeX Live](http://www.tug.org/texlive/), and Linux user need to run `sudo apt-get install texlive-full`.
2. `make latex`
3. `make latexpdf`
4. `make latexpdf`



