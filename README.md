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

3. Open the `doc/build/html/index.html` with a browser to check the HTML docs.

### Generate PDF document(optional)

1. `Install TexLive`
    - Windows users can get it from [TeX Live](http://www.tug.org/texlive/), and Linux users need to run `sudo apt-get install texlive-full`.
2. `make latex`
3. `make latexpdf` 
4. `make latexpdf`

## Review the existing online documentation
* Online HTML: http://embarc.org/arc_labs
* Online PDF: https://github.com/foss-for-synopsys-dwc-arc-processors/arc_labs/blob/gh-pages/doc/build/latex/arc_labs.pdf
