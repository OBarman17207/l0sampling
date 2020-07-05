#include <stdint.h>
#include <stdbool.h>
#ifndef COUNT_H_
#define COUNT_H_

struct count_object {
  int size;
  int runs_left;
  int total_runs;
  bool retry;
  int* count;
};

void count_setup(struct count_object* count_struct, int size, int runs, bool retry);
void increase_count(struct count_object* count_struct, int result);
void print_count(struct count_object* count_struct);

#endif //L0SAMPLER_H_
