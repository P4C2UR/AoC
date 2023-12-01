#!/bin/env -S awk -M -f

#Monkey x:
/^M/ {id = substr($2, 1, length($2)-1);next}
#Starting items: x, y
/^  S/ {
  for(i=0;i<NF-3;i++) {
    t=$(i+3)
    items[id, i]=substr(t ,1,length(t)-1)
  }
  itemcount[id]=NF-2
  items[id, NF-3]=$NF
  next
}
#Operation: new = old [+|*] [old|x]
/^  O/ {op[id]=$5;val[id]=$6;next}
#Test: divisible by x
/^  T/ {test[id]=$4;next}
#If true: throw to monkey x
/^    If true/ {true[id]=$6;next}
#If false: throw to monkey x
/^    I/ {false[id]=$6;next}

function getNew(old,op,val) {
  if(val!="old") {
    if(op=="+") return old+val
    else return old*val
  }
  else {
    if(op=="+") return old+old
    else return old*old
  }
}

END {
  v=1
  for(k=0;k<=id;k++)
    v*=test[k]
  for(round=1;round!=10001;round++) {
    for(i=0;i<=id;i++) {
      for(j=0;j<itemcount[i];j++) {
        silver[i]++
        new=getNew(items[i, j],op[i],val[i])
        new%=v
        if(new%test[i]==0) {
          target=true[i]
        }
        else {
          target=false[i]
        }
        items[target,itemcount[target]++]=new
      }
      for(j=0;j<itemcount[i];j++)
        items[i, j]=0
      itemcount[i]=0
    }
  }
  for(i=0;i<=id;i++) {
    if(max1<silver[i]) {
      max2=max1
      max1=silver[i]
    }
    else if(max2<silver[i]) {
      max2=silver[i]
    }
    printf("%d: %d\n",i,silver[i])
  }
  print max1*max2
}
