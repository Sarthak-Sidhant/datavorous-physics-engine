#!/bin/bash
set -e

# Run make
make

# Find the project root name
PROJECT_NAME=$(basename "$(pwd)")

# Move to bin/Debug
cd bin/Debug

# Run the binary
./"$PROJECT_NAME"
