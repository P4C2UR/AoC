#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 50

size_t max_length = LINE_SIZE;
char *line;
FILE *f;
int length;
int acc = 0;

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen(argv[1],"r");
  length = getline(&line, &max_length, f);
  while(length>0) {
    for(int i=0;i<length;i++) {
      if(line[i]>='0'&&line[i]<='9') {
        acc+=(line[i]-'0')*10;
        break;
      }
    }
    for(int i=length-2;i>=0;i--) {
      if(line[i]>='0'&&line[i]<='9') {
        acc+=(line[i]-'0');
        break;
      }
    }
    length = getline(&line, &max_length, f);
  }
  printf("%d\n", acc);
  return 0;
}
