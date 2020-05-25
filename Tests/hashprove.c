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
int hash_prove(int index, int k, int u, int m, int p) {

   int* hashtable = malloc(sizeof(int)*k);
   hash_create(hashtable,k,p);
   int value = hash(hashtable, index, k, m, p);
   free(hashtable);
   return value;
}

int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int u = atoi(argv[2]);
  int m = atoi(argv[3]);
  int runs = atoi(argv[4]);
  int p = 4253;
  int index = (rand() % u);
  bool retry = false;

  if(p < u){
    printf("bad value of prime\n");
    return 1;
  }
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, m, runs, retry);
  while(count_struct->runs_left > 0){
    int x = hash_prove(index,k,u,m,p);
    increase_count(count_struct, x);
  }
  print_count(count_struct);
  free(count_struct);

  return 0;
}
