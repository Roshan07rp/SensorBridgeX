#!/bin/bash
set -e

echo "=== SensorBridgeX Demo ==="

if [ ! -e /dev/sensorbridge ]; then
    echo "Device not found. Run: sudo ./scripts/load_driver.sh"
    exit 1
fi

echo
echo "[1] Generate sensor data"
./simulator/sensor_simulator

echo
echo "[2] Read data through the gateway"
./gateway/sensor_gateway read

echo
echo "[3] Driver status"
./gateway/sensor_gateway status

echo
echo "[4] Driver statistics"
./gateway/sensor_gateway stats

echo
echo "Demo complete."
