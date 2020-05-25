#include "../l0sampler.h"
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
  int u = 8;
  int m = 512;
  int total_level = (int) ((log(m)/log(2)) + 1);
  int p = 8191;
  srand(time(0));
  int k = atoi(argv[1]);
  int runs = atoi(argv[2]);
  printf("k is %d\n",k);
  int* hashtable = malloc(sizeof(int)*k);
  int* counttable = malloc(sizeof(int)*total_level);
  for(int i = 0; i < total_level; i++){
   counttable[i] = 0;
  }
  for(int j = 0; j < runs; j++){
    hash_create(hashtable,k,p);
    for(int i = 1; i < u+1; i++){
     int value = hash(hashtable, i, k, m, p);
     for(int level = 0; level < total_level; level++){
       if(index_in_level(level, value, m)){
         counttable[level] += 1;
       }
     }
   }
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
