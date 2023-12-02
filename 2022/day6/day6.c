#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define true 1
#define false 0
#define change(t,c) (t^((uint32_t)1<<(c-'a'+6)))

int main(int argc, char **argv) {
  (void)argc;
  uint32_t silver = 0;
  uint32_t gold = 0;
  uint fsilver = 0;
  uint i = 0;
  char *buf;
  int fd = open(argv[1], O_RDONLY);
  struct stat sb;
  fstat(fd,&sb);
  buf = mmap(NULL,
             sb.st_size,
             PROT_READ,
             MAP_PRIVATE,
             fd,0);

  for(int j=0;j<3;j++)
    silver = change(silver,buf[j]);
  for(i=3;i<13;i++) {
    silver = change(silver,buf[i]);
    if(__builtin_popcount(silver)==4) {
      fsilver=i+1;
      break;
    }
    silver = change(silver,buf[i-3]);
  }

  if(!fsilver)
    for(;buf[i]!=0;i++) {
      silver = change(silver,buf[i]);
      if(__builtin_popcount(silver)==4) {
        printf("%d\n",i+1);
        break;
      }
      silver = change(silver,buf[i-3]);
    }
  else printf("%d\n",fsilver);

  for(int j=1;j<14;j++) gold = change(gold,buf[i-j]);
  for(;buf[i]!=0;i++) {
    gold = change(gold,buf[i]);
    if(__builtin_popcount(gold)==14) {
      printf("%d\n",i+1);
      break;
    }
    gold = change(gold,buf[i-13]);
  }

  close(fd);
  return 0;
}
