from one_sparse_recovery import OneSparseRecovery
from hash import Hash
import sympy

## The SSparseRecovery class implements s-sparse recovery
class SSparseRecovery():
    def __init__(self, k, s, r):
        self._s_sparse_structure = []
        for i in range(2*s*r):
            one = OneSparseRecovery()
            self._s_sparse_structure.append(one)
        self._k = k
        self._s = s
        self._r = r
        self._hash_list = []
        for i in range(r):
            hash = Hash(k, 2*s, sympy.randprime(4*s, 8*s))
            self._hash_list.append(hash)


    def update(self, index, frequency):
        row = 0
        for hash_map in self._hash_list:
            hash_value = hash_map.hash(index)
            self._s_sparse_structure[2*self._s*row + hash_value].update(index,frequency)
            row += 1

    def recover(self):
        for row in range(self._r):
            sparsity = 0
            final_result = 0
            for column in range(2*self._s):
                result = self._s_sparse_structure[2*self._s*row + column].recover()
                if result != 0:
                    sparsity += 1
                    if sparsity < self._s:
                        final_result = result
            if final_result != 0:
                return final_result
        return 0
