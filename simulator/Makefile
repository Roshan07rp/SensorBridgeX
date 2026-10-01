CXX=g++
CXXFLAGS=-Wall -Wextra -O2 -std=c++17

all: sensor_simulator

sensor_simulator: sensor_simulator.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f sensor_simulator
