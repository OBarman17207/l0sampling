#include <stdint.h>
#include <stdbool.h>
#ifndef L0SAMPLER_H_
#define L0SAMPLER_H_

struct one_sparse {
  uint64_t sum_of_weights;
  uint64_t sum_of_identifiers;
  uint64_t sum_of_fingerprints;
  int zeta;
};
void print_one_sparse( struct one_sparse* one);
int index_in_level(int level, int hash_index, int buckets);
void hash_create(int* hashtable, int k, int p);
int hash(int* hashtable, int index, int k, int buckets, int p);
void setup_sparse_vector(struct one_sparse* s_sparse_table, int size, int prime);
void update_one_sparse_recovery(struct one_sparse* one, int64_t index, int64_t delta_freq, int prime);
void update_one_sparse_recovery_G(struct one_sparse* one, int64_t index, int64_t delta_freq);
void update_one_sparse_recovery_CF(struct one_sparse* one, int64_t index, int64_t delta_freq, int prime);
bool test_one_sparse_recovery(struct one_sparse *one, int prime);
bool test_one_sparse_recovery_G(struct one_sparse *one);
bool test_one_sparse_recovery_CF(struct one_sparse *one, int prime);
void update_s_sparse_recovery(int* hashtable, struct one_sparse* s_sparse_table, int index, int delta_freq, int level, int k, int s, int r, int hashprime, int sprime);
struct one_sparse* recover_one_sparse(struct one_sparse* one, int prime);
struct one_sparse* recover_vector(struct one_sparse* s_sparse_table, int s, int r, int m, int prime);
int read_stream(int k, int s, int r, int sprime, char const* filename);

#endif //L0SAMPLER_H_
