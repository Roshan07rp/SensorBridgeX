#include "sensorbridgex/csv.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace sbx {
static std::string trim_csv(std::string s){auto a=s.find_first_not_of(" \t\r\n");if(a==std::string::npos)return {};auto b=s.find_last_not_of(" \t\r\n");return s.substr(a,b-a+1);}
std::vector<SensorReading> read_csv(const std::string& path){
 std::ifstream f(path);if(!f)throw std::runtime_error("Cannot open CSV: "+path);
 std::string line;if(!std::getline(f,line)||trim_csv(line)!="sensor_id,timestamp,temperature_c,humidity_pct")throw std::runtime_error("Missing or invalid CSV header");
 std::vector<SensorReading> out;size_t ln=1;
 while(std::getline(f,line)){++ln;if(trim_csv(line).empty())continue;std::stringstream ss(line);std::string id,ts,t,h,extra;
 if(!std::getline(ss,id,',')||!std::getline(ss,ts,',')||!std::getline(ss,t,',')||!std::getline(ss,h,',')||std::getline(ss,extra,','))throw std::runtime_error("Malformed CSV row "+std::to_string(ln));
 try{SensorReading r;size_t a=0,b=0,d=0;auto si=trim_csv(id),st=trim_csv(t),sh=trim_csv(h);r.sensor_id=std::stoi(si,&a);r.timestamp=trim_csv(ts);r.temperature_c=std::stod(st,&b);r.humidity_pct=std::stod(sh,&d);if(a!=si.size()||b!=st.size()||d!=sh.size())throw std::runtime_error("");out.push_back(r);}catch(...){throw std::runtime_error("Invalid CSV field at line "+std::to_string(ln));}
 }return out;
}
void write_csv_header(std::ostream& o){o<<"sensor_id,timestamp,temperature_c,humidity_pct\n";}
void write_reading(std::ostream& o,const SensorReading& r){o<<r.sensor_id<<','<<r.timestamp<<','<<r.temperature_c<<','<<r.humidity_pct<<'\n';}
}
