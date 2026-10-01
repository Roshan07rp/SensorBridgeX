# Testing

### Build test

```bash
make
```

### Device test

```bash
ls -l /dev/sensorbridge
```

### Kernel log

```bash
dmesg | tail -n 20
```

### Functional test

```bash
./simulator/sensor_simulator
./gateway/sensor_gateway read
./gateway/sensor_gateway status
./gateway/sensor_gateway stats
```

### Error test

Unload the driver and run the gateway:

```bash
sudo rmmod sensorbridge
./gateway/sensor_gateway read
```

The application should report that the device cannot be opened.
