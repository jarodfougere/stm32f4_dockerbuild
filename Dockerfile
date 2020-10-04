FROM ubuntu:18.04
LABEL Description="Image for building low power outpost firmware"
WORKDIR /work

COPY . .

# setup package manager
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils 
RUN apt-get install -y build-essential libssl-dev git wget nano 
RUN apt-get clean

# arm gcc toolchain + PATH export
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
RUN Scripts/install_cmake.sh
ENTRYPOINT ./build.sh
