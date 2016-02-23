#! /bin/sh

home_libs=~/libs

if test -d /llj/libs ; then
   home_libs=/llj/libs
fi

home_smack=${home_libs}/smack

./configure --prefix=${home_smack}

if test -d ${home_smack}; then
    rm -rf ${home_smack}
fi

make install

make distclean
