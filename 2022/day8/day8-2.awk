#!/bin/env -S awk -f

BEGIN {
  FS=""
}

NR == 1 {
  t=NF-2
  for(j=0;j<t;j++)
    for(i=0;i<10;i++) {
      umax[j, i]=1
      bottom[j, i]=-1
    }
  next
}

{
  for(i=0;i<10;i++) {
    lmax[i]=1
    rmax[i]=1
  }

  for(i=t-1;i>=0;i--) {
    val=sprintf("%d",$((i+2)))
    mul[i]=rmax[val]
    for(j=0;j<=val;j++)
      rmax[j]=1
    for(j=val+1;j<10;j++)
      rmax[j]++
  }

  for(i=0;i<t;i++) {
    val=sprintf("%d",$((i+2)))

    mul[i]*=lmax[val]
    mul[i]*=umax[i, val]
    for(j=0;j<=val;j++) {
      umax[i, j]=1
      lmax[j]=1
    }
    for(j=val+1;j<10;j++) {
      lmax[j]++
      umax[i, j]++
    }
    if(val<bottom[i, 0]) {
      for(j=9;j>0;j--) {
        bottom[i, j] = bottom[i, j-1]
        m_bottom[i, j] = m_bottom[i, j-1]
        b_bottom[i, j] = b_bottom[i, j-1]
      }
      bottom[i, 0] = val
      m_bottom[i, 0] = mul[i]
      b_bottom[i, 0] = 0
    }
    else {
      if(m_bottom[i, 0]>max)
        max=m_bottom[i, 0]
      m_bottom[i, 0] = mul[i]
      bottom[i, 0] = val
      for(j=1;j<10;j++)
        b_bottom[i, j]++

      for(j=1;j<10;j++) {
        if(bottom[i, j]==-1) break;
        if(bottom[i, j]<=val) {
          if(m_bottom[i, j]*(j+b_bottom[i, j])>max)
            max=m_bottom[i,j]*(j+b_bottom[i, j])
          for(k=j;k<9;k++) {
            bottom[i, k] = bottom[i, k+1]
            m_bottom[i, k] = m_bottom[i, k+1]
            b_bottom[i, k] = b_bottom[i, k+1]
            b_bottom[i, k]++
          }
          bottom[i, 9] = -1
          m_bottom[i, 9] = 1
          j--
        }
      }
    }
  }
}

END {
  for(i=0;i<t;i++) {
    for(j=1;j<10;j++) {
      if(bottom[i, j]!=-1) {
        tmax=m_bottom[i, j]*(j+b_bottom[i, j])
        printf("%d ",tmax)
        if(max<tmax) {
          max = tmax
        }
      }
    }
    printf("\n")
    for(j=0;j<10;j++)
      printf("%d ",bottom[i, j])
    printf("\n")
    for(j=0;j<10;j++)
      printf("%d ",b_bottom[i, j])
    printf("\n")
    for(j=0;j<10;j++)
      printf("%d ",m_bottom[i, j])
    printf("\n")

  }
  print max
}
