#!/bin/bash
r="$(sed 's/[A|X]/1/g;s/[B|Y]/2/g;s/[C|Z]/3/g' "data/day2")"
echo "First half:"
echo "$r" | awk '{x=($1-$2);var+=$2+((x==0)?3:(x==-1||x==2)?6:0)}END{print var}'
echo "Second half:"
echo "$r" | awk '{var+=($2-1)*3+(($1+$2-3)%3+3)%3+1}END{print var}'
