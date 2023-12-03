#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
#define buf 500

FILE *file;
char *l;
int ll,l2;
int v;

int ind(char c) {
  if(c>'a') return c-'a';
  else return c-'A'+26;
}

static inline int priority(char c) {return ind(c)+1;}
static inline void getLine() {
  if(fgets(l,buf,file)==0) return;
  ll=0;
  while(l[++ll]!='\n'){};
  l[ll]=0;
  l2=ll/2;
}

int main(int argc, char **argv) {
  int *exists = (int*)calloc(208,sizeof(int));
  char* s;
  if(argc>1) s=argv[1];
  else s="data/day3";
  file = fopen(s ,"r");
  l = (char*)malloc(sizeof(char)*buf);
  int j;
  v = 0;
  int found = false;
  int found2 = false;
  int sum = 0;
  int ssum = 0;

  getLine();
  while(!feof(file)) {
    for(j=0;j<l2;j++) {
      exists[ind(l[j])]=true;
      exists[52+ind(l[j])]=true;
    }
    for(;j<ll;j++) {
      exists[ind(l[j])]=true;
      if(exists[52+ind(l[j])]&&!found) {
        sum += priority(l[j]);
        found=true;
      }
    }
    memset(exists+52, 0, 52*sizeof(int));
    found=false;
    getLine();
    for(j=0;j<l2;j++) {
      exists[52+ind(l[j])]=exists[ind(l[j])];
      exists[104+ind(l[j])]=true;
    }
    for(;j<ll;j++) {
      exists[52+ind(l[j])]=exists[ind(l[j])];
      if(exists[104+ind(l[j])]&&!found) {
        sum += priority(l[j]);
        found=true;
      }
    }
    found=false;
    getLine();
    for(j=0;j<l2;j++) {
      if(exists[52+ind(l[j])]&&!found2) {
        ssum += priority(l[j]);
        found2=true;
      }
      exists[156+ind(l[j])]=true;
    }
    for(;j<ll;j++) {
      if(exists[52+ind(l[j])]&&!found2) {
        ssum += priority(l[j]);
        found2=true;
      }
      if(exists[156+ind(l[j])]&&!found) {
        sum += priority(l[j]);
        found=true;
      }
    }
    memset(exists, 0, 208*sizeof(int));
    found2 = false;
    found = false;
    getLine();
  }

  fclose(file);
  free(l);
  free(exists);
  printf("First half:\n%d\nSecond half:\n%d\n",sum,ssum);
  return 0;
}
