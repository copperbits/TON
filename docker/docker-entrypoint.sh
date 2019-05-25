#!/bin/bash

set -e

if [[ ! -s "$DATADIR/config.json" ]]; then
	wget https://test.ton.org/ton-lite-client-test1.config.json -O $DATADIR/config.json
fi

exec "$@"

