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
#define change(t,c) (t^((uint32_t)1<<(c-'a'+5)))

int main(int argc, char **argv) {
  (void)argc;
  uint32_t* temp = malloc(sizeof(uint32_t)*8);
  uint32_t* last = malloc(sizeof(uint32_t)*8);
  uint32_t result=0;
  __m256i values;
  const __m256i mask = _mm256_setr_epi32(-'a',-'a',-'a',-'a',-'a',-'a',-'a',-'a');
  const __m256i one = _mm256_setr_epi32(1,1,1,1,1,1,1,1);
  uint i = 15;
  int fd = open(argv[1], O_RDONLY);
  struct stat sb;
  fstat(fd,&sb);
  char *buff = mmap(NULL,
                    sb.st_size,
                    PROT_READ,
                    MAP_PRIVATE,
                    fd,0);
  values = _mm256_setr_epi32(buff[0],buff[1],buff[2],buff[3],buff[4],buff[5],buff[6],buff[7]);
  values = _mm256_add_epi32(values,mask);
  values = _mm256_sllv_epi32(one,values);
  _mm256_storeu_si256((__m256i*) temp,values);
  for(int j=0;j<4;j++) {
    last[j] = temp[j];
  }
  for(int j=4;j<8;j++) {
    result ^= temp[j];
    last[j] = temp[j];
  }


  for(;buff[i]!='\n';i+=8) {
    values = _mm256_setr_epi32(buff[i-7],buff[i-6],buff[i-5],buff[i-4],buff[i-3],buff[i-2],buff[i-1],buff[i]);
    values = _mm256_add_epi32(values,mask);
    values = _mm256_sllv_epi32(one,values);
    _mm256_storeu_si256((__m256i*) &temp[0],values);
    for(int j=0;j<4;j++) {
      result ^= last[j+4];
      result ^= temp[j];
      if(__builtin_popcount(result)==4) {
        printf("%d\n",i-6+j);
        close(fd);
        return 0;
      }
    }
    for(int j=4;j<8;j++) {
      result ^= temp[j-4];
      result ^= temp[j];
      last[j]=temp[j];
      if(__builtin_popcount(result)==4) {
        printf("%d\n",i-6+j);
        goto cleanup;
      }
    }
  }
  cleanup:
  free(temp);
  free(last);
  close(fd);
  return 0;
}
