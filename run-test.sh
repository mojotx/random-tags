#!/bin/bash

function err()
{
    echo -e "\033[31m${@}\033[0m"
}

function msg()
{
    echo -e "\033[36m${@}\033[0m"
}



SEMVERSORT="/usr/local/bin/semversort"

RAW_FILE=$( mktemp )
SORTED_FILE=$( mktemp )
trap "rm -vf ${RAW_FILE} ${SORTED_FILE}" 0 1 2 15

set -e
./rv 10 > ${RAW_FILE}
cat ${RAW_FILE} |  ${SEMVERSORT} > ${SORTED_FILE}


msg "BEFORE:"
cat ${RAW_FILE}
wc -l ${RAW_FILE}
echo
msg "AFTER:"
cat ${SORTED_FILE}
wc -l ${SORTED_FILE}
echo



