#!/bin/bash

CDIR=$PWD
PACKAGE_SET=""
PACKAGE_SET_INFO="@ These tools would be installed:"
PACKAGE_SET_QEMU=0
PACKAGE_SET_TOOL=0
PACKAGE_SET_NODE=0
NO_PACKAGES=0
NO_DESICION=1
VERBOSE=0

print_help() {
    echo "? Usage: setup.sh -qbvhnr"
	echo "? Options:"
	echo " -q => Install QEMU."
	echo " -b => Install Build Toolchain."
    echo " -n => Compile Node JS for Makefile codegen."
	echo " -h => Show help."
	echo " -v => Show version."
	echo " -r => Verbose output."
}

while getopts 'qbvhnr' SHELLARGUMENT; do
	case "$SHELLARGUMENT" in
		q)
			PACKAGE_SET="qemu-system-x86 ${PACKAGE_SET}"
			PACKAGE_SET_INFO=$"${PACKAGE_SET_INFO}\n - QEMU (x86)"
			PACKAGE_SET_QEMU=1
            NO_DESICION=0
			;;
		b)
			PACKAGE_SET="${PACKAGE_SET} iat make xorriso build-essential gcc-i686-linux-gnu binutils-i686-linux-gnu zip"
			PACKAGE_SET_INFO=$"${PACKAGE_SET_INFO}\n - Build Toolchain (x86)"
			PACKAGE_SET_TOOL=1
            NO_DESICION=0
			;;
        n)
            PACKAGE_SET="${PACKAGE_SET} python3-pip python3 gcc automake autoconf build-essential"
            PACKAGE_SET_INFO=$"${PACKAGE_SET_INFO}\n - Node JS\n - Build Toolchain (x86_64)"
            PACKAGE_SET_NODE=1
            NO_DESICION=0
            ;;
		h)
			print_help
			exit 0
			;;
		v)
			echo "+ Tunnel OS Setup Script"
			echo "$ Version: 1.4"
			exit 0
			;;
		r)
			VERBOSE=1
			;;
		?)
			print_help
			exit 1
			;;
	esac
done
shift "$(($OPTIND -1))"

if [ "$NO_DESICION" -eq 1 ]
then
    print_help
    exit 1
fi

if [ $PACKAGE_SET_TOOL -eq 1 ] || [ $PACKAGE_SET_QEMU -eq 1 ] || [ $PACKAGE_SET_NODE -eq 1 ]
then
    printf "$PACKAGE_SET_INFO"
    NO_PACKAGES=0
    echo
fi

read -r -p "? Do you want to continue? [y/N] " response
response=${response,,}
if [[ "$response" =~ ^(no|n)$ ]]
then
    exit 0
fi

if [ "$EUID" -ne 0 ]
then 
	echo "! Setup command should be runned as root user."
	exit 1
fi

if [ $VERBOSE -eq 1 ]
then
rm -vf /usr/include/stdarg.h /usr/include/cpuid.h
else
rm -f /usr/include/stdarg.h /usr/include/cpuid.h
fi

if [ $NO_PACKAGES -eq 0 ]
then
	if [ $VERBOSE -eq 1 ]
	then
		apt-get install $PACKAGE_SET -y;
	else
		apt-get -qq install -o=Dpkg::Use-Pty=0 $PACKAGE_SET -y 1> /dev/null;
	fi
fi

cd /usr/include
echo "* Downloading stdarg.h"
if [ $VERBOSE -eq 1 ]
then
	wget https://sites.uclouvain.be/SystInfo/usr/include/stdarg.h
else
	wget https://sites.uclouvain.be/SystInfo/usr/include/stdarg.h -q
fi
echo "* Downloading cpuid.h"
if [ $VERBOSE -eq 1 ]
then
	wget https://sites.uclouvain.be/SystInfo/usr/include/cpuid.h
else
	wget https://sites.uclouvain.be/SystInfo/usr/include/cpuid.h -q
fi

if [ $PACKAGE_SET_NODE -eq 1 ]
then
    echo "* Downloading Node JS."

    cd /root

    if [ ! -d "node" ]
    then
        if [ $VERBOSE -eq 1 ]
        then
            git clone --depth 1 --recursive https://github.com/nodejs/node.git
        else
            git clone --depth 1 --recursive https://github.com/nodejs/node.git &> /dev/null
        fi
    fi

    cd node

    echo "* Configuring Node JS."
    bash ./configure

    echo "* Compiling Node JS with $(nproc) jobs."
    make VERBOSE=$VERBOSE -j$(nproc)

    echo "* Installing Node JS."
    make install
fi

cd $CDIR
echo "** Everything is set up to compile this code and execute system on supported targets!"
