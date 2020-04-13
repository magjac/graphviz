FROM fedora:30

# Development tools
RUN yum -y groupinstall 'Development Tools'
RUN ln -s /usr/lib64/libedit.so.0 /usr/lib64/libedit.so
RUN yum -y install rpm-build
RUN yum -y install bison
RUN yum -y install byacc
RUN yum -y install flex

# Centos build utilities
RUN yum -y install libtool-ltdl-devel
RUN yum -y install ksh
RUN yum -y install cmake

# Option glut
RUN yum -y install freeglut-devel

# Option ann
RUN yum -y install ann-devel

# Option gts
RUN yum -y install gts-devel

# Option swig
RUN yum -y install swig

# Command lefty

# Command smyra

# Command gvedit
RUN yum -y install qt5-devel
RUN yum -y install ncurses-devel

# Plugin library devil
RUN yum -y install DevIL-devel

# Plugin library gd
RUN yum -y install gd-devel

# Plugin library ghostscipt
RUN yum -y install ghostscript-devel

# Plugin library gtk
RUN yum -y install gtkglext-devel

# Plugin library lasi
RUN yum -y install lasi-devel

# Plugin library pangocairo

# Plugin library poppler
RUN yum -y install poppler-glib-devel
RUN yum -y install poppler-qt5

# Plugin library rsvg
RUN yum -y install librsvg2-devel

# Plugin library webp

# Language extension gv_sharp & gv_ruby

# Language extension gv_go
RUN yum -y install golang
RUN yum -y install gcc-go

# Language extension gv_guile
RUN yum -y install guile-devel

# Language extension gv_java
RUN yum -y install java-devel

# Language extension gv_lua
RUN yum -y install lua-devel

# Language extension gv_ocaml
RUN yum -y install ocaml

# Language extension gv_perl
RUN yum -y install perl-ExtUtils-Embed

# Language extension gv_php
RUN yum -y install php-devel

# Language extension gv_python & gv_python2
RUN yum -y install python2-devel

# Language extension gv_python3
RUN yum -y install python3-devel

# Language extension gv_R
RUN yum -y install R-devel

# Language extension gv_ruby
RUN yum -y install ruby-devel

# Language extension gv_tcl

# Required in redhat/graphviz.spec.fedora.in
RUN yum -y install libXaw-devel
RUN yum -y install glade3-libgladeui-devel
RUN yum -y install libglade2-devel
RUN yum -y install mono-core
