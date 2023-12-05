#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define LINE_SIZE 200
#define isDigit(x) (x>='0'&&x<='9')

size_t max_length = LINE_SIZE;
FILE *f;
char *line;
int length;
long long seeds[20];
long long newseeds[20];
long long range[3];
long long min = LLONG_MAX;
int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen(argv[1], "r");
  getline(&line,&max_length, f);
  sscanf(line, "seeds: %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
         newseeds+0,  newseeds+1,  newseeds+2,  newseeds+3,  newseeds+4,
         newseeds+5,  newseeds+6,  newseeds+7,  newseeds+8,  newseeds+9,
         newseeds+10, newseeds+11, newseeds+12, newseeds+13, newseeds+14,
         newseeds+15, newseeds+16, newseeds+17, newseeds+18, newseeds+19);
  for(length = getline(&line,&max_length, f);
      length>0;
      length = getline(&line,&max_length, f)) {
    if(line[0]=='\n') {
      for(int i=0;i<20;i++) {
        seeds[i] = newseeds[i];
      }
      getline(&line,&max_length, f);
      getline(&line,&max_length, f);
    }
    sscanf(line, "%lld %lld %lld", range+0, range+1, range+2);
    for(int i=0;i<20;i++) {
      if(range[1]<=seeds[i] && range[1]+range[2]>seeds[i]) {
        newseeds[i] = range[0]-range[1]+seeds[i];
      }
    }
  }
  for(int i=0;i<20;i++) {
    if(min>newseeds[i])
      min = newseeds[i];
  }
  printf("%lld\n",min);
}
