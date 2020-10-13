ARG firmware_build_type=Debug
ARG firmware_bin_dir=bin
FROM ubuntu:18.04
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils && apt-get install -y build-essential libssl-dev git wget nano libusb-1.0.0-dev udev && apt-get clean
COPY Scripts/install_cmake.sh ./
RUN ./install_cmake.sh
COPY Scripts/install_arm_none_eabi_toolchain.sh ./
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
RUN ./install_arm_none_eabi_toolchain.sh
WORKDIR /work
COPY ./Scripts/build.sh ./
COPY Source_Code ./Source_Code
ARG firmware_build_type
ARG firmware_bin_dir
RUN ./build.sh -o ${firmware_bin_dir} -m ${firmware_build_type}