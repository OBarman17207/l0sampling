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


int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int s = atoi(argv[2]);
  int r = atoi(argv[3]);
  int prime = 1000187;
  struct one_sparse* s_sparse_structure = malloc(sizeof(struct one_sparse) * 2 * s * r);
  setup_sparse_vector(s_sparse_structure, 2*s*r);
  srand(time(0));
  int* hashtable = malloc(sizeof(struct one_sparse) * k);
  hash_create(hashtable, k, prime);
  int array_size = rand() % prime;
  int number_of_index = (rand() % s) + 1;
  printf("number of index should be %d\n", number_of_index);

  for(int i = 0; i < number_of_index; i++){
    update_s_sparse_recovery(hashtable, s_sparse_structure, ((rand() % array_size) + 1), rand(), 0, s, r, k, prime);

  }
  struct one_sparse* result = recover_vector(0, s_sparse_structure, s, r);
  if(result){
    print_one_sparse(recover_vector(0, s_sparse_structure, s, r));
  }


  return 0;
}
