#!/bin/sh

# Build the project
./Build.sh

# Navigate to the source directory
cd ../

# Make the bin folder the starting directory to look into
start_dir="bin"

# Use the find command to find directories with the maximum depth
deepest_dir_path=$(find "$start_dir" -type d -exec sh -c 'echo "$(echo "$1" | tr "/" "\n" | wc -l) $1"' sh {} \; | sort -nr | head -n 1 | awk '{print substr($0, index($0,$2))}')

# Navigate into the deepest directory of the bin folder
cd $deepest_dir_path
./Matchstick
