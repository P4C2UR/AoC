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

END {
  while(x!=fx || y!=fy) {
    curr=map[x,y]
    currval=y+x*xsize
    printf("%d %d = %d\n",x,y,curr)
    printf("%d<=%d && %d<%d && %d = %d\n",map[x+1,y],curr+1,x+1,xsize,and(steps[currval],1)>0,map[x+1,y]<=curr+1 && x+1<xsize && and(steps[currval],1)==0)
    printf("%d<=%d && %d>=%d && %d = %d\n",map[x,y-1],curr+1,y-1,0,and(steps[currval],2)>0,map[x,y-1]<=curr+1 && y-1>=0 && and(steps[currval],2)==0)
    printf("%d<=%d && %d>=%d && %d = %d\n",map[x,x-1],curr+1,x-1,0,and(steps[currval],4)>0,map[x-1,y]<=curr+1 && x-1>=0 && and(steps[currval],4)==0)
    printf("%d<=%d && %d<%d && %d = %d\n\n",map[x,y+1],curr+1,y+1,ysize,and(steps[currval],8)>0,map[x,y+1]<=curr+1 && y+1<ysize && and(steps[currval],8)==0)
    if(map[x+1,y]<=curr+1 && x+1<xsize && and(steps[currval],1)==0) {
      x++
      steps[currval]=or(steps[currval],1)
      prev[p_length]=y+x*xsize
      p_length++
    }
    else if(map[x,y-1]<=curr+1 && y-1>=0 && and(steps[currval],2)==0) {
      y--
      steps[currval]=or(steps[currval],2)
      prev[p_length]=y+x*xsize
      p_length++
    }
    else if(map[x-1,y]<=curr+1 && x-1>=0 && and(steps[currval],4)==0) {
      x--
      steps[currval]=or(steps[currval],4)
      prev[p_length]=y+x*xsize
      p_length++
    }
    else if(map[x,y+1]<=curr+1 && y+1<ysize && and(steps[currval],8)==0) {
      y++
      steps[currval]=or(steps[currval],8)
      prev[p_length]=y+x*xsize
      p_length++
    }
    else if(p_length>=0){
      p_length--
      y=prev[p_length-1]%xsize
      x=int(prev[p_length-1]/xsize)
    }
    else break
    }
  printf("%d %d\n",x,y)
#  for(i=0;i<p_length;i++)
#    print prev[i]
}
