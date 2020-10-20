FROM ubuntu:18.04
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils && apt-get install -y build-essential libssl-dev git wget nano libusb-1.0.0-dev udev dos2unix && apt-get clean 
WORKDIR /work
COPY ./Scripts/install_cmake.sh ./Scripts/install_cmake.sh
RUN dos2unix ./Scripts/install_cmake.sh
RUN ./Scripts/install_cmake.sh
COPY ./Scripts/install_arm_none_eabi_toolchain.sh ./Scripts/install_arm_none_eabi_toolchain.sh
RUN dos2unix ./Scripts/install_arm_none_eabi_toolchain.sh
RUN ./Scripts/install_arm_none_eabi_toolchain.sh
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
COPY ./Scripts/build_linux.sh ./Scripts/build_linux.sh
RUN dos2unix ./Scripts/build_linux.sh
COPY Source_Code ./Source_Code