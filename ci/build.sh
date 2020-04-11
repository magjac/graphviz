#!/bin/sh

set -x

if test -f /etc/os-release; then
    cat /etc/os-release
    . /etc/os-release
else
    cat /etc/redhat-release
    ID=$( cat /etc/redhat-release | cut -d' ' -f1 | tr 'A-Z' 'a-z' )
    VERSION_ID=$( cat /etc/redhat-release | cut -d' ' -f3  | cut -d'.' -f1 )
fi
GV_VERSION=$( cat VERSION )
COLLECTION=$( cat COLLECTION )
if [ "${ID_LIKE}" = "debian" ]; then
    tar xfz graphviz-${GV_VERSION}.tar.gz
    (cd graphviz-${GV_VERSION}; fakeroot make -f debian/rules binary)
else
    rm -rf ${HOME}/rpmbuild
    rpmbuild -ta graphviz-${GV_VERSION}.tar.gz
fi
DIR=Packages/${COLLECTION}/${ID}/${VERSION_ID}
ARCH=$( uname -m )
mkdir -p ${DIR}/os/${ARCH}
mkdir -p ${DIR}/debug/${ARCH}
mkdir -p ${DIR}/source
if [ "${ID_LIKE}" = "debian" ]; then
    mv *.deb ${DIR}/os/${ARCH}/
    mv *.ddeb ${DIR}/debug/${ARCH}/
else
    mv ${HOME}/rpmbuild/SRPMS/*.src.rpm ${DIR}/source/
    mv ${HOME}/rpmbuild/RPMS/*/*debuginfo*rpm ${DIR}/debug/${ARCH}/
    mv ${HOME}/rpmbuild/RPMS/*/*.rpm ${DIR}/os/${ARCH}/
fi
