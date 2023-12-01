#!/bin/env -S awk -f
function pop(string) {
  return substr(string,1,length(string)-1)
}
function peek(string) {
  x=length(string)
  return substr(string,x,1)
}

BEGIN {
  FS="(( {2})|\\[|(\\] ?))"
}
/^ *\[/ {
  for(i=1;i<NF;i++) {
    x=int(i/2)-1
    stacks[x]=sprintf("%s%s",$i,stacks[x])
    stacks2[x]=sprintf("%s%s",$i,stacks[x])
  }
  next
}
/^ 1/ {
  FS=" "
  stack_count=NF
  next
}
/^m.*/ {
  for(i=$2;i>0;i--) {
    from=$4-1
    to=$6-1
    stacks[to]=sprintf("%s%s",stacks[to],peek(stacks[from]))
    stacks[from]=pop(stacks[from])
  }
  x=length(stacks2[from])
  stacks2[to]=sprintf("%s%s",stacks2[to],substr(stacks2[from],x-$2+1,x))
  stacks2[from]=substr(stacks2[from],1,length(stacks2[from])-$2)
  next
}
END{
  for(i=0;i<stack_count;i++) {
    printf("%c",peek(stacks[i]))
  }
  printf("\n")
  for(i=0;i<stack_count;i++) {
    printf("%c",peek(stacks2[i]))
  }
  printf("\n")
}
