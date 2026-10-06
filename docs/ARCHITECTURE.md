# Architecture
1. Input: CSV file or deterministic built-in simulator.
2. Parsing: checks the CSV header, columns, and numeric conversion.
3. Validation: positive sensor ID, timestamp presence, finite measurements, configurable ranges.
4. Output: accepted records are written to CSV; rejected records are explained in the terminal.
5. Operations: CMake/CTest, Docker, Compose, and example systemd unit.

The application returns 0 when all records pass, 1 when any record is rejected, and 2 for operational/configuration errors. This version is user-space software, not a kernel driver. No network listener, physical hardware, or database is included.
