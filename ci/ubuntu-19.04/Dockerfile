FROM ubuntu:19.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y

# Development tools
RUN apt-get install -y build-essential
RUN apt-get install -y git
RUN apt-get install -y pkg-config
RUN apt-get install -y autoconf
RUN apt-get install -y bison
RUN apt-get install -y libtool
RUN apt-get install -y flex

# Debian build utilities
RUN apt-get install -y quilt
RUN apt-get install -y d-shlibs
RUN apt-get install -y debhelper

# Option glut
RUN apt-get install -y freeglut3-dev

# Option gts
RUN apt-get install -y libgts-dev

# Option swig
RUN apt-get install -y swig

# Command lefty
RUN apt-get install -y libxaw7-dev

# Command smyra
RUN apt-get install -y libgtkglext1-dev
RUN apt-get install -y libglade2-dev

# Command gvedit
RUN apt-get install -y libqt5gui5
RUN apt-get install -y qt5-qmake
RUN apt-get install -y qt5-default

# Plugin library devil
RUN apt-get install -y libdevil-dev

# Plugin library gd
RUN apt-get install -y libgd-dev

# Plugin library ghostscipt
RUN apt-get install -y libgs-dev

# Plugin library lasi
RUN apt-get install -y liblasi-dev

# Plugin library poppler
RUN apt-get install -y libpoppler-dev
RUN apt-get install -y libpoppler-glib-dev

# Plugin library rsvg
RUN apt-get install -y librsvg2-dev

# Plugin library webp
RUN apt-get install -y libwebp-dev

# Language extension gv_sharp & gv_ruby
RUN apt-get install -y ruby

# Language extension gv_go
RUN apt-get install -y golang-go

# Language extension gv_guile
RUN apt-get install -y guile-2.2
RUN apt-get install -y guile-2.2-dev

# Language extension gv_lua
RUN apt-get install -y lua5.3
RUN apt-get install -y liblua5.3-dev

# Language extension gv_ocaml
RUN apt-get install -y ocaml

# Language extension gv_perl
RUN apt-get install -y libperl-dev

# Language extension gv_php
RUN apt-get install -y php-dev
RUN apt-get install -y libsodium-dev
RUN apt-get install -y libargon2-0-dev

# Language extension gv_python & gv_python2
RUN apt-get install -y python2.7-dev

# Language extension gv_python3
RUN apt-get install -y libpython3-dev

# Language extension gv_ruby
RUN apt-get install -y ruby-dev

# Language extension gv_tcl
RUN apt-get install -y tcl-dev
