# Build and Run
Ubuntu/WSL:
```bash
sudo apt update && sudo apt install -y build-essential cmake
./scripts/check_environment.sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/sensorbridgex --config config/sensorbridgex.conf
```
Invalid data (exit code 1 is expected):
```bash
./build/sensorbridgex --config config/sensorbridgex.conf --input data/invalid_sensor_readings.csv --output build/invalid.csv
```
Docker:
```bash
docker compose build
mkdir -p output
docker compose run --rm sensorbridgex
```
Run commands from repository root. If CMake is missing, install `cmake` and `build-essential`.
