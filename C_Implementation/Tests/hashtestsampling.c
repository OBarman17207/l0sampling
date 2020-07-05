#include "../l0sampler.h"
#include "../count.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>



int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int runs = 1;
  int u = 100;
  int m = 1000000;
  int total_level = (int) ((log(m)/log(2)) + 1);
  int p = 1000187;
  bool retry = false;
  if(p < u){
    printf("bad value of prime\n");
    return 1;
  }
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, total_level, runs, retry);
  int* hashtable = malloc(sizeof(int) * k);
  while(count_struct->runs_left > 0){
    hash_create(hashtable,k,p);
    for(int i = 0; i < u; i++){
      int value = hash(hashtable, i, k, m, p);
      for(int level = 0; level < total_level; level++){
       //printf("hello");
        if(index_in_level(level, value, m)){
          increase_count(count_struct, level);
        }
      }
    }

     //printf("value is %d\n",value);
  }

  print_count(count_struct);
  free(count_struct);

  return 0;
}
