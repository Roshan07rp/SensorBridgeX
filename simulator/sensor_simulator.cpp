/*
 * Hardware-free sensor simulator.
 * Generates realistic sample packets and writes them to the character device.
 */

#include "../gateway/SensorPacket.h"

#include <fcntl.h>
#include <iostream>
#include <random>
#include <unistd.h>

int main() {
    const char* device = "/dev/sensorbridge";
    int fd = open(device, O_WRONLY);

    if (fd < 0) {
        perror("open /dev/sensorbridge");
        std::cerr << "Load the driver first.\n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> temp(22.0f, 32.0f);
    std::uniform_real_distribution<float> humidity(40.0f, 80.0f);
    std::uniform_int_distribution<int> light(100, 1000);

    SensorPacket packet{
        temp(generator),
        humidity(generator),
        light(generator)
    };

    const ssize_t written = write(fd, &packet, sizeof(packet));

    if (written != static_cast<ssize_t>(sizeof(packet))) {
        perror("write");
        close(fd);
        return 1;
    }

    std::cout << "SensorBridgeX Simulator\n"
              << "-----------------------\n"
              << "Temperature : " << packet.temperature << " C\n"
              << "Humidity    : " << packet.humidity << " %\n"
              << "Light       : " << packet.light << " lux\n";

    close(fd);
    return 0;
}
