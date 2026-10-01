#!/bin/bash

if ./gateway/sensor_gateway unknown-command >/dev/null 2>&1; then
    echo "FAIL: invalid command was accepted."
    exit 1
fi

echo "PASS: invalid command rejected."
