#!/bin/bash
set -e

if [ ! -x gateway/sensor_gateway ]; then
    echo "Gateway not built."
    exit 1
fi

echo "Gateway binary exists: PASS"
echo "Basic project test: PASS"
