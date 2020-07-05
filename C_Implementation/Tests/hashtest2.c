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


// define U and m for h:U->m and H a family of h
// set a random index member of U
// Choose random h
// hash and save value
// repeat step 2 and 3
// Should see a uniform random distribution
int hash_test2(int i, int k, int m, int p, int* hashtable){
  int value = hash(hashtable, i, k, m, p);
  if( value > m-1 || value < 0){
    printf("value is %d\n",value);
  }
   //value = abs(value);
  return value;

}

int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int u = atoi(argv[2]);
  int m = atoi(argv[3]);
  int runs = atoi(argv[4]);
  int p = 4253;
  bool retry = false;
  if(p < u){
    printf("bad value of prime\n");
    return 1;
  }
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, m, runs, retry);
  while(count_struct->runs_left > 0){
    for(int i = 1; i < u+1; i++){
      int* hashtable = malloc(sizeof(int)*k);
      hash_create(hashtable,k,p);
      int x = hash_test2(i,k,m,p, hashtable);
      increase_count(count_struct, x);
      free(hashtable);
    }

  }
  print_count(count_struct);
  free(count_struct);

  return 0;
}
