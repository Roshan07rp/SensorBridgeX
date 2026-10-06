#pragma once
#include <string>
namespace sbx {
struct Config {
 std::string input_path{"data/sensor_readings.csv"};
 std::string output_path{"build/accepted_readings.csv"};
 double temperature_min_c{-20.0}, temperature_max_c{85.0};
 double humidity_min_pct{0.0}, humidity_max_pct{100.0};
};
Config load_config(const std::string& path);
}
