FROM ubuntu:18.04
LABEL Description="Image for building low power outpost firmware"
WORKDIR /work

# copy local source code and build dependencies into working directory
COPY cmake ./cmake
COPY build.sh ./build.sh
COPY CMakeLists.txt ./CMakeLists.txt
COPY low_power_sensor_source ./low_power_sensor_source
COPY linker ./linker
COPY scripts ./scripts

# setup package manager
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils 
RUN apt-get install -y build-essential git wget nano
RUN apt-get clean

# arm gcc toolchain + PATH export
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"


RUN scripts/install_cmake.sh

# stm32f4 HAL repo
RUN git clone https://github.com/STMicroelectronics/STM32CubeF4.git


#ENTRYPOINT ./build.sh
