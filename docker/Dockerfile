FROM ton/builder

RUN wget https://test.ton.org/ton-test-liteclient-full.tar.xz && \
	tar xf ton-test-liteclient-full.tar.xz && \
	mkdir lite-client-build && \
	cd lite-client-build && cmake ../lite-client && \
	cmake --build . --target test-lite-client && \
	cmake --build . --target fift && \
	cmake --build . --target install

RUN cd lite-client-build && \
	install -v -m 0755 test-lite-client /usr/local/bin/ && \
	install -v -m 0755 crypto/fift /usr/local/bin/ && \
	install -v -m 0755 crypto/func /usr/local/bin/ && \
	install -v -m 0755 crypto/test-ed25519-crypto /usr/local/bin/ && \
	install -v -m 0755 crypto/tlbc /usr/local/bin/

COPY docker-entrypoint.sh /usr/local/bin/

ENV DATADIR=/data

ENTRYPOINT ["docker-entrypoint.sh"]
 
