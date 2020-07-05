import sympy
import random
from hash import modulo_power


MAX_VECTOR_RANGE = 1000000

## The OneSparseRecovery class implements one-sparse recovery with Ganguly's method
class GOneSparseRecovery():
    def __init__(self):
        self._sum_of_weights = 0
        self._sum_of_identifiers = 0
        self._sum_of_fingerprints = 0

    def update(self, index, frequency):
        self._sum_of_weights += frequency
        self._sum_of_identifiers += frequency*index
        self._sum_of_fingerprints += frequency*index*index

    def recover(self):
        if ((self._sum_of_fingerprints*self._sum_of_weights
            == self._sum_of_identifiers*self._sum_of_identifiers)
            & self._sum_of_weights != 0):
            return int(self._sum_of_identifiers/self._sum_of_weights)
        return 0

class CFOneSparseRecovery():
    def __init__(self):
        self._sum_of_weights = 0
        self._sum_of_identifiers = 0
        self._sum_of_fingerprints = 0
        self._prime = sympy.randprime(MAX_VECTOR_RANGE, 2*MAX_VECTOR_RANGE)
        self._zeta = random.randint(1, self._prime)

    def update(self, index, frequency):
        self._sum_of_weights += frequency
        self._sum_of_identifiers += frequency*index
        self._sum_of_fingerprints += (int(frequency*modulo_power(self._zeta, index, self._prime)) % self._prime)
        self._sum_of_fingerprints = self._sum_of_fingerprints % self._prime

    def recover(self):
        if self._sum_of_weights != 0:
            if (self._sum_of_fingerprints == self._sum_of_weights
                * int(modulo_power(self._zeta, int(self._sum_of_identifiers/self._sum_of_weights), self._prime)) % self._prime):
                return int(self._sum_of_identifiers/self._sum_of_weights)
        return 0

class OneSparseRecovery(CFOneSparseRecovery):
    pass
