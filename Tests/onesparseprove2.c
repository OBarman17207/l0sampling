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


int onesparseprove2() {
  struct one_sparse* one_sparse_structure = malloc(sizeof(struct one_sparse));
  one_sparse_structure->sum_of_weights = 0;
  one_sparse_structure->sum_of_identifiers = 0;
  one_sparse_structure->sum_of_fingerprints = 0;

  int array_size = rand() % 10000;
  int number_of_index = (rand() % (array_size - 2)) + 2;
  //printf("number of index should be %d\n", number_of_index);

  for(int i = 0; i < number_of_index; i++){
    update_one_sparse_recovery(one_sparse_structure, (rand() % (array_size - 1) + 1), rand(),0,0);

  }
  if(recover_one_sparse(one_sparse_structure)){
      return 0;
  }
  return 1;
}

int main(int argc, char const *argv[]) {
  int runs = atoi(argv[1]);
  bool retry = false;
  int size = 2;
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, size, runs, retry);
  while(count_struct->runs_left > 0){
    int x = onesparseprove2();
    increase_count(count_struct, x);
  }
  print_count(count_struct);
  free(count_struct);

  return 0;
}
