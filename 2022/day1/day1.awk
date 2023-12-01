#!/bin/env -S awk -f
/[0-9]+/ {var = var + $0;next}
/^$/{
  for(i=0;i<3;i++) {
    if(var>max[i]) {
      for(j=2;j>i;j--)
        max[j]=max[j-1]
      max[i]=var
      break
    }
  }
  var = 0
  next
}
END {printf("%s\n%s\n",max[0],max[0]+max[1]+max[2])}

