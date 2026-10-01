CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -O2 -Iinclude
CXXFLAGS=-Wall -Wextra -O2 -std=c++17 -Iinclude

.PHONY: all driver gateway simulator test clean

all: driver gateway simulator

driver:
	$(MAKE) -C driver

gateway:
	$(MAKE) -C gateway

simulator:
	$(MAKE) -C simulator

test:
	./tests/test_gateway.sh

clean:
	$(MAKE) -C driver clean
	$(MAKE) -C gateway clean
	$(MAKE) -C simulator clean
