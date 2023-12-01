#!/bin/env -S awk -f

/^\$ cd [a-z]/ {
  dir = sprintf("%s/%s",
                substr(dir,1,length(dir)),
                substr($3,1,length($3)-1))
  dirs[i++] = dir
  next;
}
/^\$ cd \.\./{dir=substr(dir,1,match(dir, /\/[a-z]+$/)-1);next}
/^\$ l/ {sum[dir]=0;next}
/^[0-9]+/ {sum[dir]+=$1;next}
END {
  for(j=0;j<i;j++) {
    d=dirs[j]
    subs=substr(d,1,match(d, /\/[a-z]+$/)-1)
    while(subs!="") {
      sum[subs]+=sum[d]
      subs=substr(subs,1,match(subs, /\/[a-z]+$/)-1)
    }
    sum[subs]+=sum[d]
  }
  total=70000000
  needed=30000000
  min=sum[""]
  free=total-min
  for(j=0;j<i;j++) {
    d=dirs[j]
    if(sum[d]<=100000)
      silver+=sum[d];
    if(free+sum[d]>=needed &&
       sum[d]<min)
      min=sum[d]
  }
  printf("%s\n%s\n",silver,min)
}
