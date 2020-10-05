# THESE ARGUMENTS HAVE TO COME BEFORE THE FIRST IMAGE LAYER SO THEY PERSIST ACROSS BUILD STAGES
ARG firmware_build_type
ARG firmware_bin_dir
ARG rebuild

FROM ubuntu:18.04 as base
WORKDIR /work
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils && apt-get install -y build-essential libssl-dev git wget nano && apt-get clean
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
COPY Scripts/install_cmake.sh ./Scripts/install_cmake.sh
RUN Scripts/install_cmake.sh

FROM base
ARG firmware_build_type
ARG firmware_bin_dir
ARG rebuild

COPY / /
WORKDIR /work
COPY . .
RUN Scripts/build.sh -o ${firmware_bin_dir} -m ${firmware_build_type} ${rebuild}
