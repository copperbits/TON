FROM ubuntu:18.04

RUN apt-get update && \
	apt install -y cmake openssl gperf zlib1g-dev libssl-dev build-essential xz-utils curl wget clang-4.0 && \
	rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-4.0/bin/clang 400 \
  && update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-4.0/bin/clang++ 400

ENV CC clang
ENV CXX clang++
