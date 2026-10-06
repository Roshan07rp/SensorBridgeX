#!/usr/bin/env bash
set -euo pipefail
for c in cmake c++; do command -v "$c" >/dev/null || { echo "Missing $c"; exit 1; }; done
echo "Build tools found."
