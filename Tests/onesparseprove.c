#include "../l0sampler.h"
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

int main(int argc, char const *argv[]) {
  struct one_sparse* one_sprase_recovery = malloc(sizeof(struct one_sparse));
  one_sprase_recovery->sum_of_weights = 0;
  one_sprase_recovery->sum_of_identifiers = 0;
  one_sprase_recovery->sum_of_fingerprints = 0;
  srand(time(0));
  int array_size = rand();
  int random_index = (rand() % (array_size - 1) + 1);
  printf("recoverd index should be %d\n", random_index);
  for(int i = 0; i < array_size; i ++){
    if( i == random_index){
      update_one_sparse_recovery(one_sprase_recovery, i, rand(),0,0);
    }
    else{
      update_one_sparse_recovery(one_sprase_recovery, i, 0,0,0);
    }
  }
  print_one_sparse(recover_one_sparse(one_sprase_recovery));
  return 0;
}
