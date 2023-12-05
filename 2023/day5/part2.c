#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define LINE_SIZE 200
#define isDigit(x) (x>='0'&&x<='9')

typedef struct node {
  long long start;
  long long length;
  struct node *next;
  struct node *prev;
} node;

typedef struct list {
  long long length;
  struct node *head;
  struct node *tail;
} list;

void list_append(list* l, long long v, long long v2) {
  node *n =  malloc(sizeof(node));
  n->start = v;
  n->length = v2;
  n->next = NULL;
  n->prev = l->tail;
  if(l->length==0) {
    l->head = n;
    l->tail = n;
  } else {
    l->tail->next = n;
    l->tail = n;
  }
  l->length++;
}

void list_append_list(list *l, list* a) {
  if(a->length==0)
    return;
  if(l->length==0) {
    l->tail = a->tail;
    l->head = a->head;
    l->length = a->length;
    return;
  }
  a->head->prev = l->tail;
  l->tail->next = a->head;
  l->length += a->length;
}

list *list_init(void) {
  list *l = malloc(sizeof(list));
  l->length = 0;
  l->head = NULL;
  l->tail = NULL;
  return l;
}

void list_remove(list* l,node* n) {
  if(l->length == 0) {
    return;
  } else if(l->length==1) {
    l->head = NULL;
    l->tail = NULL;
  } else if(n==l->head) {
    l->head = n->next;
    l->head->prev = NULL;
  } else if(n==l->tail) {
    l->tail = n->prev;
    l->tail->next = NULL;
  } else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }
  free(n);
  l->length--;
}

void list_print(list *l) {
  node *c = l->head;
  while(c!=NULL) {
    printf("(%lld %lld) ",c->start, c->length);
    c=c->next;
  }
  printf("%lld\n", l->length);
}

void list_clear(list* l) {
  while(l->head!=NULL) {
    list_remove(l, l->head);
  }
}

size_t max_length = LINE_SIZE;
FILE *f;
char *line;
int length;
list *seeds;
list *newseeds;
node *curr;
long long range[3];
long long min = LLONG_MAX;

void get_seeds(void) {
long long arr[20];
  getline(&line,&max_length, f);
  sscanf(line, "seeds: %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
         arr+0,  arr+1,  arr+2,  arr+3,  arr+4,
         arr+5,  arr+6,  arr+7,  arr+8,  arr+9,
         arr+10, arr+11, arr+12, arr+13, arr+14,
         arr+15, arr+16, arr+17, arr+18, arr+19);
  for(int i=0;i<20;i+=2) {
    list_append(newseeds,arr[i],arr[i+1]);
  }
}

int main(int argc, char** argv) {
  if(argc<1) {
    puts("Pass path to data file as argument");
    return 1;
  }
  line = malloc(sizeof(char)*LINE_SIZE);
  f = fopen(argv[1], "r");
  seeds = list_init();
  newseeds = list_init();
  get_seeds();
  for(length = getline(&line,&max_length, f);
      length>0;
      length = getline(&line,&max_length, f)) {
    if(line[0]=='\n') {
      list_append_list(seeds,newseeds);
      free(newseeds);
      newseeds = list_init();
      getline(&line,&max_length, f);
      getline(&line,&max_length, f);
    }
    sscanf(line, "%lld %lld %lld", range+0, range+1, range+2);
    curr = seeds->head;
    while(curr!=NULL) {
      list_print(newseeds);
      if(range[1] > curr->start+curr->length || //separata
         range[1]+range[2] < curr->start) {
        curr = curr->next;
        continue;
      } else if(range[1] <= curr->start && //seed in range
                range[1]+range[2] >= curr->start+curr->length) {
        list_append(newseeds, range[0]-range[1]+curr->start, curr->length);
        if(curr->next==NULL) {
          list_remove(seeds, curr);
          curr=NULL;
        } else {
          curr = curr->next;
          list_remove(seeds, curr->prev);
        }
        continue;
      } else if(range[1] > curr->start && //range in seed not touching borders
                range[1]+range[2] < curr->start+curr->length){
        list_append(newseeds, range[0], range[2]);
        list_append(seeds, range[1]+range[2],
                    (curr->start+curr->length)-(range[1]+range[2]));
        curr->length = range[1]-curr->start;
      } else if(range[1] == curr->start && //range in seed touching left
                range[1]+range[2] < curr->start+curr->length) {
        list_append(newseeds, range[0], range[2]);
        curr->length -= range[2];
        curr->start = range[1];
      } else if(range[1] > curr->start && //range in seed touching right
                range[1]+range[2] == curr->start+curr->length) {
        list_append(newseeds, range[0], range[2]);
        curr->length -= range[2];
      } else if(range[1] < curr->start && //intersection seed to the right
                range[1]+range[2] > curr->start &&
                range[1]+range[2] < curr->start+curr->length) {
        list_append(newseeds, range[0]-range[1]+curr->start,
                    range[1]-curr->start+range[2]);
        curr->start = range[1]-curr->start+range[2];
      } else if(range[1] > curr->start && //intersection seed to the left
                range[1] < curr->start+curr->length &&
                range[1]+range[2] > curr->start+curr->length) {
        list_append(newseeds, range[0], curr->start+curr->length-range[1]);
        curr->length -= curr->start+curr->length-range[1];
      }
      curr = curr->next;
    }
  }
  curr = newseeds->head;
  while(curr!=NULL) {
    if(min>curr->start)
      min = curr->start;
    curr = curr->next;
  }
  list_clear(seeds);
  list_clear(newseeds);
  free(seeds);
  free(newseeds);
  //printf("%lld\n",min);
}
