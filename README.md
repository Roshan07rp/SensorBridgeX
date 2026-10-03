# SensorBridgeX
## Software-Only Embedded Linux Sensor Gateway

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue) ![Linux](https://img.shields.io/badge/platform-Linux-green) ![Docker](https://img.shields.io/badge/Docker-supported-2496ED)

SensorBridgeX is a C++17 user-space telemetry gateway prototype. It ingests CSV sensor-like readings, validates them against configurable limits, reports rejected records, and exports accepted readings. It is intentionally software-only: **no physical sensors, GPIO/I²C/SPI hardware, kernel module, or root access is required**.

## Features
- Deterministic built-in simulator and CSV ingestion
- Configurable temperature/humidity validation
- Per-record accept/reject reasons and summary counters
- CMake + CTest build and automated tests
- Docker multi-stage build, Docker Compose hardening, systemd service example
- Standard-library-only C++17 implementation

## Architecture
```text
CSV / Simulator -> Parser -> Validator -> Accepted CSV
                                  |
                                  +----> Rejection reason + summary metrics
```

## Repository layout
```text
SensorBridgeX/
├── README.md  CMakeLists.txt  Dockerfile  docker-compose.yml
├── config/  data/  include/sensorbridgex/
├── src/  scripts/  tests/  docs/  systemd/
└── .gitignore  .dockerignore  LICENSE
```

## Build and run (Ubuntu / WSL)
```bash
sudo apt update
sudo apt install -y build-essential cmake
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/sensorbridgex --config config/sensorbridgex.conf
```

Invalid-data demo (three of five rows are intentionally rejected; exit code 1 is expected):
```bash
./build/sensorbridgex --config config/sensorbridgex.conf --input data/invalid_sensor_readings.csv --output build/invalid.csv
```

Simulator demo:
```bash
./build/sensorbridgex --config config/sensorbridgex.conf --simulate --output build/simulated.csv
```

## Docker
```bash
docker compose build
mkdir -p output
docker compose run --rm sensorbridgex
```

## CLI
`--config PATH`, `--input PATH`, `--output PATH`, `--simulate`, `--help`

## Honest scope
This is a software-only embedded-Linux-oriented prototype, not a physical sensor driver or a production-certified system. Do not claim hardware integration or production testing unless you perform those separately. See `docs/` for architecture, demo, security notes, and interview Q&A.
