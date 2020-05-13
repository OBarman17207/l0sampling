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
  //unsigned int moo;
  //moo = (unsigned int)pow(2,31);
  //printf("moo is %d\n",moo);
  int k = atoi(argv[1]);
  int m = atoi(argv[2]);
  int u = atoi(argv[3]);
  int p = 10937;
  srand(time(0));
  //int index = (rand()) % u;
  printf("k is %d\n",k);
  int* hashtable = malloc(sizeof(int)*k);
  int* counttable = malloc(sizeof(int)*m);
  for(int i = 0; i < m; i++){
   counttable[i] = 0;
  }
  hash_create(hashtable,k,p);
  for(int i = 1; i < u+1; i++){
   int value = hash(hashtable, i, k, m, p);
   if( value > m-1 || value < 0){
     printf("value is %d\n",value);
   }
   //value = abs(value);
   counttable[value] += 1;
  }
  int total = 0;
  for(int i = 0; i < m; i++){
   printf("count of index %d is ", i);
   printf("%d\n", counttable[i]);
   total += counttable[i];
  }
  printf("total is %d\n",total);
  return 0;
}
