#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 50
#define MAX_REDS 12
#define MAX_GREENS 13
#define MAX_BLUES 14

size_t max_length = LINE_SIZE;
FILE *f;
char* line;
int length;
int rgb[3] = {};
int max_rgb[3] = {};
int acc = 0;
int first_digit = 0;

int main() {
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen("2023/day2/data","r");
  for(length = getline(&line,&max_length, f);
      length>0;
      length = getline(&line,&max_length, f)) {
    for(int i=0;i<length;i++) {
      if(line[i]==';' || i+2>=length) {
        for(int j=0;j<3;j++) {
          if(rgb[j]>max_rgb[j])
            max_rgb[j]=rgb[j];
        }
        rgb[0]=0;rgb[1]=0;rgb[2]=0;
      }
      if(i+2>=length) {
        acc += max_rgb[0]*max_rgb[1]*max_rgb[2];
        max_rgb[0]=0;max_rgb[1]=0;max_rgb[2]=0;
        goto next_line;
      }
      if(!(line[i]>='0') || !(line[i]<='9') ||
         (i+1<length && line[i+1]==':'))
        continue;
      switch(line[i+2]) {
      case 'r':
        rgb[0] = first_digit*10+line[i]-'0';
        first_digit = 0;
      break;
      case 'g':
        rgb[1] = first_digit*10+line[i]-'0';
        first_digit = 0;
        break;
      case 'b':
        rgb[2] = first_digit*10+line[i]-'0';
        first_digit = 0;
      break;
      case ' ':
        first_digit = line[i]-'0';
      break;
      }
    }
    next_line:
  }
  printf("%d\n", acc);
  return 0;
}
