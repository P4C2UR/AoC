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
int line_no = 0;
int line_correct = 1;
int acc = 0;
int first_digit = 0;

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen(argv[1],"r");
  for(length = getline(&line,&max_length, f);
      length>0;
      length = getline(&line,&max_length, f),
      line_no++) {
    for(int i=0;i<length;i++) {
      if(line[i]==';' || i+2>=length) {
        if(rgb[0]>MAX_REDS || rgb[1]>MAX_GREENS ||
           rgb[2]>MAX_BLUES)
          line_correct = 0;
        rgb[0]=0;rgb[1]=0;rgb[2]=0;
      }
      if(i+2>=length) {
        if(line_correct) {
          printf("%d\n",line_no+1);
          acc += line_no+1;
        } else {
          line_correct = 1;
        }
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
