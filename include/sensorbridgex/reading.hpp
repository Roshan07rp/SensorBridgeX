#pragma once
#include <string>
namespace sbx {
struct SensorReading { int sensor_id{}; std::string timestamp; double temperature_c{}; double humidity_pct{}; };
struct ValidationResult { bool accepted{}; std::string reason; };
}
