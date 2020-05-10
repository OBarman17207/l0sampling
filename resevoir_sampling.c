#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


int resevoir_sample(int seed) {
  FILE* file;
  char* line = NULL;
  size_t len = 0;
  srand(seed);
  file = fopen("TestFile.txt", "r");
  //srand(seed);
  int result = 0;
  if (file) {
    if (getline(&line, &len, file) == -1){
      printf("big error!!!!\n");
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
  int size = atoi(argv[1]);
  int runs = atoi(argv[2]);
  int* result_count = malloc(sizeof(int)*(size + 1));
  srand(time(0));

  for(int i = 0; i < size + 1; i++){
    result_count[i] = 0;
  }
  //printf("hello\n");
  for(int j = 0; j < runs; j++){
    int result = resevoir_sample(rand());
    //printf("result is %d\n",result);
    result_count[result] += 1;
  }
  int total = 0;
  for(int i = 0; i < size + 1; i++){
    printf("count of index %d is ", i);
    printf("%d\n", result_count[i]);
    total += result_count[i];
  }
  printf("total is %d\n",total);
}
