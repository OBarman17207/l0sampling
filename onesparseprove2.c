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
  struct one_sparse* one_sparse_structure = malloc(sizeof(struct one_sparse));
  one_sparse_structure->sum_of_weights = 0;
  one_sparse_structure->sum_of_identifiers = 0;
  one_sparse_structure->sum_of_fingerprints = 0;
  srand(time(0));
  int array_size = rand();
  int number_of_index = (rand() % (array_size - 2)) + 2;
  printf("number of index should be %d\n", number_of_index);

  for(int i = 0; i < number_of_index; i++){
    update_one_sparse_recovery(one_sparse_structure, (rand() % (array_size - 1) + 1), rand());

  }
  if(recover_one_sparse(one_sparse_structure)->sum_of_weights != 0){
      return 1;
  }

  return 0;
}
