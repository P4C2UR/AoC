#!/bin/env -S awk -f

BEGIN {
  stops[0]=20
  stops[1]=60
  stops[2]=100
  stops[3]=140
  stops[4]=180
  stops[5]=220
  x=1
  cycle=1
}

NR == 1{
  printf("#")
}

/^n/ {
  cycle++
}

/^a/ {
  for(i=0;i<6;i++) {
    if(cycle+1==stops[i]) {
      sum+=(cycle+1)*x
    }
  }

  if((cycle)%40==0)printf("\n")
  if(x-1==cycle%40||x+1==cycle%40||x==cycle%40)
    printf("#")
  else printf(" ")
  cycle+=2
  x+=$2
}

{
  for(i=0;i<6;i++) {
    if(cycle==stops[i]) {
      sum+=(cycle)*x
    }
  }

  if((cycle-1)%40==0)printf("\n")
  if(x-1==(cycle-1)%40||x==(cycle-1)%40||x+1==(cycle-1)%40)
    printf("#")
  else printf(" ")

}

END {
  print sum
}

