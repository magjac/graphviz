FROM centos:7

# Development tools
RUN yum -y groupinstall 'Development Tools'
RUN ln -s /usr/lib64/libedit.so.0 /usr/lib64/libedit.so

# Centos build utilities
RUN yum -y install libtool-ltdl-devel
RUN yum -y install ksh
RUN yum -y install cmake

# Option glut
RUN yum -y install freeglut-devel

# Option gts

# Option swig
RUN yum -y install swig

# Command lefty

# Command smyra

# Command gvedit
RUN yum -y install qt5-qtbase-devel
RUN yum -y install ncurses-devel

# Plugin library devil

# Plugin library gd
RUN yum -y install gd-devel

# Plugin library ghostscipt
RUN yum -y install ghostscript-devel

# Plugin library gtk
RUN yum -y install gtk2-devel

# Plugin library lasi

# Plugin library pangocairo

# Plugin library poppler
RUN yum -y install poppler-glib-devel
RUN yum -y install poppler-qt

# Plugin library rsvg
RUN yum -y install librsvg2-devel

# Plugin library webp

# Language extension gv_sharp & gv_ruby

# Language extension gv_go

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
RUN yum -y install bzip2-devel
RUN yum -y install openssl-devel
RUN yum -y install libxml2-devel

# Language extension gv_python & gv_python2
RUN yum -y install python2-devel

# Language extension gv_python3
RUN yum -y install python3-devel

# Language extension gv_ruby
RUN yum -y install ruby-devel

# Language extension gv_tcl
RUN yum -y install tcl-devel

# Requred in redhat/graphviz.spec.fedora.in
RUN yum -y install libICE-devel
RUN yum -y install libSM-devel
RUN yum -y install libXaw-devel
RUN yum -y install tk-devel
