#include "sensorbridgex/validator.hpp"
#include <cmath>
namespace sbx {
ValidationResult validate(const SensorReading& r,const Config& c){
 if(r.sensor_id<=0)return {false,"sensor_id must be positive"};
 if(r.timestamp.empty())return {false,"timestamp is required"};
 if(!std::isfinite(r.temperature_c)||!std::isfinite(r.humidity_pct))return {false,"measurements must be finite"};
 if(r.temperature_c<c.temperature_min_c||r.temperature_c>c.temperature_max_c)return {false,"temperature outside configured range"};
 if(r.humidity_pct<c.humidity_min_pct||r.humidity_pct>c.humidity_max_pct)return {false,"humidity outside configured range"};
 return {true,"accepted"};
}}
