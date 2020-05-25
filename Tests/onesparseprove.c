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

//Objective: Testx if a one-sparse vector recovers successfull. This will be used as a building block for more comprehensive testing in onesparseprove2

/* Setup: Define array of random size and choose a random index in that array to give a random non-zero frequency
update the one sparse structure with all indices of the array and zero frequency except the randomly chosen index */

/* Further notes: Though this tests these concepts experminetally there are two edge cases that it does not test.
  1. The order of indices stays the same between tests
  2. All indices of the array are added into the one_sparse structure */

int onesparseprove() {
  struct one_sparse* one_sprase_recovery = malloc(sizeof(struct one_sparse));
  one_sprase_recovery->sum_of_weights = 0;
  one_sprase_recovery->sum_of_identifiers = 0;
  one_sprase_recovery->sum_of_fingerprints = 0;
  int array_size = rand() % 10000;
  int random_index = (rand() % (array_size - 1) + 1);
  printf("random index is %d\n",random_index);
  for(int i = 0; i < array_size; i ++){
    if( i == random_index){
      update_one_sparse_recovery(one_sprase_recovery, i, rand(),0,0);
    }
    else{
      update_one_sparse_recovery(one_sprase_recovery, i, 0,0,0);
    }
  }
  struct one_sparse* final_vector = recover_one_sparse(one_sprase_recovery);
  int result = -1;
  if(final_vector){
    result = (final_vector->sum_of_identifiers/final_vector->sum_of_weights);
    printf("recoved index is %d\n",result);
  }
  return (result == random_index);
}

int main(int argc, char const *argv[]) {
  int runs = atoi(argv[1]);
  bool retry = false;
  int size = 2;
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, size, runs, retry);
  while(count_struct->runs_left > 0){
    int x = onesparseprove();
    increase_count(count_struct, x);
  }
  print_count(count_struct);
  free(count_struct);

  return 0;
}
