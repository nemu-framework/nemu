# This file was automatically generated by bakefile.
#
# Any manual changes will be lost if it is regenerated,
# modify the source .bkl file instead if possible.

# You may define standard make variables such as CFLAGS or
# CXXFLAGS to affect the build. For example, you could use:
#
#      make CXXFLAGS=-g
#
# to build with debug information. The full list of variables
# that can be used by this makefile is:
# AR, CC, CFLAGS, CPPFLAGS, CXX, CXXFLAGS, LD, LDFLAGS, MAKE, RANLIB.

# You may also specify config=Debug|Release
# or their corresponding lower case variants on make command line to select
# the corresponding default flags values.
ifeq ($(config),debug)
override config := Debug
endif
ifeq ($(config),release)
override config := Release
endif
ifeq ($(config),Debug)
override CPPFLAGS += -DDEBUG
override CFLAGS += -g -O0
override CXXFLAGS += -g -O0
override LDFLAGS += -g
else ifeq ($(config),Release)
override CPPFLAGS += -DNDEBUG
override CFLAGS += -O2
override CXXFLAGS += -O2
else ifneq (,$(config))
$(warning Unknown configuration "$(config)")
endif
#
# Additionally, this makefile is customizable with the following
# settings:
#
#      ISHIKO_CPP_BASEPLATFORM_ROOT          Path to the Ishiko/C++ BasePlatform installation
#      ISHIKO_CPP_ERRORS_ROOT                Path to the Ishiko/C++ Errors installation
#      ISHIKO_CPP_IO_ROOT                    Path to the Ishiko/C++ IO installation
#      ISHIKO_CPP_BOOST_ROOT                 Path to the Boost installation
#      ISHIKO_CPP_FILESYSTEM_ROOT            Path to the Ishiko/C++ FileSystem installation
#      ISHIKO_CPP_FMT_ROOT                   Path to the fmt installation
#      ISHIKO_CPP_LOGGING_ROOT               Path to the Ishiko Logging installation
#      ISHIKO_CPP_MEMORY_ROOT                Path to the Ishiko/C++ Memory installation
#      ISHIKO_CPP_TEXT_ROOT                  Path to the Ishiko/C++ Text installation
#      ISHIKO_CPP_BOTAN_ROOT                 Path to the Botan installation
#      ISHIKO_CPP_NETWORKING_ROOT            Path to the Ishiko/C++ Networking installation
#      ISHIKO_CPP_TIME_ROOT                  Path to the Ishiko/C++ Time installation
#      NEMU_CPP_CORE_ROOT                    Path to the Nemu installation
#      ISHIKO_CPP_PROCESS_ROOT               Path to the Ishiko/C++ Process installation
#      ISHIKO_CPP_MSTCH_ROOT                 Path to the mstch installation
#      ISHIKO_CPP_CONFIGURATION_ROOT         Path to the Ishiko/C++ Configuration installation
#      ISHIKO_CPP_TYPES_ROOT                 Path to the Ishiko/C++ Types installation
#      ISHIKO_CPP_HTTP_ROOT                  Path to the Ishiko/C++ HTTP installation
#      NEMU_CPP_WEBFRAMEWORK_ROOT            Path to the Nemu WebFramework installation
#      NEMU_CPP_MUSTACHETEMPLATEENGINE_ROOT  Path to the Nemu installation

# Use "make RANLIB=''" for platforms without ranlib.
RANLIB ?= ranlib

CC := cc
CXX := c++

_true  := true
_false :=
_not    = $(if $(1),$(_false),$(_true_))
_equal  = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))


# ------------
# Configurable settings:
# 

# Path to the Ishiko/C++ BasePlatform installation
ISHIKO_CPP_BASEPLATFORM_ROOT ?= $(ISHIKO_CPP_ROOT)/base-platform
# Path to the Ishiko/C++ Errors installation
ISHIKO_CPP_ERRORS_ROOT ?= $(ISHIKO_CPP_ROOT)/errors
# Path to the Ishiko/C++ IO installation
ISHIKO_CPP_IO_ROOT ?= $(ISHIKO_CPP_ROOT)/io
# Path to the Boost installation
ISHIKO_CPP_BOOST_ROOT ?= $(BOOST_ROOT)
# Path to the Ishiko/C++ FileSystem installation
ISHIKO_CPP_FILESYSTEM_ROOT ?= $(ISHIKO_CPP_ROOT)/filesystem
# Path to the fmt installation
ISHIKO_CPP_FMT_ROOT ?= $(FMT_ROOT)
# Path to the Ishiko Logging installation
ISHIKO_CPP_LOGGING_ROOT ?= $(ISHIKO_CPP_ROOT)/logging
# Path to the Ishiko/C++ Memory installation
ISHIKO_CPP_MEMORY_ROOT ?= $(ISHIKO_CPP_ROOT)/memory
# Path to the Ishiko/C++ Text installation
ISHIKO_CPP_TEXT_ROOT ?= $(ISHIKO_CPP_ROOT)/text
# Path to the Botan installation
ISHIKO_CPP_BOTAN_ROOT ?= $(BOTAN_ROOT)
# Path to the Ishiko/C++ Networking installation
ISHIKO_CPP_NETWORKING_ROOT ?= $(ISHIKO_CPP_ROOT)/networking
# Path to the Ishiko/C++ Time installation
ISHIKO_CPP_TIME_ROOT ?= $(ISHIKO_CPP_ROOT)/time
# Path to the Nemu installation
NEMU_CPP_CORE_ROOT ?= $(NEMU_CPP_ROOT)/core
# Path to the Ishiko/C++ Process installation
ISHIKO_CPP_PROCESS_ROOT ?= $(ISHIKO_CPP_ROOT)/process
# Path to the mstch installation
ISHIKO_CPP_MSTCH_ROOT ?= $(MSTCH_ROOT)
# Path to the Ishiko/C++ Configuration installation
ISHIKO_CPP_CONFIGURATION_ROOT ?= $(ISHIKO_CPP_ROOT)/configuration
# Path to the Ishiko/C++ Types installation
ISHIKO_CPP_TYPES_ROOT ?= $(ISHIKO_CPP_ROOT)/types
# Path to the Ishiko/C++ HTTP installation
ISHIKO_CPP_HTTP_ROOT ?= $(ISHIKO_CPP_ROOT)/http
# Path to the Nemu WebFramework installation
NEMU_CPP_WEBFRAMEWORK_ROOT ?= $(NEMU_CPP_ROOT)/web-framework
# Path to the Nemu installation
NEMU_CPP_MUSTACHETEMPLATEENGINE_ROOT ?= $(NEMU_CPP_ROOT)/mustache-template-engine

# ------------

all: ../bakefile/../../lib/lib$(if $(call _equal,$(config),Debug),Nemu-d,Nemu).a

../bakefile/../../lib/lib$(if $(call _equal,$(config),Debug),Nemu-d,Nemu).a:
	$(AR) rc $@ 
	$(RANLIB) $@

clean:
	rm -f ../bakefile/../../lib/lib$(if $(call _equal,$(config),Debug),Nemu-d,Nemu).a

.PHONY: all clean
