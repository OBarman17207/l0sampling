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
   int k = atoi(argv[1]);
   int u = atoi(argv[2]);
   int m = atoi(argv[3]);
   int runs = atoi(argv[4]);
   int p = 4253;
   if(p < u){
     printf("bad value of prime\n");
     return 1;
   }
   srand(time(0));
   int index = u - 2;

   printf("k is %d\n",k);
   int* hashtable = malloc(sizeof(int)*k);
   int* counttable = malloc(sizeof(int)*m);

   for(int i = 0; i < m; i++){
     counttable[i] = 0;
   }
   for(int i = 0; i < runs; i++){
     hash_create(hashtable,k,p);
     int value = hash(hashtable, index, k, m, p);
     counttable[value] += 1;
   }
   for(int i = 0; i < m; i++){
     printf("count of index %d is ", i);
     printf("%d\n", counttable[i]);
   }
   return 0;
}
