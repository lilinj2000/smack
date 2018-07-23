#! /bin/sh

node=`uname -n`

home_libs=~/libs/${node}

home_smack=${home_libs}/smack

./configure --prefix=${home_smack}

if test -d ${home_smack}; then
    rm -rf ${home_smack}
fi

make install

make distclean
