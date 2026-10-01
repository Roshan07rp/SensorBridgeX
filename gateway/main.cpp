#include "SensorGateway.h"

#include <cstdlib>
#include <iostream>
#include <string>

static void usage(const char* program) {
    std::cout
        << "Usage:\n"
        << "  " << program << " read\n"
        << "  " << program << " status\n"
        << "  " << program << " stats\n"
        << "  " << program << " reset\n"
        << "  " << program << " rate <milliseconds>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    SensorGateway gateway("/dev/sensorbridge");

    if (!gateway.openDevice())
        return 1;

    const std::string command = argv[1];

    if (command == "read") {
        SensorPacket packet{};
        if (!gateway.readSensor(packet))
            return 1;

        std::cout << "\n=== SensorBridgeX Gateway ===\n"
                  << "Temperature : " << packet.temperature << " C\n"
                  << "Humidity    : " << packet.humidity << " %\n"
                  << "Light       : " << packet.light << " lux\n"
                  << "Status      : OK\n";
    } else if (command == "status") {
        std::cout << "Device status: "
                  << (gateway.getStatus() ? "ONLINE" : "OFFLINE") << '\n';
    } else if (command == "stats") {
        unsigned long count = 0;
        if (!gateway.getReadCount(count))
            return 1;
        std::cout << "Driver read count: " << count << '\n';
    } else if (command == "reset") {
        if (!gateway.resetSensor())
            return 1;
        std::cout << "Sensor reset completed.\n";
    } else if (command == "rate") {
        if (argc != 3) {
            usage(argv[0]);
            return 1;
        }

        const int rate = std::atoi(argv[2]);
        if (!gateway.setSampleRate(rate))
            return 1;

        std::cout << "Sample rate set to " << rate << " ms.\n";
    } else {
        usage(argv[0]);
        return 1;
    }

    return 0;
}
