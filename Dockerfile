ARG firmware_build_type=Debug
ARG firmware_bin_dir=bin
FROM ubuntu:18.04
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils && apt-get install -y build-essential libssl-dev git wget nano libusb-1.0.0-dev udev && apt-get clean
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
COPY Scripts/install_cmake.sh ./
RUN ./install_cmake.sh
COPY Scripts/install_arm_none_eabi_toolchain.sh ./
RUN ./install_arm_none_eabi_toolchain.sh
WORKDIR /work
COPY Source_Code .
COPY ./build.sh ./
RUN ./build.sh -o ${firmware_bin_dir} -m ${firmware_build_type} && chmod 777 objects && chmod -x objects && chmod 777 ${firmware_bin_dir} && chmod -x ${firmware_bin_dir}