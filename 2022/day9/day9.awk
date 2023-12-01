#!/bin/env -S awk -f

function neutral(coord, distance, direction, num) {
  if(distance==0) {
  }
  else if(distance==1) {
    offset[coord, num]=direction
  }
  else {
    offset[coord, num]=direction
    same(coord, distance-1, direction, distance, num)
  }
}

function same(coord, distance, direction,ndist,num,t) {
  t=position[coord, num] + distance*direction
  if(num==9) {
    if(coord==0) {
      for(i=position[coord];i!=t;i+=direction) {
        found[i, position[1,9]]=1
      }
    }
    else {
      for(i=position[coord];i!=t;i+=direction) {
        found[position[0,9],i]=1
      }
    }
  }
  position[coord,num]=t
  if(num!=9&&ndist!=0)
    move(coord,ndist-1,direction,num+1)
}

function opposite(coord, distance, direction,num) {
  offset[coord,num]=0
  neutral(coord, distance-1, direction,num)
}

function rotate(coord, distance, direction,ndist,num) {
  if(distance==0) return 1
  offset[coord,num]=direction
  if(distance!=1)
  {
    position[0,num]=position[0,num]+offset[0,num]
    position[1,num]=position[1,num]+offset[1,num]
    offset[(coord+1)%2,num]=0
    same(coord, distance-2, direction,ndist,num)
  }
}

function diagon(coord, distance, direction,num) {
  if(offset[coord,num]==direction) {
    position[0,num]=position[0,num]+offset[0,num]
    position[1,num]=position[1,num]+offset[1,num]
    offset[(coord+1)%2,num]=0
    same(coord, distance-1, direction,distance,num)
  }
  else {
    if(distance==1) {
      offset[coord,num]=0
    }
    else {
      offset[coord,num]-=1
      rotate(coord, distance-1, direction,distance,num)
    }
  }
}

function move(coord, distance, direction,num) {
  printf("coord %d distance %d direction %d num %d\n",coord,distance,direction,num)
  if(offset[0,num]==0 && offset[1,num]==0)
    neutral(coord, distance, direction,num)
  else if(direction==offset[coord,num] && offset[(coord+1)%2,num]==0)
    same(coord, distance, direction,distance,num)
  else if(direction==-1*offset[coord,num] && offset[(coord+1)%2,num]==0)
    opposite(coord, distance, direction,num)
  else if(0!=offset[coord,num])
    diagon(coord, distance, direction,num)
  else if(offset[coord,num]==0)
    rotate(coord, distance, direction,distance,num)
  else
    printf("Logic error\n")
}

BEGIN {
  position[0] = 0
  position[1] = 0
  offset[0]=0
  offset[1]=0
  found[0, 0]=1
}
/^[U|R]/ {direction=1}
/^[D|L]/ {direction=-1}
/^[D|U]/ {coord=1}
/^[L|R]/ {coord=0}

{
  printf("%c %d",$1, $2)
  move(coord,$2,direction,0)
  found[position[0,9], position[1,9]]=1

  for(i=0;i<2;i++) {
    if(max[i]<position[i,9]) max[i]=position[i,9]
    else if(min[i]>position[i,9]) min[i]=position[i,9]
  }

  for(i=0;i<10;i++) {
    printf("%d: %d %d\n",i,position[0,i],position[1,i])
  }

  for(i=max[1]+1;i>min[1]-2;i--) {
    for(j=min[0]-1;j<max[0]+2;j++) {
      if(found[j, i]==1) printf("+")
      else printf(".")
    }
    printf("\n")
  }

}

END {
  printf("  ")
  for(j=min[0]-2;j<max[0]+2;j++)
    printf("%2d ",j)
  printf("\n")
  for(i=max[1]+2;i>min[1]-2;i--) {
    printf("%2d ",i)
    for(j=min[0]-2;j<max[0]+2;j++) {
      if(found[j, i]==1) printf("+  ")
      else printf(".  ")
      count+=found[j, i]
    }
    printf("\n")
  }
  print count
}
