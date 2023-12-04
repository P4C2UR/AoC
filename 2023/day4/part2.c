#include <stdlib.h>
#include <stdio.h>

#define LINE_SIZE 200

size_t max_length = LINE_SIZE;
FILE *f;
char *line;
int length;
int winning[10];
int card[25];
int n;
int acc = 0;
int buff[10] = {};
int curr;
int t;

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen(argv[1], "r");
  for(length = getline(&line,&max_length, f);
      length>0;
      length = getline(&line,&max_length, f)) {
    sscanf(line,"Card %d: %d %d %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
           &n,
           winning+0, winning+1, winning+2, winning+3, winning+4,
           winning+5, winning+6, winning+7, winning+8, winning+9,
           card+0, card+1, card+2, card+3, card+4,
           card+5, card+6, card+7, card+8, card+9,
           card+10, card+11, card+12, card+13, card+14,
           card+15, card+16, card+17, card+18, card+19,
           card+20, card+21, card+22, card+23, card+24);
    curr = 0;
    for(int i=0;i<10;i++) {
      for(int j=0;j<25;j++) {
        if(winning[i]==card[j]) {
          curr++;
          break;
        }
      }
    }
    acc+=buff[0]+1;
    t = buff[0];
    for(int i=0;i<9;i++) {
      buff[i]=buff[i+1]+((i<curr)?1:0)*(t+1);
    }
    buff[9]=((curr==10)?1:0)*(t+1);
  }
  printf("%d\n", acc);
}
