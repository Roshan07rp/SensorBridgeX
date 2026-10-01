# SensorBridgeX — 5–10 Minute Demo

## 1. Introduction

"SensorBridgeX is an Embedded Linux sensor gateway implemented using C and C++. It demonstrates sensor data flowing through a Linux character device driver to a user-space gateway."

## 2. Show architecture

```text
Sensor -> Character Driver -> /dev/sensorbridge -> C++ Gateway
```

## 3. Show repository

```bash
tree
```

## 4. Build

```bash
make clean
make
```

## 5. Load driver

```bash
sudo ./scripts/load_driver.sh
lsmod | grep sensorbridge
dmesg | tail
```

## 6. Generate data

```bash
./simulator/sensor_simulator
```

## 7. Read data

```bash
./gateway/sensor_gateway read
```

## 8. Demonstrate ioctl

```bash
./gateway/sensor_gateway status
./gateway/sensor_gateway stats
./gateway/sensor_gateway rate 1000
./gateway/sensor_gateway reset
```

## 9. Explain failure handling

```bash
sudo rmmod sensorbridge
./gateway/sensor_gateway read
```

Explain that the gateway handles the missing device instead of crashing.

## 10. Close

"SensorBridgeX demonstrates the complete path from sensor data to a user-space application through a Linux character device. A real deployment can replace the simulator with an I2C or SPI sensor."
