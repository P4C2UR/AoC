#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *f;
int times[4];
int distances[4];
int acc = 1;
double delta;
double t;

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  f = fopen(argv[1], "r");
  fscanf(f, "Time: %d %d %d %d\n", times+0, times+1, times+2, times+3);
  fscanf(f, "Distance: %d %d %d %d\n", distances+0, distances+1, distances+2,
         distances+3);
  for(int i=0;i<4;i++) {
    delta = sqrt(times[i]*times[i]-4*distances[i])/2.0;
    t = times[i]/2.0;
    acc *= floor(t+delta-0.001)-ceil(t-delta+0.001)+1;
  }
  printf("%d\n",acc);
}
