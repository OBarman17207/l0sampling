#include "l0sampler.h"
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
  srand(time(0));

  printf("final result is %d\n", read_stream(k,s,r));
}
