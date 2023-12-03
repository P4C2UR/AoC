#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 200
#define isDigit(c) (c>='0'&&c<='9')

size_t max_length = LINE_SIZE;
FILE *f;
char *line;
char *pline;
int length;
int acc = 0;

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
  printf("%d\n", ret);
  return ret;
}

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  line = malloc(sizeof(char)*LINE_SIZE);
  pline = malloc(sizeof(char)*LINE_SIZE);
  for(int i=0;i<LINE_SIZE;i++)
    pline[i]='.';
  f = fopen(argv[1], "r");
  for(length = getline(&line,&max_length, f);
      length>0;
      memcpy(pline,line,max_length),
      length = getline(&line,&max_length, f)) {
    for(int i=0;i<length-1;i++) {
      if(isDigit(line[i])) {
        if(i-1>-1 && !isDigit(pline[i-1]) && pline[i-1]!='.') {
          acc += parseNumber(line,i);
        } else if(!isDigit(pline[i]) && pline[i]!='.') {
          acc += parseNumber(line,i);
        } else if(i+1<length-1 && !isDigit(pline[i+1]) && pline[i+1]!='.') {
          acc += parseNumber(line,i);
        }
      } else if(line[i]!='.') {
        if(i-1>-1 && isDigit(pline[i-1]))
          acc += parseNumber(pline, i-1);
        if(isDigit(pline[i]))
          acc += parseNumber(pline, i);
        if(i+1<length-1 && isDigit(pline[i+1]))
          acc += parseNumber(pline, i+1);
        if(isDigit(line[i-1]))
          acc += parseNumber(line, i-1);
        if(isDigit(line[i+1]))
          acc += parseNumber(line, i+1);
      }
    }
    for(int i=0;i<length;i++)
      printf("%c",pline[i]);
    puts("");
  }
  printf("%d\n", acc);
  return 0;
}
