#!/bin/env -S awk -f
{
  gsub("[A|X]", "1")
  gsub("[B|Y]", "2")
  gsub("[C|Z]", "3")
  x=$1-$2
  silver+=$2+((x==0)?3:(x==-1||x==2)?6:0)
  t=(($1+$2-3)%3+3)%3 # = mod($1+$2,3)
  gold+=($2-1)*3 + t + 1
}
END {
  print silver
  print gold
}
