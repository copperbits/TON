FROM ubuntu:18.04 as builder

RUN apt-get update && \
	apt install -y cmake openssl gperf zlib1g-dev libssl-dev build-essential xz-utils curl wget clang-4.0 && \
	rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-4.0/bin/clang 400 \
 && update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-4.0/bin/clang++ 400

ENV CC clang
ENV CXX clang++

COPY ton-test-liteclient-full/lite-client /lite-client

RUN mkdir lite-client-build && \
	cd lite-client-build && cmake /lite-client && \
	cmake --build . --target test-lite-client && \
	cmake --build . --target fift && \
	cmake --build . --target install

RUN wget https://test.ton.org/ton-lite-client-test1.config.json -O /lite-client-build/config.json

FROM ubuntu:18.04

RUN apt update && \
	apt install -y openssl && \
	rm -rf /var/lib/apt/lists/*

COPY --from=builder lite-client-build/test-lite-client /usr/local/bin/ton-lite-client
COPY --from=builder lite-client-build/crypto/fift /usr/local/bin/
COPY --from=builder lite-client-build/crypto/func /usr/local/bin/
COPY --from=builder lite-client-build/crypto/test-ed25519-crypto /usr/local/bin/
COPY --from=builder lite-client-build/crypto/tlbc /usr/local/bin/
COPY --from=builder lite-client-build/config.json /etc/ton/
COPY --from=builder lite-client/crypto/fift/Asm.fif /usr/include/ton/
COPY --from=builder lite-client/crypto/fift/Fift.fif /usr/include/ton/

ENV FIFTPATH=/usr/include/ton
WORKDIR /data

ENTRYPOINT ["ton-lite-client", "-C", "/etc/ton/config.json"]
 
