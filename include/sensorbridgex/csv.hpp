#pragma once
#include "sensorbridgex/reading.hpp"
#include <iosfwd>
#include <vector>
#include <string>
namespace sbx {
std::vector<SensorReading> read_csv(const std::string& path);
void write_csv_header(std::ostream& out);
void write_reading(std::ostream& out, const SensorReading& reading);
}
