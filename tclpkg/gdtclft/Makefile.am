# $Id$ $Revision$
## Process this file with automake to produce Makefile.in

SUBDIRS = demo

pdfdir = $(pkgdatadir)/doc/pdf
pkgtcldir = $(pkglibdir)/tcl

AM_CPPFLAGS = \
	 -I$(top_srcdir) \
	@GDLIB_CFLAGS@ @TCL_INCLUDES@

LIBS = @LIBS@ -lc

AM_CFLAGS = @TCL_CFLAGS@

man = gdtclft.3tcl
pdf = gdtclft.3tcl.pdf

if WITH_LIBGD
if WITH_TCL
pkgtcl_LTLIBRARIES = libgdtclft.la
man_MANS = $(man)
pdf_DATA = $(pdf)
noinst_LTLIBRARIES = libgdtclft_C.la
endif
endif

libgdtclft_la_SOURCES = gdtclft.c
libgdtclft_C_la_SOURCES = gdtclft.c

libgdtclft_la_LDFLAGS = -no-undefined

if WITH_LIBGD
libgdtclft_la_LIBADD = \
	$(top_builddir)/tclpkg/tclstubs/libtclstubs_C.la \
	$(GDLIB_LIBS)

if WITH_TCL
all-local: pkgIndex.tcl

pkgIndex.tcl: libgdtclft.la
	sh $(top_srcdir)/tclpkg/mkpkgindex.sh libgdtclft.la Gdtclft $(VERSION)

test:
	echo 'load .libs/libgdtclft$(TCL_SHLIB_SUFFIX) Gdtclft ; cd tests ; source all' | tclsh8.3
endif
endif

gdtclft.3tcl.pdf: gdtclft.3tcl.ps
	@PS2PDF@ $< $@

gdtclft.3tcl.ps: $(srcdir)/gdtclft.3tcl
	@GROFF@ -Tps -man $< >$@

EXTRA_DIST = $(man) $(pdf)

CLEANFILES = pkgIndex.tcl

DISTCLEANFILES = $(pdf) gdtclft.3tcl.ps
