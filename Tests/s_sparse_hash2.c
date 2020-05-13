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


void s_sparse_test(int k, int s, int r, int level, int prime, int index, struct one_sparse* s_sparse_structure) {

  int* hashtable = malloc(sizeof(struct one_sparse)*k*r);
  hash_create(hashtable, k*r, prime);
  //int number_of_index = 8;
  //printf("number of index should be %d\n", number_of_index);
  update_s_sparse_recovery(hashtable, s_sparse_structure, index, 1, level, s, r, k, prime);
  //struct one_sparse* result = recover_vector(0, s_sparse_structure, s, r);

}

int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int s = atoi(argv[2]);
  int r = atoi(argv[3]);
  int runs = atoi(argv[4]);
  int array_size = atoi(argv[5]);
  srand(time(0));
  int prime = 1000187;
  int m = pow(array_size,3);
  printf("m is %d\n",m);
  int total_level = (int) ((log(m)/log(2)) + 1);
  int* counttable = malloc(sizeof(int) * (array_size+1));
  struct one_sparse* s_sparse_structure = malloc(sizeof(struct one_sparse) * 2 * s * r * total_level);
  int* hashtable = malloc(sizeof(struct one_sparse) * k);
  for(int i = 0; i < array_size + 1; i++){
   counttable[i] = 0;
  }
  for(int i = 0; i < runs; i++){
    hash_create(hashtable, k, prime);
    setup_sparse_vector(s_sparse_structure, 2 * s * r * total_level);
    for(int j = 1; j < array_size + 1; j++){
      int hash_value = hash(hashtable, j, k, m, prime);
      for(int ii = 0; ii < total_level; ii++){
        if(index_in_level(ii, hash_value, m)){
          s_sparse_test(k, s, r, ii, 10937, j, s_sparse_structure);
        }
      }
    }
    struct one_sparse* result = malloc(sizeof(struct one_sparse));
    result = recover_vector(s_sparse_structure,s,r,total_level);
    if(result){
      counttable[(result->sum_of_identifiers/result->sum_of_weights)] += 1;
    }
    else{
      counttable[0] += 1;
    }
  }

  int total = 0;
  for(int i = 0; i < array_size + 1; i++){
   printf("count of index %d is ", i);
   printf("%d\n", counttable[i]);
   total += counttable[i];
  }
  printf("total is %d\n",total);
  return 0;
}
