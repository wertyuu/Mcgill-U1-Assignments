#!/bin/bash

if [ $# == 0 ]; then
    cp * ../backup
    rm ../backup/backup.sh
else
    while (($#)) ; do
        cp "$1" ../backup
shift
done
fi
