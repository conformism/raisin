FROM ubuntu:20.04

ARG ROOT_DIR=/disks/ramfs
ARG BUILD_DIR=$ROOT_DIR/build
ARG LLVM_VERSION=12

WORKDIR $BUILD_DIR

RUN apt-get update && apt-get install -y locales \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8

ENV LANG en_US.utf8
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -y --no-install-recommends \
        build-essential \
        cmake \
		git \
        llvm-${LLVM_VERSION}-dev \
        libclang-${LLVM_VERSION}-dev \
        clang-${LLVM_VERSION}
#    && rm -rf /var/lib/apt/lists/*

RUN apt update && \
    apt install -y \
        texlive-xetex \
        pdf2svg \
		lcov \
		gcovr \
		cppcheck \
		clang-format-${LLVM_VERSION} \
		clang-tidy-${LLVM_VERSION} \
		iwyu \
		pip

RUN pip install lizard

#RUN ln -s /usr/bin/clang++-${LLVM_VERSION} /usr/bin/clang++ && \
RUN ln -s /usr/bin/clang-format-${LLVM_VERSION} /usr/bin/clang-format && \
	ln -s /usr/bin/clang-tidy-${LLVM_VERSION} /usr/bin/clang-tidy && \
	ln -s /usr/bin/llvm-cov-${LLVM_VERSION} /usr/bin/llvm-cov && \
	ln -s /usr/bin/llvm-profdata-${LLVM_VERSION} /usr/bin/llvm-profdata

RUN git clone https://github.com/catchorg/Catch2.git \
	&& cd Catch2 \
	&& cmake -Bbuild -H. -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release \
	&& cmake --build build/ --target install

RUN git clone https://github.com/aras-p/ClangBuildAnalyzer.git \
	&& cd ClangBuildAnalyzer \
	&& cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Release \
	&& cmake --build build/ --target install

# TODO is -DClang_DIR useful?
CMD cmake \
        -DCMAKE_BUILD_TYPE=Coverage \
        -DClang_DIR="/usr/lib/llvm-${LLVM_VERSION}/lib/cmake/clang" \
        .. \
    && make
