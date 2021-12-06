ARG DEBIAN_BASE_DIST=ubuntu:20.04
FROM ${DEBIAN_BASE_DIST} as base

ARG ROOT_DIR=/workdir
ARG BUILD_DIR=${ROOT_DIR}/build
ARG LLVM_VERSION=12

WORKDIR $ROOT_DIR

ENV LANG=en_US.utf8 \
    DEBIAN_FRONTEND=noninteractive \
    LLVM_DIR="/usr/lib/llvm-12/lib/cmake/llvm" \
    Clang_DIR="/usr/lib/llvm-12/lib/cmake/clang"

RUN apt-get update \
    && apt-get install \
        -y --no-install-recommends \
        locales \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8 \
    && apt-get update \
    && apt-get install --yes --no-install-recommends \
        build-essential \
        cmake \
		git \
        llvm-${LLVM_VERSION}-dev \
        libclang-${LLVM_VERSION}-dev \
        clang-${LLVM_VERSION} \
        texlive-xetex \
        pdf2svg \
		lcov \
		gcovr \
		cppcheck \
		clang-format-${LLVM_VERSION} \
		clang-tidy-${LLVM_VERSION} \
		iwyu \
		doxygen \
		graphviz \
		plantuml \
		python3-jinja2 \
		python3-pygments \
		pip \
        gdb \
        python3-dev \
        python3-pip \
        python3-setuptools \
        libglib2.0-dev \
        libc6-dbg \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && pip install \
		lizard==1.17.9 \
		codechecker==6.18.0 \
		coverxygen==1.7.0 \
        pwndbg==0.1.1 \
    && ln -sf "/usr/bin/clang-${LLVM_VERSION}" "/usr/bin/clang" \
    && ln -sf "/usr/bin/clang-${LLVM_VERSION}" "/usr/bin/clang++" \
    && ln -s /usr/bin/clang-format-${LLVM_VERSION} /usr/bin/clang-format \
	&& ln -s /usr/bin/clang-tidy-${LLVM_VERSION} /usr/bin/clang-tidy \
	&& ln -s /usr/bin/llvm-cov-${LLVM_VERSION} /usr/bin/llvm-cov \
	&& ln -s /usr/bin/llvm-profdata-${LLVM_VERSION} /usr/bin/llvm-profdata \
    && echo "source $PWD/gdbinit.py" >> ~/.gdbinit

FROM base as catch2
ARG CATCH2_BUILD_PATH=${CATCH2_BUILD_PATH}
ARG CATCH2_VERSION=v3.0.0-preview3
RUN git clone https://github.com/catchorg/Catch2.git \
        --depth 1 -b ${CATCH2_VERSION} /tmp/catch2-build/ \
    && cd /tmp/catch2-build/  \
	&& cmake -Bbuild/ -H. -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release

FROM base as clangbuildanalyzer
ARG CLANGBUILDANALYZER_BUILD_PATH=${CLANGBUILDANALYZER_BUILD_PATH}
ARG CLANGBUILDANALYZER_VERSION=5d40542
RUN git clone https://github.com/aras-p/ClangBuildAnalyzer.git /tmp/clangbuildanalyzer-build/ \
    && cd /tmp/clangbuildanalyzer-build/ \
	&& git checkout ${CLANGBUILDANALYZER_VERSION} \
	&& cmake -Bbuild/ -H. -DCMAKE_BUILD_TYPE=Release

FROM base as uncrustify
ARG UNCRUSTIFY_BUILD_PATH=${UNCRUSTIFY_BUILD_PATH}
ARG UNCRUSTIFY_VERSION=uncrustify-0.73.0
RUN git clone https://github.com/uncrustify/uncrustify \
        --depth 1 -b ${UNCRUSTIFY_VERSION} /tmp/uncrustify-build/ \
    && cd /tmp/uncrustify-build/ \
	&& cmake -Bbuild/ -H. -DCMAKE_BUILD_TYPE=Release

FROM base as main

ARG ROOT_DIR=/workdir
ARG BUILD_DIR=${ROOT_DIR}/build

COPY --from=catch2 /tmp/catch2-build/ /tmp/catch2-build/
COPY --from=clangbuildanalyzer /tmp/clangbuildanalyzer-build/ /tmp/clangbuildanalyzer-build/
COPY --from=uncrustify /tmp/uncrustify-build/ /tmp/uncrustify-build/


RUN cd /tmp/catch2-build/ \
    && cmake --build "build" --target install \
	&& cd /tmp/clangbuildanalyzer-build/ \
    && cmake --build "build" --target install \
	&& cd /tmp/uncrustify-build/ \
	&& cmake --build "build" --target install \
    && rm -rf /tmp/*

WORKDIR "${BUILD_DIR}"
