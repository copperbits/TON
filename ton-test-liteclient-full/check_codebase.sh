#!/bin/bash

ARCHIVE_NAME=ton-test-liteclient-full.tar.xz
SOURCES=https://test.ton.org/$ARCHIVE_NAME
SOURCE_IN_ARCHIVE=lite-client
SOURCE_DIR=lite-client
CHECK_DIR=lite-client-check

DIFF_CONFIG=lite-client-check-exclude.pats

cd "$( dirname "${BASH_SOURCE[0]}")"

# CLEAN UP
echo ">>> cleaning up"
rm -f $ARCHIVE_NAME
rm -rf $CHECK_DIR
mkdir $CHECK_DIR

# DOWNLOAD
echo ">>> downloading latest sources from $SOURCES"
wget -q $SOURCES
tar -C $CHECK_DIR -xf $ARCHIVE_NAME
rm -f $ARCHIVE_NAME

echo ">>> checking sources"

# COMPARE
RES=$(diff -r $SOURCE_DIR $CHECK_DIR/$SOURCE_IN_ARCHIVE -X $DIFF_CONFIG)

if [ -z "$RES" ]
then
  echo ">>> sources are up-to-date"
else
  echo ">>> sources are changed, double check the diff:"
  echo -e "$RES"
fi
