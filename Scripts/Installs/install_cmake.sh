#!/bin/bash
# bash script to install cmake on ubuntu 18.04

if [ -d tmp ]; then 
    rm -r tmp
fi

mkdir tmp
pushd tmp > /dev/null
function cleanup()
{   
    popd > /dev/null
    while (( $? == 0 )); do popd > /dev/null; done
    rm -rf tmp
}
trap cleanup EXIT

CMAKE_VERSION=3.18 
CMAKE_BUILD=1
while getopts ":v:b:" opt; do
    case ${opt} in
    v)  
        CMAKE_VERSION=$OPTARG
        ;;
    b) 
        CMAKE_BUILD=$OPTARG
        ;;
    \?) 
        echo "Unsupported CLI option ${opt} with value ${OPTARG}"
        ;;
    esac
done

declare -a required_packages=("wget" "gcc" "make" "nano" "build_essential" "libssl-dev" "tar" "cut")
UPDATED=0
for pkg in ${required_packages[@]}; do
    echo "checking if $pkg is installed..."
    which $pkg
    if [ $? -ne 0 ]; then
        if [ $UPDATED -eq 0 ]; then
            apt-get update
            UPDATED=1
        fi
        echo "  ok"
        echo ""
        apt-get install -y $pkg
    fi
done
EXISTING_CMAKE_VERSION=$(cmake --version)
if [ "$EXISTING_CMAKE_VERSION" -lt "$CMAKE_VERSION" ]; then
    apt-get remove cmake
fi
CMAKE_FOLDER=cmake-${CMAKE_VERSION}.${CMAKE_BUILD}
CMAKE_ARCHIVE=${CMAKE_FOLDER}.tar.gz
CMAKE_URL=https://cmake.org/files/v${CMAKE_VERSION}/${CMAKE_ARCHIVE}
wget $CMAKE_URL && tar -xzvf $CMAKE_ARCHIVE
if [ $? -ne 0 ]; then
    echo "Could not download from $CMAKE_URL"
    exit 1
fi
pushd $CMAKE_FOLDER > /dev/null
./bootstrap
make -j $(nproc)
make install -j $(nproc)
popd > /dev/null
INSTALLED_CMAKE_VERSION=$(cmake --version | cut -d " " -f 3 | head -n 1)
INSTALLED_CMAKE_VERSION_MAJOR=$(echo $INSTALLED_CMAKE_VERSION | cut -d "." -f 1)
INSTALLED_CMAKE_VERSION_MINOR=$(echo $INSTALLED_CMAKE_VERSION | cut -d "." -f 2)
if [ $(echo "${INSTALLED_CMAKE_VERSION_MAJOR}.${INSTALLED_CMAKE_VERSION_MINOR}") = $(echo "$CMAKE_VERSION") ]; then
    echo "cmake was installed successfully!"
    cmake --version
else
    echo "Error installing cmake"
    exit -1
fi
popd > /dev/null