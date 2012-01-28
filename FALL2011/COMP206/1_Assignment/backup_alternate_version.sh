#!/usr/bin/env bash

if [ $# == 0 ]; then
    cp -r * ../backup
    rm ../backup/backup.sh
else
    while (($#)) ; do
        cp "$1" ../backup
shift
done
fi
