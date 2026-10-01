# Build and Run

## Install dependencies

```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r) git
```

## Build

```bash
make
```

## Load

```bash
sudo ./scripts/load_driver.sh
```

## Generate data

```bash
./simulator/sensor_simulator
```

## Read data

```bash
./gateway/sensor_gateway read
```

## Other commands

```bash
./gateway/sensor_gateway status
./gateway/sensor_gateway stats
./gateway/sensor_gateway reset
./gateway/sensor_gateway rate 1000
```

## Unload

```bash
sudo ./scripts/unload_driver.sh
```
