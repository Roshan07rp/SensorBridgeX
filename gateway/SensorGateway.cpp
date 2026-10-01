#include "SensorGateway.h"
#include "../include/sensorbridge_ioctl.h"

#include <fcntl.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

SensorGateway::SensorGateway(const std::string& device)
    : devicePath(device), fd(-1) {}

SensorGateway::~SensorGateway() {
    closeDevice();
}

bool SensorGateway::openDevice() {
    fd = open(devicePath.c_str(), O_RDWR);
    if (fd < 0) {
        perror("open /dev/sensorbridge");
        return false;
    }
    return true;
}

bool SensorGateway::readSensor(SensorPacket& packet) {
    if (fd < 0)
        return false;

    const ssize_t bytes = read(fd, &packet, sizeof(packet));
    if (bytes != static_cast<ssize_t>(sizeof(packet))) {
        perror("read");
        return false;
    }
    return true;
}

bool SensorGateway::getStatus() {
    int status = 0;
    if (ioctl(fd, SENSORBRIDGE_GET_STATUS, &status) < 0) {
        perror("ioctl GET_STATUS");
        return false;
    }
    return status == 1;
}

bool SensorGateway::setSampleRate(int milliseconds) {
    if (ioctl(fd, SENSORBRIDGE_SET_SAMPLE_RATE, &milliseconds) < 0) {
        perror("ioctl SET_SAMPLE_RATE");
        return false;
    }
    return true;
}

bool SensorGateway::resetSensor() {
    if (ioctl(fd, SENSORBRIDGE_RESET) < 0) {
        perror("ioctl RESET");
        return false;
    }
    return true;
}

bool SensorGateway::getReadCount(unsigned long& count) {
    if (ioctl(fd, SENSORBRIDGE_GET_READ_COUNT, &count) < 0) {
        perror("ioctl GET_READ_COUNT");
        return false;
    }
    return true;
}

void SensorGateway::closeDevice() {
    if (fd >= 0) {
        close(fd);
        fd = -1;
    }
}
