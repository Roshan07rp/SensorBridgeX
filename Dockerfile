FROM ubuntu:24.04 AS build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends build-essential cmake && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF && cmake --build build -j"$(nproc)"
FROM ubuntu:24.04 AS runtime
RUN useradd --system --create-home --uid 10001 appuser
WORKDIR /app
COPY --from=build /src/build/sensorbridgex /app/sensorbridgex
COPY config /app/config
COPY data /app/data
RUN mkdir -p /app/output && chown -R appuser:appuser /app
USER appuser
ENTRYPOINT ["/app/sensorbridgex"]
CMD ["--config","/app/config/sensorbridgex.conf","--input","/app/data/sensor_readings.csv","--output","/app/output/accepted.csv"]
