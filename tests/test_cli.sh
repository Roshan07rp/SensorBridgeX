#!/usr/bin/env bash
set -euo pipefail
BIN="$1"; ROOT="$2"; T="$(mktemp -d)"; trap 'rm -rf "$T"' EXIT
"$BIN" --config "$ROOT/config/sensorbridgex.conf" --input "$ROOT/data/sensor_readings.csv" --output "$T/good.csv" > "$T/good.log"
grep -q 'Received: 5' "$T/good.log"; grep -q 'Accepted: 5' "$T/good.log"; grep -q 'Rejected: 0' "$T/good.log"
set +e
"$BIN" --config "$ROOT/config/sensorbridgex.conf" --input "$ROOT/data/invalid_sensor_readings.csv" --output "$T/bad.csv" > "$T/bad.log"
S=$?
set -e
[[ "$S" -eq 1 ]]; grep -q 'Accepted: 2' "$T/bad.log"; grep -q 'Rejected: 3' "$T/bad.log"
echo 'CLI tests passed.'
