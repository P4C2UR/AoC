#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1048576
#define NAME_SIZE 30
#define DEBUG 1

#define def_list_add(type) \
  void list_add_##type##_(list_##type **l, type *t) { \
    list_##type *tmp = *l; \
    (*l)=malloc(sizeof(list_##type)); \
    (*l)->current = t; \
    (*l)->next = tmp; \
  }

#define def_list_print(type) \
  void list_print_##type##_(list_##type *l) { \
    list_##type *c = l; \
    printf("("); \
    fflush(stdout); \
    while(c->next!=NULL) { \
      printf("{%d, %s}, ",c->current->size,c->current->name); \
      c=c->next; \
    } \
    printf("{%d, %s}",c->current->size,c->current->name); \
    printf(")\n"); \
  }

#define dec_list_add(type) \
  void list_add_##type##_(list_##type **l, type *t)

#define typedef_list(type) \
  typedef struct list_##type##_ list_##type

#define list(type) \
  struct list_##type##_ { \
    type *current; \
    list_##type *next; \
  }; \
  def_list_add(type) \
  def_list_print(type) \
  dec_list_add(type)

#define list_print(type, list) \
  list_print_##type##_(list)

#define list_add(type, list, obj) \
  list_add_##type##_(list, obj)

#define fso \
  ui size;\
  char *name

#define curr_inc \
  if(curr>=chars) { \
    chars = read(fd, buff, BUFF_SIZE); \
    if(chars==0) goto finnished; \
    curr=0; \
  } \
  else curr++

#define debug if(DEBUG)


typedef int ui;
typedef struct dir_ dir;
typedef_list(dir);

struct dir_ {
  ui size;
  char *name;
  list_dir *dirs;
  dir *parent;
};

list(dir);

dir* append_dir(char *name);

dir root;
dir *current;

dir* append_dir(char *name) {
  dir *d = malloc(sizeof(dir));
  d->name = name;
  d->size = 0;
  d->dirs = malloc(sizeof(list_dir));
  d->parent = current;
  list_add(dir,&(current->dirs),d); 
  return d;
}

int main(int argc, char* argv[]) {
  int fd;

  size_t chars;
  size_t curr;

  char buff[BUFF_SIZE];
  char *dn; /*dir name*/
  list_dir *curr_dir;
  ui i; /*dir name counter*/
  ui t; /*tmp var*/
  ui na = 0; /*numeric accumulator*/
  list_dir *all;
  dir *tmp;


  int pass = 0;
  ui ans = 0;

  root.size=0;
  root.dirs = NULL;
  root.parent = NULL;
  all = malloc(sizeof(list_dir));
  current = &root;

  fd = open(argv[1], O_RDONLY);
  chars = read(fd, buff, BUFF_SIZE);
  while(1) {
    for(curr=0; curr<BUFF_SIZE; curr++) {
      switch(buff[curr]) {
        case '$':
          curr+=2;
          if(buff[curr]=='c') {
            curr+=3;
            switch(buff[curr]) {
              case '/':
                debug puts("root");
                current = &root;
                curr_inc;
                break;
              case '.':
                debug puts("parent");
                current = current->parent;
                curr+=2;
                break;
              default:
                debug puts("descended");
                curr_dir=current->dirs;
                t=curr;
                while(buff[curr]!='\n') {
                  for(i=0;buff[curr]!='\n';i++) {
                    if(buff[curr]!=curr_dir->current->name[i]) {
                      curr=t;
                      curr_dir=curr_dir->next;
                      break;
                    }
                    curr_inc;
                  }
                }
                current=curr_dir->current;
                break;
            }
          }
          else if(current->size!=0 && current->dirs!=NULL) {
            debug puts("ls ignored");
            pass=1;
            curr+=2;
          }
          else {
            debug puts("ls used");
            pass=0;
            curr+=2;
          }
          break;
        case 'd':
          debug puts("dir found");
          if(pass==0) {
            curr+=4;
            dn = malloc(sizeof(char)*NAME_SIZE);
            for(i=0;buff[curr]!='\n'; i++) {
              dn[i]=buff[curr];
              curr_inc;
            }
            dn[i]='\0';
            list_add(dir,&all,append_dir(dn));
          }
          else while(buff[curr]!='\n') curr_inc;
          break;
        default:
          debug puts("file found");
          if(pass==0) {
              na+=buff[curr]-'0';
              curr_inc;
            while(buff[curr]!=' ') {
              na*=10;
              na+=buff[curr]-'0';
              curr_inc;
            }
            for(tmp=current;tmp!=NULL;tmp=tmp->parent) /*TODO: optimize*/
              tmp->size+=na;
            na=0;
            while(buff[curr]!='\n') curr_inc;
          }
          else while(buff[curr]!='\n') curr_inc;
          break;
      }
    }
    chars = read(fd, buff, BUFF_SIZE);
  }
  close(fd);
finnished:
  for(curr_dir=all;curr_dir->current!=NULL;curr_dir=curr_dir->next)
    if(curr_dir->current->size<=100000) ans+=curr_dir->current->size;
  printf("%d\n",ans);

  ans = root.size; /*TODO: optimize*/
  for(curr_dir=all;curr_dir->current!=NULL;curr_dir=curr_dir->next) {
    t = curr_dir->current->size; 
    if(70000000-root.size+t>=30000000 &&
        ans>t) ans = t;
  }
  printf("%d\n",ans);
  return 0;
}
