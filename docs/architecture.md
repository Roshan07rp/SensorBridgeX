# SensorBridgeX Architecture

## Layers

1. Sensor / simulator
2. Linux character device driver
3. `/dev/sensorbridge`
4. C++ gateway
5. Validation and statistics

## Data flow

```text
Sensor Simulator
      |
      | write()
      v
/dev/sensorbridge
      |
      | read()
      v
C++ Gateway
      |
      v
Application Output
```

## Real hardware extension

The simulator can later be replaced by an I2C/SPI sensor implementation on an embedded Linux board.
