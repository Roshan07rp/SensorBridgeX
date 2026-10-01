#!/bin/bash

if [ ! -e /dev/sensorbridge ]; then
    echo "FAIL: /dev/sensorbridge does not exist."
    exit 1
fi

echo "PASS: /dev/sensorbridge exists."
