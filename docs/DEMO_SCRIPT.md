# 5–7 Minute Interview Demo
1. **Problem (45 sec):** Explain that this is a software-only embedded Linux telemetry gateway prototype.
2. **Architecture (60 sec):** Show `include/`, `src/`, `config/`, `tests/`.
3. **Build/test (60 sec):** Run CMake build and `ctest`.
4. **Valid records (60 sec):** Run the default config; point out received/accepted/rejected counters.
5. **Invalid records (60 sec):** Run the invalid CSV and explain the three rejected rows and exit code 1.
6. **Deployment (60 sec):** Show Dockerfile, Compose hardening, and systemd example.
7. **Limitations (30 sec):** Be transparent: no real sensor, driver, network ingestion, or production load test.
