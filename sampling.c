#include "l0sampler.h"
#include "count.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

/* s describes sparsity of recovered vector and should be small
** k is k-wise independence of hash families and should be O(s)
** r is the number of rows in the s-sparse recovery algorithim */
int main(int argc, char const *argv[]) {
  int k = atoi(argv[1]);
  int s = atoi(argv[2]);
  int r = atoi(argv[3]);
  int n = atoi(argv[4]);
  int runs = atoi(argv[5]);
  bool retry = atoi(argv[6]);
  int size = n + 1;
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, size, runs, retry);
  while(count_struct->runs_left > 0){
    int x = read_stream(k,s,r);
    increase_count(count_struct, x);
  }
  print_count(count_struct);
  free(count_struct);

  return 0;
}
