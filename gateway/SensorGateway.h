#ifndef SENSOR_GATEWAY_H
#define SENSOR_GATEWAY_H

#include "SensorPacket.h"
#include <string>

class SensorGateway {
public:
    explicit SensorGateway(const std::string& device);
    ~SensorGateway();

    bool openDevice();
    bool readSensor(SensorPacket& packet);
    bool getStatus();
    bool setSampleRate(int milliseconds);
    bool resetSensor();
    bool getReadCount(unsigned long& count);
    void closeDevice();

private:
    std::string devicePath;
    int fd;
};

#endif
