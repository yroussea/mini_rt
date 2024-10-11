#!/usr/bin/env bash

SOURCES_FILE=$(make print_SOURCES_FILE)
SRC_DIR=$(make print_SRC_DIR)

TMP_FILE=$(mktemp)
pushd $SRC_DIR >/dev/null
find . -name '*.c' -type f | sed 's/^\.\///' > $TMP_FILE
popd >/dev/null

echo -e "SRC\t\t= \\" > $SOURCES_FILE
while read p; do
	echo -e "\t\t  $p \\" >> $SOURCES_FILE
done < $TMP_FILE
echo >> $SOURCES_FILE

rm -rf $TMP_FILE
