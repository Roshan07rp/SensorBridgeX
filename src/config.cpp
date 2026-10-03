#include "sensorbridgex/config.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
namespace sbx {
static std::string trim(std::string s) { auto a=s.find_first_not_of(" \t\r\n"); if(a==std::string::npos)return {}; auto b=s.find_last_not_of(" \t\r\n"); return s.substr(a,b-a+1); }
static double number(const std::string& k,const std::string& v) { try { size_t n=0; double d=std::stod(v,&n); if(n!=v.size()) throw std::runtime_error(""); return d; } catch(...) { throw std::runtime_error("Invalid numeric config: "+k); } }
Config load_config(const std::string& path) {
 std::ifstream f(path); if(!f) throw std::runtime_error("Cannot open config: "+path);
 Config c; std::string line; int n=0;
 while(std::getline(f,line)){ ++n; line=trim(line); if(line.empty()||line[0]=='#')continue; auto p=line.find('='); if(p==std::string::npos)throw std::runtime_error("Malformed config line "+std::to_string(n));
 auto k=trim(line.substr(0,p)),v=trim(line.substr(p+1));
 if(k=="input")c.input_path=v; else if(k=="output")c.output_path=v;
 else if(k=="temperature_min_c")c.temperature_min_c=number(k,v); else if(k=="temperature_max_c")c.temperature_max_c=number(k,v);
 else if(k=="humidity_min_pct")c.humidity_min_pct=number(k,v); else if(k=="humidity_max_pct")c.humidity_max_pct=number(k,v);
 else throw std::runtime_error("Unknown config key: "+k);
 }
 if(c.temperature_min_c>c.temperature_max_c||c.humidity_min_pct>c.humidity_max_pct||c.humidity_min_pct<0||c.humidity_max_pct>100)throw std::runtime_error("Invalid configured ranges");
 return c;
}
}
