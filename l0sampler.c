#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "l0sampler.h"




/* Prints index and frequency of a one_sparse vector
** Does not test for sparsity and if vector one is not truly one-sparse this function prints nonsense */
void print_one_sparse(struct one_sparse* one){
  printf("%ld ", (one->sum_of_weights));
  printf("%ld ", (one->sum_of_identifiers));
}

int64_t power(int a, int b){
  int64_t result = 1;
  for(int i = 0; i < b; i++){
    result *= a;
  }
  return result;
}

int random(int range){
  int inv_range = ((int) ((RAND_MAX)/range));
  int x = rand();
  while (x >= range*inv_range){
    x = rand();
  }
  return x/inv_range;
}

/* Checks if an index via it's hashed counterpart is in a level */
int index_in_level(int level, int hash_index, int buckets){
  if (hash_index <= (buckets/pow(2,level))){
    return 1;
  }
  return 0;
}

//void tab_hash_create(int* hashtable, int buckets, int r);
//void tab_hash(int* hashtable, int index,int buckets, int r);
/* Chooses h:[vec_len] -> [vec_len^3] from a k-wise independent hash family by instantiaing k random numbers bounded by a large prime */
void hash_create(int* hashtable, int k, int p){
  //Set up Carter Wergman hash with prime p > vec_len

  //choose ao to ak-2 s.t 0 <= ai < p
  for (int i = 0; i < k - 1; i ++){
    //hashtable[i] = random(p);
    hashtable[i] = rand() % p;
  }
  //choose ak-1 s.t 0< ak-1 < p
  //hashtable[k - 1] = random(p - 1) + 1;
  hashtable[k - 1] = (rand() % (p - 1)) + 1;
 }

/* Maps an index to a hashed_index in range[0,buckets) */
int hash(int* hashtable, int index, int k, int buckets, int p){

  uint64_t hashed_index = 0;
  for (int i = 0; i < k; i++){
    hashed_index += hashtable[i] * power(index,i);
  }

  int result = hashed_index % p;
  result = result % buckets;
  if(result < 0){
    result = abs(result);
  }

  return result;
}

/* Sets up a table of initialized one_sparse objects of size 2*s*r */
void setup_sparse_vector(struct one_sparse* s_sparse_table, int size){
  for (int i = 0; i < size; i++){
      s_sparse_table[i].sum_of_weights = 0;
      s_sparse_table[i].sum_of_identifiers = 0;
      s_sparse_table[i].sum_of_fingerprints = 0;
  }
}

/* Updates a one-sparse structure with an index and frequency */
void update_one_sparse_recovery(struct one_sparse* one, int64_t index, int64_t delta_freq){
  one->sum_of_weights += delta_freq;
  one->sum_of_identifiers += index*delta_freq;
  one->sum_of_fingerprints += index*index*delta_freq;
}

/* Updates a s-sparse structure for a specific level with an index and frequency
** Does this by choosing to update r one-sparse structures */
void update_s_sparse_recovery(int* hashtable, struct one_sparse* s_sparse_table, int index, int delta_freq, int level, int s, int r, int k, int prime){
  int* row_hashtable = malloc(sizeof(int) * k);
  for (int i = level*r; i < (level+1)*r; i++){
    //Chooses a level and trial unique row of primes for hashing
    for(int j = 0; j < k; j ++){
      row_hashtable[j] = hashtable[i*k + j];
    }

    int hashed_index = hash(row_hashtable, index, k, 2*s, prime);
    update_one_sparse_recovery(&s_sparse_table[i*2*s + hashed_index], index, delta_freq);
  }
  free(row_hashtable);
}

/* recovers a one-sparse structure if and only if it is truly one-sparse*/
struct one_sparse* recover_one_sparse(struct one_sparse* one){
  //Checks if one is one-sparse
  if(one->sum_of_weights != 0){
    if (((one->sum_of_fingerprints * one->sum_of_weights) == (one->sum_of_identifiers * one->sum_of_identifiers))){
      return one;
    }
  }

  return NULL;
}


/* recovers a s-sparse vector of a specific level (NULL otherwise)
** Does this by greedily trying to recover one-sparse vectors */
struct one_sparse* recover_vector(struct one_sparse* s_sparse_table, int s, int r, int m){
  struct one_sparse* result = malloc(sizeof(struct one_sparse));
  struct one_sparse* s_vector = malloc(sizeof(struct one_sparse)*s);
  setup_sparse_vector(s_vector,s);
  int sparse_counter = 0;
  for (int i = 0; i < m*r; i++){
    for(int j = 0; j < 2*s; j++){
      result = recover_one_sparse(&s_sparse_table[i*2*s + j]);
      if(result){
        s_vector[sparse_counter] = *result;
        sparse_counter++;
        if(sparse_counter > s){
          j = 2*s;
          setup_sparse_vector(s_vector,s);
          sparse_counter = 0;
        }
      }


    }
    if(sparse_counter > 0){
      return &s_vector[0];
    }
  }

  return NULL;

}

/* Reads through the stream taking the first element as the vector Length
** Calls the instantiation,updating and recovery functins */
int read_stream(int k, int s, int r) {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  size_t vec_len = 0;
  int prime1 = 10937;
  int prime2 = 11069;
  //srand(seed);
  //srand(seed);
  file = fopen("TestFile.txt", "r");

  if (file) {
    if (getline(&line, &len, file) != -1){

      // number of values
      vec_len = strtol(line,NULL,10);
    }

    //Chosen to be vec_len^3 so that there are no collisions with high probabillity
    int buckets = (int) pow(vec_len,3);

    if(buckets > prime1 || buckets > prime2){
      return 0;
    }
    // number of subvectors such that at least one level is s-sparse
    int m = (int) ((log(buckets)/log(2)) + 1);

    // table of random values bounded by a large prime used to hash indexs into aprroximantly geometric levels
    int* primetable = malloc(sizeof(int) * k);
    hash_create(primetable, k, prime1);

    // a table of 1-sparse structures
    struct one_sparse* s_sparse_table = malloc(sizeof(struct one_sparse) * 2 * s * r * m);
    setup_sparse_vector(s_sparse_table, 2*s*r*m);

    // a family of hashes used for s-sparse recovery
    int* hashtable = malloc(sizeof(int) * k * r * m);
    hash_create(hashtable, k*r*m, prime2);



    // loop through the stream of updates
    while (getline(&line, &len, file) != -1) {
      int index = strtol(strtok(line, ","), NULL, 10);

      int delta_freq = strtol(strtok(NULL, ","), NULL, 10);
      int hash_index = hash(primetable, index, k, buckets, prime1);

      // loop through the m levels
      for (int level = 0; level < m; level ++){
        if (index_in_level(level, hash_index, buckets)){


          // update s-sparse recovery for that specific level
          update_s_sparse_recovery(hashtable, s_sparse_table, index, delta_freq, level, s, r, k, prime2);
        }
      }
    }
    free(primetable);
    free(hashtable);
    fclose(file);

    //Recover an s-sparse vector
    struct one_sparse* final_vector = malloc(sizeof(struct one_sparse));
    final_vector = recover_vector(s_sparse_table, s, r, m);
    if (final_vector){
      int result = (final_vector->sum_of_identifiers/final_vector->sum_of_weights);
      free(s_sparse_table);
      free(final_vector);
      return result;

    }


  }
  return 0;
}
