#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define isDigit() (*region>='0')
#define populate(var) \
  var=*(region++)-'0';\
  if(isDigit()) var=var*10+*(region++)-'0';\
  region++


char str[10] = "000000000\n"; 

char* itoa(int n) {
  uint i = 8;
  for(; n > 9; i--) {
    str[i] = (n % 10) + '0';
    n /= 10;
  }
  str[i] = n % 10 + '0';
  return str + i;
}
int main(int argc, char* argv[]) {
  register short f1,f2,s1,s2;
  register int sum=0;
  register int ssum=0;
  {
    auto int fd = open(argv[1], O_RDONLY);
    auto char* region;
    {
      auto struct stat sb;
      fstat(fd,&sb);       
      region = mmap(NULL,
                    sb.st_size,
                    PROT_READ,
                    MAP_PRIVATE,
                    fd,0);
    }
    while(*region != 0) {
      populate(f1);
      populate(f2);
      populate(s1);
      populate(s2);
      if(f2 >= s1 && f1 <= s2) {
        ssum++;
        if((f1 <= s1 && f2 >= s2) || (s1 <= f1 && s2 >= f2))
          sum++;
      }
    }
    close(fd);
  }
  puts("First half:");
  write(1,itoa(sum),10);
  puts("Second half:");
  write(1,itoa(ssum),10);
  return 0;
}
