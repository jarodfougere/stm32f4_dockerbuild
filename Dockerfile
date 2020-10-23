FROM ubuntu:18.04
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils && apt-get install -y build-essential libssl-dev git wget nano libusb-1.0.0-dev udev dos2unix && apt-get clean 
COPY Scripts/Installs /install_scripts
WORKDIR /install_scripts
RUN dos2unix *
RUN ./install_cmake.sh
RUN ./install_arm_none_eabi_toolchain.sh
WORKDIR /