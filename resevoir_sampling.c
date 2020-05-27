#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "count.h"


int resevoir_sample() {
  FILE* file;
  char* line = NULL;
  size_t len = 0;
  file = fopen("TestFile.txt", "r");
  int result = 0;
  if (file) {
    if (getline(&line, &len, file) == -1){
      printf("no file found\n");
      return 0;
    }
    int current_size = 0;

    while (getline(&line, &len, file) != -1) {
      int index = strtol(strtok(line, ","), NULL, 10);
      current_size++;
      if(rand() < (RAND_MAX/current_size)){
        result = index;
      }

    }
  }
  fclose(file);
  return result;
}

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]);
  int runs = atoi(argv[2]);
  int size = n + 1;
  bool retry = false;
  srand(time(0));
  struct count_object* count_struct = malloc(sizeof(struct count_object));
  count_setup(count_struct, size, runs, retry);
  for(int j = 0; j < runs; j++){
    int result = resevoir_sample();
    //printf("result is %d\n",result);
    increase_count(count_struct, result);
  }
  print_count(count_struct);
  free(count_struct);
  return 0;

}
