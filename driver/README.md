# Driver

`sensorbridge.c` is the Linux kernel character-device driver.

Build:

```bash
make
```

Load:

```bash
sudo insmod sensorbridge.ko
```

Unload:

```bash
sudo rmmod sensorbridge
```
