#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <immintrin.h>
#define true 1
#define false 0
#define change(t,c) (t^(1<<(c-'a'+5)))

int main(int argc, char **argv) {
  uint32_t silver;
  uint32_t gold;
  uint32_t* temp = malloc(sizeof(uint32_t)*8);
  uint32_t* last = malloc(sizeof(uint32_t)*8);
  uint32_t result=0;
  unsigned int fsilver = 0;
  __m128i values;
  const __m128i mask = _mm_setr_epi32(-'a',-'a',-'a',-'a');
  // const __m256i mask8 = _mm256_setr_epi32(-'a',-'a',-'a',-'a',-'a',-'a',-'a',-'a');
  const __m128i one = _mm_setr_epi32(1,1,1,1);
  //const __m256i one8 = _mm256_setr_epi32(1,1,1,1,1,1,1,1);
  unsigned int i = 15;
  int fd = open(argv[1], O_RDONLY);
  struct stat sb;
  fstat(fd,&sb);
  char *buff = mmap(NULL,
                    sb.st_size,
                    PROT_READ,
                    MAP_PRIVATE,
                    fd,0);

  values = _mm_setr_epi32(buff[0],buff[1],buff[2],buff[3]);
  values = _mm_add_epi32(values,mask);
  values = _mm_sllv_epi32(one,values);
  _mm_storeu_si128((__m128i*) temp,values);
  for(int j=0;j<4;j++) {
    last[j] = temp[j];
    result ^= temp[j];
  }
  for(;buff[i]!='\n';i+=4) {
    values = _mm_setr_epi32(buff[i-3],buff[i-2],buff[i-1],buff[i]);
    values = _mm_add_epi32(values,mask);
    values = _mm_sllv_epi32(one,values);
    _mm_storeu_si128((__m128i*) &temp[0],values);
    for(int j=0;j<4;j++) {
      result ^= last[j];
      last[j] = temp[j];
      result ^= temp[j];
      if(__builtin_popcount(result)==4) {
        printf("%d\n",i-4+j);
        goto silver_end;
      }
    }
  }
 silver_end:
  //TODO: second part
  free(temp);
  free(last);
  close(fd);
  return 0;
}
