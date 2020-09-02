#!/bin/bash

function err()
{
    echo -e "\033[31m${@}\033[0m" >&2
}

function msg()
{
    echo -e "\033[36m${@}\033[0m"
}

function debug()
{
    echo -e "\033[1;30m${@}\033[0m" >&2
}


SEMVERSORT="/usr/local/bin/semversort"

RAW_FILE=$( mktemp )
SORTED_FILE=$( mktemp )
trap "debug 'Removing files...' ; rm -vf ${RAW_FILE} ${SORTED_FILE}" 0 1 2 15

./rv 100 > ${RAW_FILE}
if [[ $? -ne 0 ]]; then
    err "Error running ./rv 100!"
    exit 1
fi

debug "Testing for errors v0.0.0 in Raw"
ggrep "v0.0.0" "${RAW_FILE}"

cat ${RAW_FILE} |  ${SEMVERSORT} > ${SORTED_FILE}
debug "Testing for errors v0.0.0 in Sorted"
ggrep "v0.0.0" "${SORTED_FILE}"


msg "BEFORE:"
cat ${RAW_FILE}
wc -l ${RAW_FILE}
echo
msg "AFTER:"
cat ${SORTED_FILE}
wc -l ${SORTED_FILE}
echo




