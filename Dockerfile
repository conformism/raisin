FROM ubuntu:20.04

ARG BUILD_DIR=/disks/ramfs
ARG LLVM_VERSION=10

WORKDIR $BUILD_DIR

RUN apt-get update && apt-get install -y locales \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8

ENV LANG en_US.utf8
ENV DEBIAN_FRONTEND=noninteractive \
    LLVM_CONFIG="/usr/lib/llvm-${LLVM_VERSION}/bin/llvm-config"

RUN apt update && \
    apt install -y --no-install-recommends \
        build-essential \
        cmake \
        llvm-${LLVM_VERSION}-dev \
        libclang-${LLVM_VERSION}-dev \
    && rm -rf /var/lib/apt/lists/*

COPY cfg-clang cfg-clang

RUN make -C cfg-clang
