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

int s_sparse_test(int k, int s, int r, int prime, int array_size, int number_of_index) {


  struct one_sparse* s_sparse_structure = malloc(sizeof(struct one_sparse) * 2 * s * r);
  setup_sparse_vector(s_sparse_structure, 2 * s * r);

  int* hashtable = malloc(sizeof(struct one_sparse) * k*r);
  hash_create(hashtable, k*r, prime);


  for(int i = 0; i < number_of_index; i++){
    update_s_sparse_recovery(hashtable, s_sparse_structure, (rand() % array_size) + 1, 1, 0, s, r, k, prime);
  }
  struct one_sparse* result = recover_vector(s_sparse_structure, s, r, 1);

  if (result){
    return (result->sum_of_identifiers/result->sum_of_weights);
  }
  return 0;
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
