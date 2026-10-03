# Interview Q&A
**What is SensorBridgeX?** A C++17 telemetry gateway prototype that parses sensor-like CSV records, validates them, and exports accepted records.

**Why software-only?** It can be built and demonstrated on Linux/WSL without hardware, while still showing ingestion, validation, tests, and deployment packaging.

**Why C++17?** Strong typing, RAII, standard containers, and filesystem support are useful for maintainable Linux applications.

**Why separate parser and validator?** Parsing handles format and conversion; validation applies domain rules, which makes testing and maintenance easier.

**How are invalid rows handled?** The gateway prints a reason, skips the invalid record, continues processing, and returns exit code 1 if any were rejected.

**What does CMake do?** Describes targets and dependencies and integrates with CTest.

**What does Docker add?** A repeatable runtime image; the app runs as non-root with reduced container capabilities.

**Is it a Linux device driver?** No. This edition is user-space software and does not claim hardware integration.

**How could it scale?** Add a streaming adapter, bounded queues/back-pressure, structured logs, metrics, and storage, then benchmark before introducing concurrency.

**Current limitations?** CSV input only, no network protocol, database, authentication, physical sensor, or production certification.
