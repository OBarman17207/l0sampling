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
  int n = atoi(argv[4]);
  int runs = atoi(argv[5]);
  int* frequency_range = malloc(sizeof(int) * (n+1));
  for(int i = 0; i < n+1; i ++){
    frequency_range[i] = 0;
  }
  float mean = runs/n;
  float sd = 0;
  int total = 0;
  srand(time(0));
  for(int i = 0; i < runs; i++){

    int x = read_stream(k,s,r);
    if ( x > 0){
      frequency_range[x] += 1;
    }
    else{
      i--;
      runs++;
    }

  }


  for(int i = 0; i < n+1; i ++){
    printf("count of index %d is ", i);
    printf("%d\n", frequency_range[i]);
    if( i > 0){
      float f = (frequency_range[i] - mean);
      sd += pow(f, 2);
    }
    total += frequency_range[i];
  }
  printf("sd is %f\n", sqrt(sd/runs));
  printf("total is %d\n", total);
  return 0;
}
