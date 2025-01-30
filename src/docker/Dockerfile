FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get update

RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get upgrade -y

RUN apt-get install -y \
    wget \
    binutils \
    pkg-config

RUN apt-get install -y \
    gcc-8 \
    g++-8 \
    gcc-8-multilib \
    g++-8-multilib \
    libstdc++-8-dev:i386

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-8 \
    --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-8 \
    --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-8 \
    --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-8

RUN apt-get install -y \
    linux-libc-dev:i386 \
    linux-libc-dev

RUN apt-get install -y \
    libc6:i386 \
    libc6-dev:i386

RUN apt-get install -y \
    lib32gcc1 \
    lib32stdc++6

RUN apt-get install -y \
    build-essential \
    dos2unix \
    zlib1g-dev:i386 \
    zlib1g-dev

RUN apt-get install -y \
    libssl1.0.0:i386 \
    libssl1.0-dev:i386 \
    libssl1.0.0 \
    libssl1.0-dev

RUN cd /tmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.19.0/cmake-3.19.0-Linux-x86_64.sh && \
    chmod +x cmake-3.19.0-Linux-x86_64.sh && \
    ./cmake-3.19.0-Linux-x86_64.sh --skip-license --prefix=/usr && \
    rm cmake-3.19.0-Linux-x86_64.sh

RUN mkdir -p /usr/lib/i386-linux-gnu && \
    ln -sf /usr/lib/i386-linux-gnu/libssl.so.1.0.0 /usr/lib/i386-linux-gnu/libssl.so && \
    ln -sf /usr/lib/i386-linux-gnu/libcrypto.so.1.0.0 /usr/lib/i386-linux-gnu/libcrypto.so

RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY . .

RUN mkdir -p cmake build && \
    chmod -R 777 /build

CMD ["bash", "cmake/compile.sh"]