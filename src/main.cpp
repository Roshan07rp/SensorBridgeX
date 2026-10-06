#include "sensorbridgex/config.hpp"
#include "sensorbridgex/csv.hpp"
#include "sensorbridgex/validator.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
namespace sbx { std::vector<SensorReading> simulated_readings(); }
int main(int argc,char** argv){
 try{
 std::string cfg="config/sensorbridgex.conf",in,out;bool sim=false;
 for(int i=1;i<argc;++i){std::string a=argv[i];if(a=="--help"){std::cout<<"SensorBridgeX: --config PATH --input PATH --output PATH --simulate --help\n";return 0;}
 else if(a=="--simulate")sim=true;else if(a=="--config"&&i+1<argc)cfg=argv[++i];else if(a=="--input"&&i+1<argc)in=argv[++i];else if(a=="--output"&&i+1<argc)out=argv[++i];else throw std::runtime_error("Unknown/incomplete argument: "+a);}
 auto c=sbx::load_config(cfg);if(!in.empty())c.input_path=in;if(!out.empty())c.output_path=out;
 auto rows=sim?sbx::simulated_readings():sbx::read_csv(c.input_path);
 std::filesystem::path op(c.output_path);if(op.has_parent_path())std::filesystem::create_directories(op.parent_path());
 std::ofstream file(c.output_path);if(!file)throw std::runtime_error("Cannot write output: "+c.output_path);sbx::write_csv_header(file);
 size_t ok=0,bad=0;std::cout<<"\n=== SensorBridgeX Telemetry Gateway ===\n";
 for(const auto& r:rows){auto v=sbx::validate(r,c);if(v.accepted){sbx::write_reading(file,r);++ok;std::cout<<"[ACCEPT] sensor="<<r.sensor_id<<" temp="<<r.temperature_c<<" C humidity="<<r.humidity_pct<<"%\n";}
 else{++bad;std::cout<<"[REJECT] sensor="<<r.sensor_id<<" reason="<<v.reason<<"\n";}}
 std::cout<<"\n--- Summary ---\nReceived: "<<rows.size()<<"\nAccepted: "<<ok<<"\nRejected: "<<bad<<"\nOutput: "<<c.output_path<<"\n";
 return bad?1:0;
 }catch(const std::exception& e){std::cerr<<"SensorBridgeX error: "<<e.what()<<"\n";return 2;}
}
