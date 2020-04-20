FROM ubuntu:19.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y

# Development tools
RUN apt-get update && apt-get install --no-install-recommends -y build-essential
RUN apt-get update && apt-get install --no-install-recommends -y git
RUN apt-get update && apt-get install --no-install-recommends -y pkg-config
RUN apt-get update && apt-get install --no-install-recommends -y autoconf
RUN apt-get update && apt-get install --no-install-recommends -y bison
RUN apt-get update && apt-get install --no-install-recommends -y libtool
RUN apt-get update && apt-get install --no-install-recommends -y flex

# Debian build utilities
RUN apt-get update && apt-get install --no-install-recommends -y quilt
RUN apt-get update && apt-get install --no-install-recommends -y d-shlibs
RUN apt-get update && apt-get install --no-install-recommends -y debhelper
RUN apt-get update && apt-get install --no-install-recommends -y fakeroot

# Option glut
RUN apt-get update && apt-get install --no-install-recommends -y freeglut3-dev

# Option gts
RUN apt-get update && apt-get install --no-install-recommends -y libgts-dev

# Option swig
RUN apt-get update && apt-get install --no-install-recommends -y swig

# Command lefty
RUN apt-get update && apt-get install --no-install-recommends -y libxaw7-dev

# Command smyra
RUN apt-get update && apt-get install --no-install-recommends -y libgtkglext1-dev
RUN apt-get update && apt-get install --no-install-recommends -y libglade2-dev

# Command gvedit
RUN apt-get update && apt-get install --no-install-recommends -y libqt5gui5
RUN apt-get update && apt-get install --no-install-recommends -y qt5-qmake
RUN apt-get update && apt-get install --no-install-recommends -y qt5-default

# Plugin library devil
RUN apt-get update && apt-get install --no-install-recommends -y libdevil-dev

# Plugin library gd
RUN apt-get update && apt-get install --no-install-recommends -y libgd-dev

# Plugin library ghostscipt
RUN apt-get update && apt-get install --no-install-recommends -y libgs-dev

# Plugin library lasi
RUN apt-get update && apt-get install --no-install-recommends -y liblasi-dev

# Plugin library poppler
RUN apt-get update && apt-get install --no-install-recommends -y libpoppler-dev
RUN apt-get update && apt-get install --no-install-recommends -y libpoppler-glib-dev

# Plugin library rsvg
RUN apt-get update && apt-get install --no-install-recommends -y librsvg2-dev

# Plugin library webp
RUN apt-get update && apt-get install --no-install-recommends -y libwebp-dev

# Language extension gv_sharp & gv_ruby
RUN apt-get update && apt-get install --no-install-recommends -y ruby

# Language extension gv_go
RUN apt-get update && apt-get install --no-install-recommends -y golang-go

# Language extension gv_guile
RUN apt-get update && apt-get install --no-install-recommends -y guile-2.2
RUN apt-get update && apt-get install --no-install-recommends -y guile-2.2-dev

# Language extension gv_lua
RUN apt-get update && apt-get install --no-install-recommends -y lua5.3
RUN apt-get update && apt-get install --no-install-recommends -y liblua5.3-dev

# Language extension gv_ocaml
RUN apt-get update && apt-get install --no-install-recommends -y ocaml

# Language extension gv_perl
RUN apt-get update && apt-get install --no-install-recommends -y libperl-dev

# Language extension gv_php
RUN apt-get update && apt-get install --no-install-recommends -y php-dev
RUN apt-get update && apt-get install --no-install-recommends -y libsodium-dev
RUN apt-get update && apt-get install --no-install-recommends -y libargon2-0-dev

# Language extension gv_python & gv_python2
RUN apt-get update && apt-get install --no-install-recommends -y python2.7-dev

# Language extension gv_python3
RUN apt-get update && apt-get install --no-install-recommends -y libpython3-dev

# Language extension gv_ruby
RUN apt-get update && apt-get install --no-install-recommends -y ruby-dev

# Language extension gv_tcl
RUN apt-get update && apt-get install --no-install-recommends -y tcl-dev

# Test utilities
RUN apt-get update && apt-get install --no-install-recommends -y python-pytest
RUN apt-get update && apt-get install --no-install-recommends -y python3-pytest

# Clean up
RUN rm -rf /var/lib/apt/lists/*
