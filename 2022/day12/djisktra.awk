#!/bin/env -S awk -f

function _ord_init(    low, high, i, t)
{
  low = sprintf("%c", 7) # BEL is ascii 7
  if (low == "\a") {    # regular ascii
    low = 0
    high = 127
  } else if (sprintf("%c", 128 + 7) == "\a") {
    # ascii, mark parity
    low = 128
    high = 255
  } else {        # ebcdic(!)
    low = 0
    high = 255
  }

  for (i = low; i <= high; i++) {
    t = sprintf("%c", i)
    _ord_[t] = i
  }
}
function ord(str,    c)
{
  c = substr(str, 1, 1)
  return _ord_[c]
}

BEGIN{FS="";_ord_init();ysize=0}

{
  for(i=0;i<NF;i++) {
    if($(i+1)=="S") {
      val=0
      x=i
      y=ysize
      xsize=NF
    }
    else if($(i+1)=="E") {
      val=ord("z")-ord("a")
      fx=i
      fy=ysize
    }
    else
      val=ord($(i+1))-ord("a")
    map[i, ysize] = val
  }
  ysize++
}

function min(x,y,m) {
  m=99999
  if(map[x+1,y]<m && map[x+1,y]!=0)
    m=map[x+1,y]
  if(map[x,y+1]<m && map[x,y+1]!=0)
    m=map[x,y+1]
  if(map[x,y-1]<m && map[x,y-1]!=0)
    m=map[x,y-1]
  if(map[x-1,y]<m && map[x-1,y]!=0)
    m=map[x-1,y]
  return m
}

END {
  visited[x,y]=1
  while(x!=fx || y!=fy) {
    curr=map[x,y]

  }
  djikstra(x+1,y)
  djikstra(x,y+1)
  for(i=0;i<ysize;i++) {
    for(j=0;j<xsize;j++) {
      printf("%3d",map[j,i])
    }
    printf("\n")
  }
  printf("\n")
  for(i=0;i<ysize;i++) {
    for(j=0;j<xsize;j++) {
      printf("%3d",visited[j,i])
    }
    printf("\n")
  }
}
