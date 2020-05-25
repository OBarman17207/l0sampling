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
