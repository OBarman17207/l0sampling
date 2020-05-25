#include "count.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>




void count_setup(struct count_object* count_struct, int size, int runs, bool retry){
  count_struct->size = size;
  count_struct->total_runs = runs;
  count_struct->runs_left = runs;
  count_struct->retry = retry;
  count_struct->count = malloc(sizeof(int) * size);
  for(int i = 0; i < size; i ++){
    count_struct->count[i] = 0;
  }
}

void increase_count(struct count_object* count_struct, int result){
  if (!(result == 0 && count_struct->retry)){
    (count_struct->count)[result] += 1;
    count_struct->runs_left -= 1;
  }
}

void print_count(struct count_object* count_struct){
  float mean = count_struct->total_runs/(count_struct->size - 1);
  float sd = 0;
  int total = 0;

  for(int i = 0; i < count_struct->size; i ++){
    printf("count of index %d is ", i);
    printf("%d\n", count_struct->count[i]);
    if( i > 0){
      float f = (count_struct->count[i] - mean);
      sd += pow(f, 2);
    }
    total += count_struct->count[i];
  }
  printf("sd is %f\n", sqrt(sd/count_struct->total_runs));
  printf("total is %d\n", total);
}
