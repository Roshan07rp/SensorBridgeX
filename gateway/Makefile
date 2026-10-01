CXX=g++
CXXFLAGS=-Wall -Wextra -O2 -std=c++17 -I../include

all: sensor_gateway

sensor_gateway: main.o SensorGateway.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp SensorGateway.h
	$(CXX) $(CXXFLAGS) -c $<

SensorGateway.o: SensorGateway.cpp SensorGateway.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o sensor_gateway
