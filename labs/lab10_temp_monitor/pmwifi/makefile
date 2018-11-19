# Application name
APPL ?= lab_10_wifi

# Optimization Level
# Please Refer to toolchain_xxx.mk for this option
OLEVEL ?= O2

##
# Current Board And Core
##
BOARD ?= emsk
BD_VER ?= 11
CUR_CORE ?= arcem6

##
# select debugging jtag
##
JTAG ?= usb

##
# Set toolchain
##
TOOLCHAIN ?= gnu


EXT_DEV_LIST += wifi/mrf24g sensor/temperature/tcn75

STACKSZ = 4096

#
# root dir of embARC
#
EMBARC_ROOT = ../../../..

# Selected OS
OS_SEL ?= freertos
# Select Middleware Packages
MID_SEL = common lwip lwip-contrib
LWIP_CONTRIB_APPS ?= httpserver

# application source dirs
APPL_CSRC_DIR = .
APPL_ASMSRC_DIR = .

# application include dirs
APPL_INC_DIR = .

# include current project makefile
COMMON_COMPILE_PREREQUISITES += makefile

### Options above must be added before include options.mk ###
# include key embARC build system makefile
override EMBARC_ROOT := $(strip $(subst \,/,$(EMBARC_ROOT)))
include $(EMBARC_ROOT)/options/options.mk
