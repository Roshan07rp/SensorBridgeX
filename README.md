# SensorBridgeX — Embedded Linux Sensor Gateway & Character Device Driver Framework

SensorBridgeX is a Linux-based embedded sensor gateway demonstration built using **C/C++ only**.

It demonstrates:

- Linux character-device driver concepts
- Kernel-space / user-space communication
- `/dev/sensorbridge` device interface
- `open()`, `read()`, `write()`, and `ioctl()`
- C++ user-space gateway
- C++ sensor simulator
- Makefile-based builds
- Error handling and statistics
- A design that can later connect to real I2C/SPI sensors

## Architecture

```text
Sensor Simulator
       |
       v
Linux Character Driver (sensorbridge.ko)
       |
       v
/dev/sensorbridge
       |
       v
C++ Sensor Gateway
       |
       v
Validation / Statistics / Console
```

## Requirements

- Ubuntu / Ubuntu on WSL2
- GCC / G++
- Make
- Linux kernel headers matching the running kernel
- VS Code (recommended)
- Git

## Quick start

```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r) git
make
sudo ./scripts/load_driver.sh
./gateway/sensor_gateway
```

If your WSL kernel does not provide loadable-module support, build the user-space components first and use a native Ubuntu VM/installation for the kernel-module demonstration.

## Project structure

```text
SensorBridgeX/
├── driver/
├── gateway/
├── simulator/
├── include/
├── scripts/
├── tests/
├── docs/
├── demo/
├── Makefile
└── README.md
```

## Important note

The simulator represents the physical sensor for a hardware-free demonstration. It does not claim to be a real physical sensor. A production version can replace the simulator with an I2C/SPI sensor implementation.

## Interview focus

Be prepared to explain:

1. User space vs kernel space
2. Character devices
3. `file_operations`
4. `/dev/sensorbridge`
5. `open/read/write/ioctl`
6. `copy_to_user()` and `copy_from_user()`
7. Kernel modules
8. I2C/SPI extension
9. Error handling
10. Driver lifecycle
