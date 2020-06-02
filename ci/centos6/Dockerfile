FROM centos:6

# Development tools
RUN yum -y groupinstall 'Development Tools'

# Centos build utilities
RUN yum -y install \
libtool-ltdl-devel \
libedit-devel \
ksh \
cmake \
# Option xpat
expat-devel \
# Option glut
freeglut-devel \
# Option gts
# Option swig
swig \
# Command lefty
# Command smyra
# Command gvedit
&& rpm -Uvh http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm \
&& yum -y install qt5-qtbase-devel \
ncurses-devel \
# Plugin library devil
# Plugin library gd
gd-devel \
# Documentation
ghostscript \
# Plugin library
ghostscript-devel \
# Plugin library gtk
gtk2-devel \
# Plugin library lasi
# Plugin library pangocairo
# Plugin library poppler
poppler-glib-devel \
poppler-qt \
# Plugin library rsvg
librsvg2-devel \
# Plugin library webp
# Language extension gv_sharp & gv_ruby
ruby \
# Language extension gv_go
# Language extension gv_guile
guile-devel \
# Language extension gv_java
java-devel \
# Language extension gv_lua
lua-devel \
# Language extension gv_ocaml
ocaml \
# Language extension gv_perl
perl-ExtUtils-Embed \
# Language extension gv_php
php-devel \
bzip2-devel \
pcre-devel \
openssl-devel \
# Language extension gv_python & gv_python2
python2-devel \
# Language extension gv_python3
python34-devel \
# Language extension gv_ruby
ruby-devel \
# Language extension gv_tcl
tcl-devel \
# Requred in redhat/graphviz.spec.fedora.in
libICE-devel \
libSM-devel \
libXaw-devel \
tk-devel \
# Test utilities
python2-pytest \
python34-pytest \
# Clean up
&& yum clean all && rm -rf /var/cache/yum
