#include <stdlib.h>
#include <stdio.h>

#define LINE_SIZE 200
#define isDigit(c) (c>='0'&&c<='9')

size_t max_length = LINE_SIZE;
FILE *f;
char **lines;
int length;
int acc = 0;
char *t;

int parseNumber(char *arr, int i) {
  int ret = 0;
  while(isDigit(arr[i])) {
    i--;
    if(i==-1)
      break;
  }
  i++;
  while(isDigit(arr[i])) {
    ret*=10;
    ret+=arr[i]-'0';
    arr[i]='.';
    i++;
  }
  return ret;
}

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  lines = malloc(sizeof(char*)*3);
  for(int i=0;i<3;i++)
    lines[i] = malloc(sizeof(char)*LINE_SIZE);
  for(int i=0;i<LINE_SIZE;i++) {
    lines[0][i]='.';
    lines[1][i]='.';
  }
  f = fopen(argv[1], "r");
  for(length = getline(&lines[2],&max_length, f); length>0;) {
    for(int i=0;i<length-1;i++) {
      if(isDigit(lines[1][i]) || lines[1][i]=='.')
        continue;
      if(i-1>=0) {
        for(int j=0;j<3;j++) {
          if(isDigit(lines[j][i-1]))
            acc += parseNumber(lines[j], i-1);
        }
      }
      if(isDigit(lines[0][i]))
        acc += parseNumber(lines[0],i);
      if(isDigit(lines[2][i]))
        acc += parseNumber(lines[2],i);
      if(i+1<length-1) {
        for(int j=0;j<3;j++) {
          if(isDigit(lines[j][i+1]))
            acc += parseNumber(lines[j], i+1);
        }
      }
    }
    t=lines[0];
    lines[0] = lines[1];
    lines[1] = lines[2];
    lines[2] = t;
    length = getline(&lines[2],&max_length, f);
  }
  printf("%d\n", acc);
  return 0;
}
