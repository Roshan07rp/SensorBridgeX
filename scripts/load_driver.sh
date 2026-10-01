#!/bin/bash
set -e

cd "$(dirname "$0")/.."

if [ ! -f driver/sensorbridge.ko ]; then
    echo "Driver not built. Run: make"
    exit 1
fi

sudo insmod driver/sensorbridge.ko
echo "SensorBridgeX driver loaded."
ls -l /dev/sensorbridge
