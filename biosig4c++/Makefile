####### Makefile for "BioSig for C/C++" #####################
###
###  $Id$
###  Copyright (C) 2006,2007,2008,2009,2010,2011 Alois Schloegl <alois.schloegl@gmail.com>
###  This file is part of the "BioSig for C/C++" repository
###  (biosig4c++) at http://biosig.sf.net/
###
##############################################################

##### Target: GNU/Linux

## make save2gdf   - makes converter
## make mex4o      - makes mexSLOAD, mexSOPEN for Octave (requires Octave-headers)
## make mex4m      - makes mexSLOAD, mexSOPEN for Matlab (requires Matlab, mex -setup must be configured)
## make mexw32     - makes mexSLOAD.mexw32, mexSOPEN.mexw32 (requires that mingw32, gnumex libraries from Matlab/Win32)
## make mexw64     - makes mexSLOAD.mexw64, mexSOPEN.mexw64 (requires that mce-w32, gnumex libraries from Matlab/Win64)
## make mex        - mex4o and mex4m combined
## make libbiosig  - makes libbiosig
## make biosig4python - makes python interface (requires Python)
## make biosig4java - makes Java interface (experimental)
## make biosig4php - makes PHP interface (experimental)
## make biosig4perl - makes perl interface (experimental)
## make biosig4ruby - makes ruby interface (experimental)
## make biosig4tcl - makes tcl/tk interface (experimental)
## make win32      - makes save2gdf.exe, libbiosig.a, libbiosig.dll, for MSWindows, requires MinGW
## make win64      - makes save2gdf.exe, libbiosig.a, libbiosig.dll for 64bit Windows, requires mce-w64 
## make sigviewer  - makes sigviewer

##### Target: Win32
## make win32      - makes save2gdf.exe,libbiosig.lib,libbiosig.dll, for MSWindows, requires MinGW
## make mexw32 mex/mexSLOAD.mexw32   - requires MinGW32 and GNUMEX libraries from Matlab/Win32
## make win64/sigviewer.exe 	- requires sources of SigViewer, and MinGW32 (mingw-cross-env: make suitesparse zlib qt )

##### Target: Win64
## make win64      - makes save2gdf.exe,libbiosig.lib,libbiosig.dll, for MSWindows, requires MinGW
## make mexw64 mex/mexSLOAD.mexw64   - requires MCE-W64 and GNUMEX libraries from Matlab/Win64
## make win64/sigviewer.exe 	- requires sources of SigViewer and MCE-W64, make suitesparse zlib qt 

###############################
# whether dynamic or static linking is used, can be controlled with
# LIBEXT. Setting it to 'a' links statically, 'so' links dynamically
#
LIBEXT        = a
#LIBEXT	      = so
###############################

### User-specified options: its likely you want to change this
# settings for cross compiler: tested with mingw-cross-env and mce-w64 with make suitesparse zlib qt ; 
CROSS   = /usr/local/src/mingw-cross-env/usr/bin/i686-pc-mingw32
## local mingw-cross-env 
ifeq "$(wildcard $(CROSS)-gcc)" ""
CROSS         = $(shell pwd)/../mingw-cross-env/usr/bin/i686-pc-mingw32
endif
ifeq "$(wildcard $(CROSS)-gcc)" ""
CROSS         = /usr/local/src/mingw-cross-env/usr/bin/i686-pc-mingw32
endif
CROSS64       = $(shell pwd)/../mce-w64/usr/bin/x86_64-w64-mingw32
# settings for mex files
MEX_OPTION    = -largeArrayDims # turn on for 64 bit Matlab, otherwise empty
# directory for sources of sigviewer
PathToSigViewer = ../sigviewer
PathToSigViewerWIN32 = ../sigviewer4win32
PathToSigViewerWIN64 = ../sigviewer4win64

## default options
CC            = gcc
CXX           = g++
#DEFINES      = -D=WITHOUT_SCP_DECODE
DEFINES       = -D=WITH_ZLIB -D=__4HAERTEL__ -D=WITH_FAMOS -D=WITH_CHOLMOD -D=WITHOUT_NETWORK #-D=WITH_FEF #-D=WITH_PDP -D=WITH_DICOM #-D=WITH_GDCM #-D=WITH_GSL #-D=WITH_EEPROBE #-D=SOFTCODED_PHYSDIMTABLE # if you have zlib
#DEFINES      += -D=CNT32
CFLAGS        = -pipe -fPIC -Wall -O2 $(DEFINES) -Wextra # -I cntopenlib/include/
CXXFLAGS      = -pipe -fPIC -Wall -O2 $(DEFINES) -Wextra # -I cntopenlib/include/
AR            = ar crs
INCPATH       = -I /usr/local/include/gdcm-2.0/
#		../gdcm-2.0.10/Source/DataStructureAndEncodingDefinition \
#		../gdcm-2.0.10/Source/InformationObjectDefinition  	\
#		../gdcm-2.0.10/Source/MediaStorageAndFileFormat 	\
#		../gdcm-2.0.10/Source/DataDictionary 			\
#		../gdcm-2.0.10/Source/Common
LINK          = $(CXX)
LFLAGS_dynamic = -L/usr/local/lib/ -L.
LIBS_dynamic  = -lbiosig
LFLAGS_static = -L/usr/local/lib/
LIBS_static   = libbiosig.a
ifeq ($(LIBEXT),so)
  LFLAGS      = $(LFLAGS_dynamic)
  LIBS        = $(LIBS_dynamic)
else
  LFLAGS      = $(LFLAGS_static)
  LIBS        = $(LIBS_static)
endif
ifneq (,$(findstring WITH_ZLIB, $(DEFINES)))
  LDLIBS     += -lcholmod
endif
ifneq (,$(findstring WITH_CHOLMOD, $(DEFINES)))
  LDLIBS     += -lz
endif
LIBS          += $(LDLIBS)

DELETE        = rm
COPY          = cp -f
TEMP_DIR      = /tmp/

##########################################################
## set Matlab and Octave variables
ifneq ($(shell which matlab), )
  MATLABDIR  := $(dir $(shell readlink -f $(shell which matlab) ) )
  MEX         = $(MATLABDIR)mex
  MEX_EXT    := $(shell $(MATLABDIR)mexext)
endif

# Octave - global install  (e.g. from debian package)
OCTAVE_VERSION = 
# Octave - local install (e.g. compiled from sources) 
OCTAVE_VERSION = -3.4.2

OCT           = mkoctfile$(OCTAVE_VERSION)
##########################################################

##########################################################
## set variables for Python
SWIG          = swig
PYTHONVER     = $(shell python -c "import sys; print sys.version[:3]")
##########################################################
 
##########################################################
## set variables for MinGW Crosscompiler: compile on linux binaries for windows
##
PathToMinGW   = $(dir $(CROSS))..$(nondir $(CROSS))
PathToMinGW64 = $(dir $(CROSS64))..$(nondir $(CROSS64))

MinGWCC      = $(CROSS)-gcc
MinGWCXX     = $(CROSS)-g++
MinGWDEF     = $(DEFINES) 
MinGWCFLAGS  = -pipe -fPIC  -D_REENTRANT -D=BUILD_DLL $(MinGWDEF) -I$(PathToMinGW)/include/
MinGWLIBS    = win32/libbiosig.a -L$(PathToMinGW)/lib/ -lws2_32 $(LDLIBS) # static
MinGWLINK    = $(MinGWCXX)

MinGW64CC      = $(CROSS64)-gcc
MinGW64CXX     = $(CROSS64)-g++
MinGW64CFLAGS  = -pipe -fPIC -O2 -D_REENTRANT -D=BUILD_DLL $(MinGWDEF) -I$(PathToMinGW64)/include/
MinGW64LIBS    = win64/libbiosig.a -L$(PathToMinGW64)/lib/ -lws2_32 $(LDLIBS) # static
MinGW64LINK    = $(MinGW64CXX)
##########################################################

# Versioning
MAJOR_VERSION := $(word 3, $(shell grep '\#define BIOSIG_VERSION_MAJOR' biosig.h))
MINOR_VERSION := $(word 3, $(shell grep '\#define BIOSIG_VERSION_MINOR' biosig.h))
STEPPING      := $(word 3, $(shell grep '\#define BIOSIG_VERSION_STEPPING' biosig.h))
TODAY         := $(shell date +%Y%m%d)

####### Output directory

OBJ	      = ./obj
BIN	      = $(DESTDIR)/usr/bin
LIB	      = $(DESTDIR)/usr/lib

####### Files
SOURCES       = biosig.c \
		XMLParser/tinyxml.cpp \
		XMLParser/tinyxmlparser.cpp \
		XMLParser/tinyxmlerror.cpp \
		XMLParser/tinystr.cpp \
		t210/sopen_scp_read.c \
		t210/sopen_famos_read.c \
		t210/sopen_alpha_read.c \
		t210/scp-decode.cpp \
		t220/sopen_scp_write.c \
		t220/crc4scp.c \
		t230/sopen_hl7aecg.c \
		t240/sopen_fef_read.c \
		test0/sandbox.c \
		physicalunits.c \
		biosig-network.c \
		save2gdf.c \
		biosig_client.c \
		biosig_server.c

OBJECTS       = \
		crc4scp.o \
		biosig.o \
		tinyxml.o \
		tinyxmlparser.o \
		tinyxmlerror.o \
		tinystr.o \
		sopen_scp_read.o \
		sopen_alpha_read.o \
		sopen_scp_write.o \
		sopen_hl7aecg.o \
		biosig-network.o \
		sandbox.o \

MinGWOBJECTS  = \
		win32/crc4scp.obj \
		win32/biosig.obj \
		win32/getlogin_r.obj \
		win32/tinyxml.obj \
		win32/tinyxmlparser.obj \
		win32/tinyxmlerror.obj \
		win32/tinystr.obj \
		win32/sopen_scp_read.obj \
		win32/sopen_alpha_read.obj \
		win32/sopen_scp_write.obj \
		win32/sopen_hl7aecg.obj \
		win32/biosig-network.obj \
		win32/sandbox.obj \

ifneq (,$(findstring WITH_FAMOS, $(DEFINES)))
  OBJECTS      += sopen_famos_read.o
endif
ifneq (,$(findstring WITH_FAMOS, $(MinGWDEF)))
  MinGWOBJECTS += win32/sopen_famos_read.obj
endif
ifneq (,$(findstring WITH_FEF, $(DEFINES)))
  OBJECTS      += sopen_fef_read.o
endif
ifneq (,$(findstring WITH_FEF, $(MinGWDEF)))
  MinGWOBJECTS += win32/sopen_fef_read.obj
endif
ifeq (,$(findstring WITHOUT_SCP_DECODE, $(DEFINES)))
  OBJECTS      += scp-decode.o
endif
ifeq (,$(findstring WITHOUT_SCP_DECODE, $(MinGWDEF)))
  MinGWOBJECTS += win32/scp-decode.obj
endif

MinGW64OBJECTS  = $(patsubst win32/%.obj, win64/%.obj, $(MinGWOBJECTS))

TARGET = save2gdf libbiosig.a

first: $(TARGET)
all:   $(TARGET) mex4o biosig4python win32 win64 #biosig_client biosig_server mma java tcl perl php ruby #sigviewer 
lib:	libbiosig.a win32/libbiosig.dll win32/libbiosig.a win64/libbiosig.a

#############################################################
#	Compilation: Implicit, default rules
#############################################################

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.C.o:
	$(CC) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.c.o:
	$(CC) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

%.o: %.c biosig.h biosig-dev.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"
%.o: t210/%.c biosig.h biosig-dev.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"
%.o: t220/%.c biosig.h biosig-dev.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"
%.o: t230/%.c biosig.h biosig-dev.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"
%.o: t240/%.c biosig.h biosig-dev.h
	$(CC) -c $(CFLAGS) -I t240 $(INCPATH) -o "$@" "$<"
%.o: test0/%.c biosig.h biosig-dev.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"
%.o: XMLParser/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

win32/%.obj: %.c  biosig-dev.h biosig.h 
	$(MinGWCC) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"
win32/%.obj: t210/%.c  biosig-dev.h biosig.h 
	$(MinGWCC) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"
win32/%.obj: t220/%.c  biosig-dev.h biosig.h 
	$(MinGWCC) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"
win32/%.obj: t230/%.c  biosig-dev.h biosig.h 
	$(MinGWCC) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"
win32/%.obj: t240/%.c  biosig-dev.h biosig.h 
	$(MinGWCC) -c $(MinGWCFLAGS) -I t240 $(INCPATH) -o "$@" "$<"
win32/%.obj: test0/%.c  biosig-dev.h biosig.h 
	$(MinGWCC) -c $(MinGWCFLAGS) -I t240 $(INCPATH) -o "$@" "$<"
win32/%.obj: XMLParser/%.cpp 
	$(MinGWCXX) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"

win64/%.obj: %.c  biosig-dev.h biosig.h 
	$(MinGW64CC) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"
win64/%.obj: t210/%.c  biosig-dev.h biosig.h 
	$(MinGW64CC) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"
win64/%.obj: t220/%.c  biosig-dev.h biosig.h 
	$(MinGW64CC) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"
win64/%.obj: t230/%.c  biosig-dev.h biosig.h 
	$(MinGW64CC) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"
win64/%.obj: t240/%.c  biosig-dev.h biosig.h 
	$(MinGW64CC) -c $(MinGW64CFLAGS) -I t240 $(INCPATH) -o "$@" "$<"
win64/%.obj: test0/%.c  biosig-dev.h biosig.h 
	$(MinGW64CC) -c $(MinGW64CFLAGS) -I t240 $(INCPATH) -o "$@" "$<"
win64/%.obj: XMLParser/%.cpp 
	$(MinGW64CXX) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"


#############################################################
#	event table: conversion from ascii to C code
#############################################################

biosig.o win32/biosig.obj win32/biosig.obj: eventcodes.i eventcodegroups.i units.i biosig.c biosig.h biosig-dev.h

eventcodes.i eventcodegroups.i : ../biosig/doc/eventcodes.txt
	./eventcodes.awk "$<"

units.i : ../biosig/doc/units.csv
	awk "-F," '/^[^#,]/ { split( $$0, a, "\""); sub(/\[.*\]/, "",a[2]); sub(/ *$$/, "",a[2]); print "\t{ "$$1", \"" a[2] "\"}, "}' "$<" > units.i

#############################################################
#	Compilation: exceptions, explicit rules
#############################################################

sopen_fef_read.o: t240/sopen_fef_read.c biosig-dev.h biosig.h
#	cd t240
#	#asn1c -fcompound-names -pdu=SessionArchiveSection -S /home/schloegl/cvs/asn1c/skeletons fef.asn1
#	asn1c -fcompound-names -pdu=SessionArchiveSection fef.asn1
#	#asn1c -fcompound-names iso11073-10471.asn1
#	#asn1c -fcompound-names iso11073-20601.asn1
#	cd ..
#	$(MAKE) -C t240 -f Makefile.am.sample
	$(CC) -c $(CFLAGS) -I t240 $(INCPATH) -o "$@" "$<"

sopen_hl7aecg.o: t230/sopen_hl7aecg.c biosig-dev.h biosig.h XMLParser/tinyxml.h XMLParser/tinystr.h
	$(CXX) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

sopen_scp_read.o: t210/sopen_scp_read.c biosig-dev.h biosig.h biosig.h t210/structures.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

scp-decode.o: t210/scp-decode.cpp biosig-dev.h biosig.h t210/structures.h t210/codes.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

getlogin_r.o: win32/getlogin_r.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

########### WIN32 ##################

win32/sopen_scp_read.obj: t210/sopen_scp_read.c biosig-dev.h biosig.h t210/structures.h
	$(MinGWCC) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"

win32/scp-decode.obj: t210/scp-decode.cpp biosig-dev.h biosig.h t210/structures.h t210/codes.h
	$(MinGWCXX) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"

win32/sopen_hl7aecg.obj: t230/sopen_hl7aecg.c biosig-dev.h biosig.h XMLParser/tinyxml.h XMLParser/tinystr.h
	$(MinGWCXX) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"

win32/getlogin_r.obj: win32/getlogin_r.c
	$(MinGWCC) -c $(MinGWCFLAGS) $(INCPATH) -o "$@" "$<"

win32/sigviewer.exe: win32/libbiosig.a win32/libbiosig.dll 
	#-$(COPY) ../biosig/doc/eventcodes.txt $(PathToSigViewerWIN32)/src/
	-$(DELETE) $(PathToSigViewerWIN32)/extern/include/*.h
	-$(COPY) biosig.h $(PathToSigViewerWIN32)/extern/include
	-$(DELETE) $(PathToSigViewerWIN32)/extern/lib/lib*
	-$(COPY) win32/libbiosig.a $(PathToSigViewerWIN32)/extern/lib
	sed -i 's|\([[:space:]]*-lbiosig\)\([ #\\]*\)$$|\1 -lcholmod -lz \2|' $(PathToSigViewerWIN32)/src/src.pro
	-(cd $(PathToSigViewerWIN32)/src; $(CROSS)-qmake; make)
	#-(cd $(PathToSigViewerWIN32); svn revert -R .; svn up -r 556; patch -p0 <../biosig4c++/patches/patch_sigviewer_0.5.1-as.4-DisplayHeaderInfo+EventTableAlways4Columns+SampleRateChanged2FLOAT64+libbiosigEventTable.diff; cd src; $(CROSS32)-qmake; $(MAKE);)
	-$(COPY) $(PathToSigViewerWIN32)/bin/release/sigviewer.exe win32/sigviewer-$(shell cat $(PathToSigViewerWIN32)/src/version.txt)-win32.exe

########### WIN64 ##################

win64/sopen_scp_read.obj: t210/sopen_scp_read.c biosig-dev.h biosig.h t210/structures.h
	$(MinGW64CC) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"

win64/scp-decode.obj: t210/scp-decode.cpp biosig-dev.h biosig.h t210/structures.h t210/codes.h
	$(MinGW64CXX) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"

win64/sopen_hl7aecg.obj: t230/sopen_hl7aecg.c biosig-dev.h biosig.h XMLParser/tinyxml.h XMLParser/tinystr.h
	$(MinGW64CXX) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"

win64/getlogin_r.obj: win32/getlogin_r.c
	$(MinGW64CC) -c $(MinGW64CFLAGS) $(INCPATH) -o "$@" "$<"

win64/sigviewer.exe: win64/libbiosig.a win64/libbiosig.dll 
	#-$(COPY) ../biosig/doc/eventcodes.txt $(PathToSigViewerWIN64)/src/
	-$(DELETE) $(PathToSigViewerWIN64)/extern/include/*.h
	-$(COPY) biosig.h $(PathToSigViewerWIN64)/extern/include
	-$(DELETE) $(PathToSigViewerWIN64)/extern/lib/lib*
	-$(COPY) win64/libbiosig.a $(PathToSigViewerWIN64)/extern/lib
	sed -i 's|\([[:space:]]*-lbiosig\)\([ #\\]*\)$$|\1 -lcholmod -lz \2|' $(PathToSigViewerWIN64)/src/src.pro
	-(cd $(PathToSigViewerWIN64)/src; $(CROSS64)-qmake; make)
	#-(cd $(PathToSigViewerWIN64); svn revert -R .; svn up -r 556; patch -p0 <../biosig4c++/patches/patch_sigviewer_0.5.1-as.4-DisplayHeaderInfo+EventTableAlways4Columns+SampleRateChanged2FLOAT64+libbiosigEventTable.diff; cd src; $(CROSS64)-qmake; $(MAKE);)
	-$(COPY) $(PathToSigViewerWIN64)/bin/release/sigviewer.exe win64/sigviewer-$(shell cat $(PathToSigViewerWIN64)/src/version.txt)-win64.exe


#############################################################
#	other language bindings (on Linux)
#############################################################

biosig4python : python/_biosig.so python/biosig.py

python/biosig.py python/swig_wrap.cxx: python/swig.i
	$(SWIG) -c++ -python -I/usr/include -I/usr/share/pyshared/numpy/core/include/numpy -o python/swig_wrap.cxx python/swig.i

python/_biosig.so : python/swig_wrap.cxx  libbiosig.$(LIBEXT)
	$(CXX) -c $(CXXFLAGS) python/swig_wrap.cxx -o python/swig_wrap.o -I/usr/include/python$(PYTHONVER) -I/usr/share/pyshared/numpy/core/include/numpy
	$(CXX) -shared python/swig_wrap.o  $(LFLAGS) $(LIBS) -o python/_biosig.so


java: libbiosig.$(LIBEXT) java/biosig.i
	$(MAKE) -C java 
perl: libbiosig.$(LIBEXT) perl/biosig.i
	$(MAKE) -C perl 
php: libbiosig.$(LIBEXT) php/biosig.i
	$(MAKE) -C php 
python: libbiosig.$(LIBEXT) python/swig.i
	$(MAKE) -C python 
ruby: libbiosig.$(LIBEXT) ruby/biosig.i
	$(MAKE) -C ruby 
tcl: libbiosig.$(LIBEXT) tcl/biosig.i
	$(MAKE) -C tcl 


#############################################################
#	WIN32 - BUILD
#############################################################

win32/libbiosig.lib: win32/libbiosig.a 
	$(COPY) "$<" "$@"

win32/libbiosig.a: $(MinGWOBJECTS) win32/libcnsfef.a biosig.h biosig-dev.h
	-$(DELETE) "$@"
	$(CROSS)-$(AR) "$@" $(MinGWOBJECTS) t240/*.obj

win32/libcnsfef.a:
	$(MAKE) CROSS=$(CROSS) -C t240 ../win32/libcnsfef.a 

win32/libbiosig.dll: $(MinGWOBJECTS) biosig.h biosig-dev.h
	$(MinGWLINK) -shared -fPIC  $(MinGWOBJECTS) $(MinGWLIBS) -o "$@" -Wl,--output-def,win32/libbiosig.def,--out-implib,win32/libbiosig.dll.a
	-$(COPY) "$@" $(PathToSigViewerWIN32)/extern/lib/

win32/save2gdf.exe: save2gdf.c win32/libbiosig.a
	$(MinGWLINK) $(MinGWCFLAGS) "$<" $(MinGWLIBS) -o "$@"

win32/pdp2gdf.exe: pdp2gdf.c win32/libbiosig.a
	$(MinGWLINK) $(MinGWCFLAGS) "$<" $(MinGWLIBS) -o "$@"

win32 exe: win32/save2gdf.exe win32/libbiosig.dll win32/libbiosig.a #mexw32 win32mma 


#############################################################
#	WIN64 - BUILD
#############################################################

win64/libbiosig.lib: win64/libbiosig.a 
	$(COPY) "$<" "$@"

win64/libbiosig.a: $(MinGW64OBJECTS) win64/libcnsfef.a biosig.h biosig-dev.h
	-$(DELETE) "$@"
	$(CROSS64)-$(AR) "$@" $(MinGW64OBJECTS) t240/*.o64

win64/libcnsfef.a:
	$(MAKE) CROSS64=$(CROSS64) -C t240 ../win64/libcnsfef.a 

win64/libbiosig.dll: $(MinGW64OBJECTS) biosig.h biosig-dev.h
	$(MinGW64LINK) -shared -fPIC  $(MinGW64OBJECTS) $(MinGW64LIBS) -o "$@" -Wl,--output-def,win32/libbiosig.def,--out-implib,win32/libbiosig.dll.a
	-$(COPY) "$@" $(PathToSigViewerWIN64)/extern/lib/

win64/save2gdf.exe: save2gdf.c win64/libbiosig.a
	$(MinGW64LINK) $(MinGW64CFLAGS) "$<" $(MinGW64LIBS) -o "$@"

win64/pdp2gdf.exe: pdp2gdf.c win64/libbiosig.a
	$(MinGW64LINK) $(MinGW64CFLAGS) "$<" $(MinGW64LIBS) -o "$@"

win64: win64/save2gdf.exe win64/libbiosig.dll win64/libbiosig.a #mexw64 win64mma 


#############################################################
#	GNU/Linux - BUILD
#############################################################

t240/libcnsfef.a:
#	$(MAKE) -C t240 regen		#
	$(MAKE) -C t240 libcnsfef.a	# generate t240/*.o files

libbiosig.a: $(OBJECTS) t240/libcnsfef.a biosig.h biosig-dev.h
	-$(DELETE) libbiosig.a
	$(AR) libbiosig.a $(OBJECTS) t240/*.o

libbiosig.so: $(OBJECTS) t240/libcnsfef.a biosig.h biosig-dev.h
	$(CXX) -shared -fPIC -Wl,-soname,libbiosig.so.${MAJOR_VERSION} $(LDLIBS) \
		-o libbiosig.so.${MAJOR_VERSION}.${MINOR_VERSION}.${STEPPING} $(OBJECTS) t240/*.o
	ln -sf libbiosig.so.${MAJOR_VERSION}.${MINOR_VERSION}.${STEPPING} libbiosig.so.${MAJOR_VERSION}
	ln -sf libbiosig.so.${MAJOR_VERSION} libbiosig.so

save2gdf: save2gdf.o libbiosig.$(LIBEXT) Makefile
	$(LINK) $(CXXFLAGS) save2gdf.o $(LFLAGS) $(LIBS) -o save2gdf

pdp2gdf: pdp2gdf.o libbiosig.$(LIBEXT)
	$(LINK) $(CXXFLAGS) pdp2gdf.o $(LFLAGS) $(LIBS) -o pdp2gdf

physicalunits: physicalunits.o libbiosig.$(LIBEXT)
	$(LINK) $(CXXFLAGS) physicalunits.o $(LFLAGS) $(LIBS) -o physicalunits

bscs: biosig_client biosig_server sandbox.o biosig.o
biosig_client: biosig_client.c libbiosig.$(LIBEXT) biosig-network.o Makefile
	$(LINK) $(CXXFLAGS) biosig_client.c  biosig-network.o $(LFLAGS) $(LIBS) -o biosig_client

biosig_server: biosig_server.c libbiosig.$(LIBEXT) biosig-network.o Makefile
	$(LINK) $(CXXFLAGS) biosig_server.c  biosig-network.o $(LFLAGS) $(LIBS) -o biosig_server


#############################################################
#	MathLink interface to Mathematica
#############################################################
mma: libbiosig.$(LIBEXT)
	$(MAKE) -C mma CROSS=$(CROSS) CROSS64=$(CROSS64) sload

win32mma: win32/libbiosig.a
	$(MAKE) -C mma CROSS=$(CROSS) CROSS64=$(CROSS64) sload.exe

win64mma: win64/libbiosig.a 
	$(MAKE) -C mma CROSS=$(CROSS) CROSS64=$(CROSS64) sload.w64.exe


#############################################################
#	MEX-files for Octave and Matlab
#############################################################
mex mex4m mex4o oct %.mex %.$(MEX_EXT): libbiosig.a
	$(MAKE) -C mex CROSS=$(CROSS) CROSS64=$(CROSS64) OCTAVE_VERSION=$(OCTAVE_VERSION) $@
	-cp mex/*.mex* ../biosig/t200_FileAccess/

mexw32 %.mexw32: win32/libbiosig.a
	$(MAKE) -C mex CROSS=$(CROSS) CROSS64=$(CROSS64) $(@F)
	-cp mex/*.mexw32 ../biosig/t200_FileAccess/
	
mexw64 %.mexw64: win64/libbiosig.a
	$(MAKE) -C mex CROSS=$(CROSS) CROSS64=$(CROSS64) $(@F)
	-cp mex/*.mexw64 ../biosig/t200_FileAccess/

#############################################################
#	SigViewer
#############################################################

sigviewer: $(PathToSigViewer)/bin/sigviewer 
	$(COPY) $(PathToSigViewer)/bin/release/sigviewer bin/sigviewer-$(TODAY)
	$(COPY) $(PathToSigViewer)/bin/release/sigviewer bin/sigviewer-$(shell cat $(PathToSigViewer)/src/version.txt)
	ln -sf sigviewer-$(TODAY) bin/sigviewer 

$(PathToSigViewer)/bin/sigviewer: libbiosig.$(LIBEXT) biosig.h
	-$(DELETE) $(PathToSigViewer)/extern/include/*
	-$(COPY) biosig.h $(PathToSigViewer)/extern/include
	-$(DELETE) $(PathToSigViewer)/extern/lib/lib*
	-$(COPY) libbiosig.a $(PathToSigViewer)/extern/lib
	sed -i 's|\([[:space:]]*-lbiosig\)\([ #\\]*\)$$|\1 -lcholmod -lz \2|' $(PathToSigViewer)/src/src.pro
	(cd $(PathToSigViewer)/src; qmake; $(MAKE);)
	#(cd $(PathToSigViewer); svn revert -R .; svn up -r 556; patch -p0 <../biosig4c++/patches/patch_sigviewer_0.5.1-as.4-DisplayHeaderInfo+EventTableAlways4Columns+SampleRateChanged2FLOAT64+libbiosigEventTable.diff; cd src; qmake; $(MAKE);)

docs: 	docs/save2gdf.txt  docs/mexSLOAD.txt
	asciidoc -d manpage docs/save2gdf.txt
	asciidoc -d manpage docs/mexSLOAD.txt


# for backward compatibility
save2scp: save2gdf
save2aecg: save2gdf


#############################################################
#	INSTALL and DE-INSTALL
#############################################################

distclean:
	-$(DELETE) *.a
	-$(DELETE) eventcodes.i
	-$(DELETE) *.o
	-$(DELETE) *.lib
	-$(DELETE) *.so
	-$(DELETE) *.so.*
	-$(DELETE) *.mex*
	-$(DELETE) *.oct
	-$(DELETE) t5.scp t6.scp save2gdf gztest test_scp_decode biosig_server biosig_client
	-$(DELETE) t?.[bge]df* t?.hl7* t?.scp* t?.cfw* t?.gd1* t?.*.gz *.fil $(TEMP_DIR)/t1.*
	-$(DELETE) python/swig_wrap.* python/biosig.py* python/_biosig.so
	-$(DELETE) QMakefile
	-$(DELETE) igor/libIgor.a
	-$(DELETE) win32/*.a win32/*.lib win32/libbiosig.* win32/*.obj win32/*.exe
	-$(DELETE) win64/*.a win64/*.lib win64/libbiosig.* win64/*.obj win64/*.exe
	-$(DELETE) -rf win32/zlib
	-$(MAKE) -C java clean
	-$(MAKE) -C matlab clean
	-$(MAKE) -C mma clean
	-$(MAKE) -C php clean
	-$(MAKE) -C perl clean
	-$(MAKE) -C ruby clean
	-$(MAKE) -C tcl clean
	-$(MAKE) -C mex clean

clean:
	-$(DELETE) *~
	-$(DELETE) *.a
	-$(DELETE) eventcodes.i
	-$(DELETE) *.o
	-$(DELETE) *.so
	-$(DELETE) *.so.*
	-$(DELETE) *.mex*
	-$(DELETE) *.oct
	-$(DELETE) python/biosig.py* _biosig.so
	-$(DELETE) python/swig_wrap.*
	-$(DELETE) win32/*.exe  win32/*.o* win32/*.lib win32/*.a  
	-$(DELETE) win64/*.exe  win64/*.o* win64/*.lib win64/*.a  
	-$(DELETE) t240/*.o
	-$(DELETE) t240/libcnsfef.a
	-$(DELETE) t240/libbiosig.*
	-$(DELETE) t240/*.obj
	-$(DELETE) pdp2gdf
	-$(MAKE) -C java clean
	-$(MAKE) -C matlab clean
	-$(MAKE) -C mma clean
	-$(MAKE) -C php clean
	-$(MAKE) -C perl clean
	-$(MAKE) -C ruby clean
	-$(MAKE) -C tcl clean
	-$(MAKE) -C mex clean

install_sigviewer: sigviewer
	install $(PathToSigViewer)/bin/release/sigviewer $(BIN)

install_octave: mexSLOAD.mex 
	mkdir -p  		$(DESTDIR)/usr/local/share/octave/site-m/
	install mex/mexSLOAD.mex* 	$(DESTDIR)/usr/local/share/octave/site-m/
	install mex/mexSOPEN.mex* 	$(DESTDIR)/usr/local/share/octave/site-m/

install: save2gdf libbiosig.a libbiosig.so doc/save2gdf.1
	install -d 		$(BIN)
	install save2gdf 	$(BIN)
	install heka2itx 	$(BIN)
	install save2aecg 	$(BIN)
	install save2scp  	$(BIN)
	#install rec2bin  	$(BIN)
	#install bin2rec  	$(BIN)
	install -d		$(LIB) $(DESTDIR)/usr/include
	install biosig.h    	$(DESTDIR)/usr/include
	install libbiosig.so.${MAJOR_VERSION}.${MINOR_VERSION}.${STEPPING} $(LIB)
	ln -sf libbiosig.so.${MAJOR_VERSION}.${MINOR_VERSION}.${STEPPING} $(LIB)/libbiosig.so.${MAJOR_VERSION}
	ln -sf libbiosig.so.${MAJOR_VERSION} $(LIB)/libbiosig.so
	install libbiosig.a	$(LIB)
	mkdir -p  		$(DESTDIR)/usr/share/man/man1
	install doc/*.1  	$(DESTDIR)/usr/share/man/man1
	#install libbiosig.man $(DESTDIR)/usr/share/
	#$(MAKE)  install_sigviewer
	#$(MAKE)  install_octave

remove:
	rm $(BIN)/save2gdf
	rm $(BIN)/heka2itx
	rm $(BIN)/save2scp
	rm $(BIN)/save2aecg
	#rm $(BIN)/rec2bin
	#rm $(BIN)/bin2rec
	rm $(BIN)/sigviewer
	rm $(BIN)/eventcodes.txt
	rm $(DESTDIR)/usr/include/biosig.h
	rm $(LIB)/libbiosig.*
	rm $(DESTDIR)/usr/share/man/man1/save2gdf.1
	rm $(DESTDIR)/usr/share/man/man1/mexSLOAD.1
	rm $(DESTDIR)/usr/share/man/man1/sigviewer.1
	#rm $(DESTDIR)/usr/share/man/man1/rec2bin.1
	#rm $(DESTDIR)/usr/share/man/man1/bin2rec.1


#############################################################
#	Testing
#############################################################
#	./save2gdf -V8 ~/data/test/tms32/small_test.float32.log
	./save2gdf -f=TMSi t0.scp t2.log
	cat t2.log

$(TEMP_DIR)t1.scp:
	# scp example data sets
	wget  -q -P$(TEMP_DIR) http://www.openecg.net/ECGsamples.zip
	wget  -q -P$(TEMP_DIR) http://www.openecg.net/ECGsamplesc.zip
	unzip -u $(TEMP_DIR)ECGsamples.zip "scp*.zip" -d $(TEMP_DIR)
	unzip -u $(TEMP_DIR)ECGsamplesc.zip "scp*.zip" -d $(TEMP_DIR)
	mkdir -p $(TEMP_DIR)scp/high
	mkdir -p $(TEMP_DIR)scp/highc
	mkdir -p $(TEMP_DIR)scp/redred
	mkdir -p $(TEMP_DIR)scp/redredc
	unzip -u $(TEMP_DIR)scp_high.zip -d $(TEMP_DIR)scp/high
	unzip -u $(TEMP_DIR)scp_highc.zip -d $(TEMP_DIR)scp/highc
	unzip -u $(TEMP_DIR)scp_redred.zip -d $(TEMP_DIR)scp/redred
	unzip -u $(TEMP_DIR)scp_redredc.zip -d $(TEMP_DIR)scp/redredc
	rm -rf $(TEMP_DIR)ECGsamples*.zip
	rm -rf $(TEMP_DIR)scp*.zip
	$(COPY) $(TEMP_DIR)scp/redred/PFE103.scp $(TEMP_DIR)t1.scp
	touch $(TEMP_DIR)t1.scp

$(TEMP_DIR)t1.hl7:
	# HL7aECG example data set
	wget -q -P$(TEMP_DIR) http://hl7.org/library/committees/rcrim/annecg/aECG%20Release%201%20Schema%20and%20Example%2Ezip
	unzip -u "$(TEMP_DIR)aECG Release 1 Schema and Example.zip"  -d $(TEMP_DIR)
	$(COPY) "$(TEMP_DIR)2003-12 Schema/example/Example aECG.xml" $(TEMP_DIR)t1.hl7
	rm -rf "$(TEMP_DIR)aECG Release 1 Schema and Example.zip"
	rm -rf "$(TEMP_DIR)2003-12 Schema"
	touch $(TEMP_DIR)t1.hl7

$(TEMP_DIR)t1.edf:
	# EDF+ example data set
	wget -q -P$(TEMP_DIR) http://www.edfplus.info/downloads/files/osas.zip
	unzip -u "$(TEMP_DIR)osas.zip"  -d $(TEMP_DIR)
	cp "$(TEMP_DIR)Osas2002plusQRS.edf" $(TEMP_DIR)t1.edf
	touch $(TEMP_DIR)t1.edf

asc: save2gdf
	./save2gdf -f=ASCII t0.xxx t1.asc

bin: save2gdf
	./save2gdf -f=BIN t0.xxx t1.bin

testbin: save2gdf $(TEMP_DIR)t1.edf
	./save2gdf -f=BIN $(TEMP_DIR)t1.edf $(TEMP_DIR)t1.hdr
	./save2gdf -f=BIN $(TEMP_DIR)t1.hdr $(TEMP_DIR)t2.hdr
	./save2gdf -f=GDF $(TEMP_DIR)t2.hdr $(TEMP_DIR)t2.gdf

testscp: save2gdf $(TEMP_DIR)t1.scp
	# test converting SCP data
	./save2gdf -f=HL7 $(TEMP_DIR)/t1.scp $(TEMP_DIR)/t1.scp.hl7
	./save2gdf -f=GDF $(TEMP_DIR)/t1.scp.hl7 $(TEMP_DIR)/t1.scp.hl7.gdf
	./save2gdf -f=SCP $(TEMP_DIR)/t1.scp.hl7.gdf $(TEMP_DIR)/t1.scp.hl7.gdf.scp
	./save2gdf -f=GDF $(TEMP_DIR)/t1.scp.hl7.gdf.scp $(TEMP_DIR)t1.scp.hl7.gdf.scp.gdf
	./save2gdf -f=HL7 $(TEMP_DIR)t1.scp.hl7.gdf.scp.gdf $(TEMP_DIR)t1.scp.hl7.gdf.scp.gdf.hl7
	./save2gdf -f=SCP $(TEMP_DIR)t1.scp.hl7.gdf.scp.gdf.hl7 $(TEMP_DIR)t1.scp.hl7.gdf.scp.gdf.hl7.scp
	./save2gdf -f=GDF $(TEMP_DIR)t1.scp $(TEMP_DIR)t1.scp.gdf
	./save2gdf -f=HL7 $(TEMP_DIR)t1.scp.gdf $(TEMP_DIR)t1.scp.gdf.hl7
	./save2gdf -f=SCP $(TEMP_DIR)t1.scp.gdf.hl7 $(TEMP_DIR)t1.scp.gdf.hl7.scp
	./save2gdf -f=HL7 $(TEMP_DIR)t1.scp.gdf.hl7.scp $(TEMP_DIR)t1.scp.gdf.hl7.scp.hl7
	./save2gdf -f=GDF $(TEMP_DIR)t1.scp.gdf.hl7.scp.hl7 $(TEMP_DIR)t1.scp.gdf.hl7.scp.hl7.gdf
	./save2gdf -f=SCP $(TEMP_DIR)t1.scp.gdf.hl7.scp.hl7.gdf $(TEMP_DIR)t1.scp.gdf.hl7.scp.hl7.gdf.scp

testhl7: save2gdf $(TEMP_DIR)t1.hl7
	# test converting HL7aECG data
	./save2gdf -f=GDF $(TEMP_DIR)t1.hl7 $(TEMP_DIR)t1.hl7.gdf
	./save2gdf -f=SCP $(TEMP_DIR)t1.hl7.gdf $(TEMP_DIR)t1.hl7.gdf.scp
	./save2gdf -f=HL7 $(TEMP_DIR)t1.hl7.gdf.scp $(TEMP_DIR)t1.hl7.gdf.scp.hl7
	./save2gdf -f=SCP $(TEMP_DIR)t1.hl7.gdf.scp.hl7 $(TEMP_DIR)t1.hl7.gdf.scp.hl7.scp
	./save2gdf -f=GDF $(TEMP_DIR)t1.hl7.gdf.scp.hl7.scp $(TEMP_DIR)t1.hl7.gdf.scp.hl7.scp.gdf
	./save2gdf -f=HL7 $(TEMP_DIR)t1.hl7.gdf.scp.hl7.scp.gdf $(TEMP_DIR)t1.hl7.gdf.scp.hl7.scp.gdf.hl7
	./save2gdf -f=SCP $(TEMP_DIR)t1.hl7 $(TEMP_DIR)t1.hl7.scp
	./save2gdf -f=GDF $(TEMP_DIR)t1.hl7.scp $(TEMP_DIR)t1.hl7.scp.gdf
	./save2gdf -f=HL7 $(TEMP_DIR)t1.hl7.scp.gdf $(TEMP_DIR)t1.hl7.scp.gdf.hl7
	./save2gdf -f=GDF $(TEMP_DIR)t1.hl7.scp.gdf.hl7 $(TEMP_DIR)t1.hl7.scp.gdf.hl7.gdf
	./save2gdf -f=SCP $(TEMP_DIR)t1.hl7.scp.gdf.hl7.gdf $(TEMP_DIR)t1.hl7.scp.gdf.hl7.gdf.scp
	./save2gdf -f=HL7 $(TEMP_DIR)t1.hl7.scp.gdf.hl7.gdf.scp $(TEMP_DIR)t1.hl7.scp.gdf.hl7.gdf.scp.hl7

test: $(TEMP_DIR)t1.scp save2scp save2aecg save2gdf
	# biosig4python
	# includes test for on-the-fly compression and decompression
	./save2gdf  -z  $(TEMP_DIR)t1.scp        $(TEMP_DIR)t1.scp.gdf
	./save2scp  -z 	$(TEMP_DIR)t1.scp        $(TEMP_DIR)t1.scp.scp
	./save2aecg -z 	$(TEMP_DIR)t1.scp        $(TEMP_DIR)t1.scp.hl7
	./save2gdf 	$(TEMP_DIR)t1.scp.gdf.gz $(TEMP_DIR)t1.scp.gdf.gdf
	./save2gdf 	$(TEMP_DIR)t1.scp.scp.gz $(TEMP_DIR)t1.scp.scp.gdf
	./save2gdf 	$(TEMP_DIR)t1.scp.hl7.gz $(TEMP_DIR)t1.scp.hl7.gdf
	./save2scp 	$(TEMP_DIR)t1.scp.gdf.gz $(TEMP_DIR)t1.scp.gdf.scp
	./save2scp 	$(TEMP_DIR)t1.scp.scp.gz $(TEMP_DIR)t1.scp.scp.scp
	./save2scp 	$(TEMP_DIR)t1.scp.hl7.gz $(TEMP_DIR)t1.scp.hl7.scp
	./save2aecg 	$(TEMP_DIR)t1.scp.gdf.gz $(TEMP_DIR)t1.scp.gdf.hl7
	./save2aecg	$(TEMP_DIR)t1.scp.scp.gz $(TEMP_DIR)t1.scp.scp.hl7
	./save2aecg	$(TEMP_DIR)t1.scp.hl7.gz $(TEMP_DIR)t1.scp.hl7.hl7
	# python test0/test.py

zip: $(TEMP_DIR)t1.scp save2gdf
	# test for on-the-fly compression and decompression
	# on-the-fly compression of output file
	./save2gdf -z -f=GDF $(TEMP_DIR)t1.scp t1.gdf
	./save2gdf -z -f=GDF1 $(TEMP_DIR)t1.scp t1.gd1
	./save2gdf -z -f=EDF $(TEMP_DIR)t1.scp t1.edf
	./save2gdf -z -f=BDF $(TEMP_DIR)t1.scp t1.bdf
	./save2gdf -z -f=SCP $(TEMP_DIR)t1.scp t1.scp
	./save2gdf -z -f=CFWB $(TEMP_DIR)t1.scp t1.cfw
	./save2gdf -z -f=MFER $(TEMP_DIR)t1.scp t1.mwf
	./save2gdf -z -f=HL7 $(TEMP_DIR)t1.scp t1.hl7

	gzip -c $(TEMP_DIR)t1.scp >$(TEMP_DIR)t1.scp.gz
	# on-the-fly decompression of input file
	./save2gdf -f=GDF $(TEMP_DIR)t1.scp.gz t1.gdf
	./save2gdf -f=EDF $(TEMP_DIR)t1.scp.gz t1.edf
	./save2gdf -f=BDF $(TEMP_DIR)t1.scp.gz t1.bdf
	./save2gdf -f=SCP $(TEMP_DIR)t1.scp.gz t1.scp
	./save2gdf -f=HL7 $(TEMP_DIR)t1.scp.gz t1.hl7
	./save2gdf -f=MFER $(TEMP_DIR)t1.scp.gz t1.mwf
	./save2gdf -f=CFWB $(TEMP_DIR)t1.scp.gz t1.cfw

test6: $(TEMP_DIR)t1.scp save2gdf
	$(COPY) $(TEMP_DIR)t1.scp t0.xxx
	#test7: $(TEMP_DIR)t1.edf save2gdf
	#$(COPY) $(TEMP_DIR)t1.edf t0.xxx
	./save2gdf -z -f=GDF1 t0.xxx t1.gd1
	./save2gdf -z -f=GDF t0.xxx t1.gdf
	./save2gdf -z -f=EDF t0.xxx t1.edf
	./save2gdf -z -f=BDF t0.xxx t1.bdf
	./save2gdf -z -f=SCP t0.xxx t1.scp
	./save2gdf    -f=HL7 t0.xxx t1.hl7   # -z not supported for HL7
	gzip t1.hl7
	./save2gdf -z -f=CFWB t0.xxx t1.cfw
	./save2gdf -z -f=MFER t0.xxx t1.mwf
	./save2gdf -z -f=BVA t0.xxx t1.bva
	./save2gdf -f=GDF1 t1.gd1.gz t2.gd1.gd1
	./save2gdf -f=GDF t1.gd1.gz t2.gd1.gdf
	./save2gdf -f=EDF t1.gd1.gz t2.gd1.edf
	./save2gdf -f=BDF t1.gd1.gz t2.gd1.bdf
	./save2gdf -f=SCP t1.gd1.gz t2.gd1.scp
	./save2gdf -f=HL7 t1.gd1.gz t2.gd1.hl7
	./save2gdf -f=CFWB t1.gd1.gz t2.gd1.cfw
	./save2gdf -f=GDF1 t1.gdf.gz t2.gdf.gd1
	./save2gdf -f=GDF t1.gdf.gz t2.gdf.gdf
	./save2gdf -f=EDF t1.gdf.gz t2.gdf.edf
	./save2gdf -f=BDF t1.gdf.gz t2.gdf.bdf
	./save2gdf -f=SCP t1.gdf.gz t2.gdf.scp
	./save2gdf -f=HL7 t1.gdf.gz t2.gdf.hl7
	./save2gdf -f=CFWB t1.gdf.gz t2.gdf.cfw
	./save2gdf -f=GDF1 t1.edf.gz t2.edf.gd1
	./save2gdf -f=GDF t1.edf.gz t2.edf.gdf
	./save2gdf -f=EDF t1.edf.gz t2.edf.edf
	./save2gdf -f=BDF t1.edf.gz t2.edf.bdf
	./save2gdf -f=SCP t1.edf.gz t2.edf.scp
	./save2gdf -f=HL7 t1.edf.gz t2.edf.hl7
	./save2gdf -f=CFWB t1.edf.gz t2.edf.cfw
	./save2gdf -f=GDF1 t1.bdf.gz t2.bdf.gd1
	./save2gdf -f=GDF t1.bdf.gz t2.bdf.gdf
	./save2gdf -f=EDF t1.bdf.gz t2.bdf.edf
	./save2gdf -f=BDF t1.bdf.gz t2.bdf.bdf
	./save2gdf -f=SCP t1.bdf.gz t2.bdf.scp
	./save2gdf -f=HL7 t1.bdf.gz t2.bdf.hl7
	./save2gdf -f=CFWB t1.bdf.gz t2.bdf.cfw
	./save2gdf -f=GDF1 t1.scp.gz t2.scp.gd1
	./save2gdf -f=GDF t1.scp.gz t2.scp.gdf
	./save2gdf -f=EDF t1.scp.gz t2.scp.edf
	./save2gdf -f=BDF t1.scp.gz t2.scp.bdf
#	./save2gdf -f=SCP t1.scp.gz t2.scp.scp
	./save2gdf -f=HL7 t1.scp.gz t2.scp.hl7
	./save2gdf -f=CFWB t1.scp.gz t2.scp.cfw
	./save2gdf -f=GDF1 t1.hl7.gz t2.hl7.gd1
	./save2gdf -f=GDF t1.hl7.gz t2.hl7.gdf
	./save2gdf -f=EDF t1.hl7.gz t2.hl7.edf
	./save2gdf -f=BDF t1.hl7.gz t2.hl7.bdf
	./save2gdf -f=SCP t1.hl7.gz t2.hl7.scp
	./save2gdf -f=HL7 t1.hl7.gz t2.hl7.hl7
	./save2gdf -f=CFWB t1.hl7.gz t2.hl7.cfw
	./save2gdf -f=GDF1 t1.cfw.gz t2.cfw.gd1
	./save2gdf -f=GDF t1.cfw.gz t2.cfw.gdf
	./save2gdf -f=EDF t1.cfw.gz t2.cfw.edf
	./save2gdf -f=BDF t1.cfw.gz t2.cfw.bdf
	./save2gdf -f=SCP t1.cfw.gz t2.cfw.scp
	./save2gdf -f=HL7 t1.cfw.gz t2.cfw.hl7
	./save2gdf -f=GDF1 t1.mwf.gz t2.mwf.gd1
	./save2gdf -f=GDF t1.mwf.gz t2.mwf.gdf
	./save2gdf -f=EDF t1.mwf.gz t2.mwf.edf
	./save2gdf -f=BDF t1.mwf.gz t2.mwf.bdf
	./save2gdf -f=SCP t1.mwf.gz t2.mwf.scp
	./save2gdf -f=HL7 t1.mwf.gz t2.mwf.hl7

testpybdf : $(TEMP_DIR)BDFtestfiles.zip
	unzip -u $(TEMP_DIR)BDFtestfiles.zip -d $(TEMP_DIR) && \
	python python/demo.py $(TEMP_DIR)*-256.bdf
	python python/example.py $(TEMP_DIR)*-256.bdf 256 && \
	python python/example.py $(TEMP_DIR)*-2048.bdf 2048

$(TEMP_DIR)BDFtestfiles.zip :
	wget -P$(TEMP_DIR) http://www.biosemi.com/download/BDFtestfiles.zip
