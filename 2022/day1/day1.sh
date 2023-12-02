#!/bin/bash
r="$(awk '/[0-9]+/ {var += $0}
         /^$/{print var; var = 0}' "$1" | sort -g)"
echo "First half:"
echo "$r" | tail -n 1 -
echo "Second part:"
echo "$r" | tail -n 3 - | awk '{var = var + $0};END{print var}' -
