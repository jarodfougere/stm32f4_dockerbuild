FROM ubuntu:18.04 AS base_image
WORKDIR /work
COPY . .

FROM base_image AS base_build
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils 
RUN apt-get install -y build-essential libssl-dev git wget nano 
RUN apt-get clean

FROM base_build AS cmake_armgcc_toolchains
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
RUN Scripts/install_cmake.sh

FROM cmake_armgcc_toolchains
ENTRYPOINT Scripts/build.sh
