#include "l0sampler.h"
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
int main(int argc, char const *argv[]) {
  int u = 100;
  int m = 1000000;
  int total_level = (int) ((log(m)/log(2)) + 1);
  printf("total_level %d\n",total_level);
  int p = 1000187;
  srand(time(0));
  //int index = (rand()) % u;
  int k = atoi(argv[1]);
  printf("k is %d\n",k);
  int* hashtable = malloc(sizeof(int)*k);
  int* counttable = malloc(sizeof(int)*total_level);
  for(int i = 0; i < total_level; i++){
   counttable[i] = 0;
  }
  hash_create(hashtable,k,p);
  for(int i = 0; i < u; i++){
   int value = hash(hashtable, i, k, m, p);
   printf("hash is value %d\n", value);
   for(int level = 0; level < total_level; level++){
     //printf("hello");
     if(index_in_level(level, value, m)){
       counttable[level] += 1;
     }
   }

   //printf("value is %d\n",value);
  }
  int total = 0;
  for(int i = 0; i < total_level; i++){
   printf("count of index %d is ", i);
   printf("%d\n", counttable[i]);
   total += counttable[i];
  }
  printf("total is %d\n",total);
  return 0;
}
