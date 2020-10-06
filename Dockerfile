ARG firmware_build_type=Debug
ARG firmware_bin_dir=bin
FROM ubuntu:18.04
RUN apt-get update -y && apt-get upgrade
RUN apt-get install -y apt-utils && apt-get install -y build-essential libssl-dev git wget nano libusb-1.0.0-dev udev && apt-get clean
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
ENV cmake_version=3.18
ENV cmake_build=1
ENV CMAKE_FOLDER=cmake-${cmake_version}.${cmake_build}
ENV CMAKE_ARCHIVE=${CMAKE_FOLDER}.tar.gz
ENV CMAKE_URL=https://cmake.org/files/v${cmake_version}/${CMAKE_ARCHIVE}
RUN wget $(echo $CMAKE_URL)
RUN tar -xzvf $(echo $CMAKE_ARCHIVE)
WORKDIR ${CMAKE_FOLDER}
RUN ./bootstrap
RUN make && make install
RUN unset CMAKE_ARCHIVE && unset CMAKE_FOLDER && unset CMAKE_URL
WORKDIR ..
RUN git clone https://github.com/texane/stlink
WORKDIR ./stlink
RUN cmake . && make
RUN cp ./bin/st-* /usr/local/bin && cp ./config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
RUN udevadm control --reload-rules && udevadm trigger
WORKDIR /work
COPY . .
RUN build.sh -o ${firmware_bin_dir} -m ${firmware_build_type} && chmod 777 objects && chmod -x objects && chmod 777 ${firmware_bin_dir} && chmod -x ${firmware_bin_dir}
