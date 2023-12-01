#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 50

size_t max_length = LINE_SIZE;
char *line;
FILE *f;
int length;
int acc = 0;
int root;
char digits[9][5] = {
  { 'o', 'n', 'e',   0,   0},
  { 't', 'w', 'o',   0,   0},
  { 't', 'h', 'r', 'e', 'e'},
  { 'f', 'o', 'u', 'r',   0},
  { 'f', 'i', 'v', 'e',   0},
  { 's', 'i', 'x',   0,   0},
  { 's', 'e', 'v', 'e', 'n'},
  { 'e', 'i', 'g', 'h', 't'},
  { 'n', 'i', 'n', 'e',   0}
};

int main() {
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen("2023/day1/data","r");
  length = getline(&line, &max_length, f);
  while(length>0) {
    if(length==1) {
      length = getline(&line, &max_length, f);
      continue;
    }
    for(int i=0;i<length;i++) {
      if(line[i]>='0'&&line[i]<='9') {
        acc+=(line[i]-'0')*10;
        goto last;
      } else {
        for(int j=0;j<9;j++) {
          for(int k=0;k<6;k++) {
            if(k==5) {
              acc+=(j+1)*10;
              goto last;
            }
            if(line[i+k]!=digits[j][k]) {
              if(digits[j][k]==0) {
                acc+=(j+1)*10;
                goto last;
              }
              break;
            }
          }
        }
      }
    }
last:
    for(int i=length-2;i>=0;i--) {
      if(line[i]>='0'&&line[i]<='9') {
        acc+=(line[i]-'0');
        break;
      } else {
        for(int j=0;j<9;j++) {
          root=4;
          for(int k=4;k>=-1;k--) {
            if(k==-1) {
              acc+=(j+1);
              goto finnish;
            }
            if(digits[j][k]==0) continue;
            if(line[i-(4-root)]!=digits[j][k]) {
              break;
            }
            root--;
          }
        }
      }
    }
  finnish:
    length = getline(&line, &max_length, f);
  }
  printf("%d\n", acc);
  return 0;
}
