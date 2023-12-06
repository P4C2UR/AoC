#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LINE_SIZE 200
#define isDigit(x) (x>='0'&&x<='9')

size_t max_length = LINE_SIZE;
char *line;
int length;
FILE *f;
long long time;
long long distance;
double delta;
double t;


long long ignore_spaces() {
  int i = 0;
  long ret = 0;
  while(line[i++]!=':') {}
  for(;i<length;i++) {
    if(isDigit(line[i])) {
      ret*=10;
      ret+=line[i]-'0';
    }
  }
  return ret;
}

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  f = fopen(argv[1], "r");
  length = getline(&line, &max_length, f);
  time = ignore_spaces();
  length = getline(&line, &max_length, f);
  distance = ignore_spaces();
  delta = sqrt(time*time-4*distance)/2.0;
  t = time/2.0;
  printf("%lld\n",(long long)(floor(t+delta-0.001)-ceil(t-delta+0.001)+1));
}
