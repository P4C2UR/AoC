#include <stdio.h>
#include <stdlib.h>
#define stack_size (9*8)
#define buf_size (500)

struct stack_a {
  char items[stack_size];
  int current;
};
typedef struct stack_a stack;
typedef unsigned int ui;
typedef unsigned short us;
typedef unsigned long ul;
typedef int i;
typedef short s;
typedef long l;
char buf[buf_size];

void push(stack *s,char c) {(*s).items[++(*s).current] = c;}
void pop(stack *s) {(*s).current--;}
char peek(stack *s) {return (*s).items[(*s).current];}
#define move(s, count, from, to) \
  do {\
    stack* t = s+from-1;\
    stack temp = {{0},-1};\
    ui i = 0;\
    for(;i<count;i++) {\
      push(&temp,peek(t));\
      pop(t);\
    }\
    while(count-->0) {\
      push(s+to-1,peek(&temp));\
      pop(&temp);\
    }\
  } while(0)
int main(int argc, char **argv) {
  FILE *f = fopen(argv[1],"r");
  ui count;
  ui from;
  ui to;
  stack stacks[9] = { {{'J','H','G','M','Z','N','T','F'},7},
    {{'V','W','J'},2},
    {{'G','V','L','J','B','T','H'},6},
    {{'B','P','J','N','C','D','V','L'},7},
    {{'F','W','S','M','P','R','G'},6},
    {{'G','H','C','F','B','N','V','M'},7},
    {{'D','H','G','M','R'},4},
    {{'H','N','M','V','Z','D'},5},
    {{'G','N','F','H'},3}
  };
  ui i = 0;
  char* s = "move %u from %u to %u\n";
  if(NULL==fgets(buf,buf_size,f)) return 1;
  while(fgets(buf,buf_size,f)[0]!='m') {}
  if(sscanf(buf,s,&count,&from,&to)!=3) return 2;
  while(!feof(f)) {
    move(stacks,count,from,to);
    if(fscanf(f,s,&count,&from,&to)!=3) return 3;
  }
  move(stacks,count,from,to);
  for(;i<9;i++) printf("%c",peek(stacks+i));
  printf("\n");
  fclose(f);
  return 0;
}
