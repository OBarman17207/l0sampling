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


int s_sparse_test(int k, int s, int r, int prime, int sprime, int number_of_index) {


  struct one_sparse* s_sparse_structure = malloc(sizeof(struct one_sparse) * 2 * s * r);
  setup_sparse_vector(s_sparse_structure, 2 * s * r, sprime);

  int* hashtable = malloc(sizeof(struct one_sparse) * k*r);
  hash_create(hashtable, k*r, prime);


  for(int i = 0; i < number_of_index; i++){
    update_s_sparse_recovery(hashtable, s_sparse_structure, (i + 1), rand(), 0, k, s, r, prime, sprime);
  }

  struct one_sparse* result = recover_vector(s_sparse_structure, s, r, 1, sprime);

  if (result){
    return (result->sum_of_identifiers/result->sum_of_weights);
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int s = atoi(argv[2]);
  int r = atoi(argv[3]);
  int sprime = atoi(argv[4]);
  int runs = atoi(argv[5]);
  int array_size = atoi(argv[6]);
  int size = array_size + 1;
  int prime = 1000187;
  bool retry = false;
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, size, runs, retry);
  while(count_struct->runs_left > 0){
    int x = s_sparse_test(k, s, r, prime, sprime, array_size);
    increase_count(count_struct, x);
  }
  print_count(count_struct);
  free(count_struct);

  return 0;
}
