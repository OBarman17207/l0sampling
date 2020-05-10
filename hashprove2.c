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
// Choose k members of U
// set random h
// hash and check
// add 1 if same
// repeat step 2 and 3

int main(int argc, char const *argv[]) {
   int u = 100;
   int m = 10;
   int p = 4253;
   srand(time(0));
   int k = atoi(argv[1]);
   printf("k is %d\n",k);
   //printf("index is %d\n", index);
   int* hashtable = malloc(sizeof(int)*k);
   hash_create(hashtable,k,p);
   int count = 0;

   for(int i = 0; i < 10000; i++){
     int index = (rand()) % u;
     int* codetable = malloc(sizeof(int)*k);
     for(int i = 0; i < k; i++){
       codetable[i] = rand() % m;
     }
     bool check = true;
     for(int j = 0; j < k; j++){
       int value = hash(hashtable, ((index + (j*rand() % u)) % u), k, m, p);
       check = check && (value == codetable[j]);
     }
     if (check){
       count += 1;
     }
   }
   printf("count is %d", count);
   return 0;
}
