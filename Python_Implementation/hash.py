import random

def modulo_power(base, exponent, modulo):
    result = 1
    for counter in range(exponent):
        result *= base
        result = result % modulo
    return result

## K wise independent Hashing via choosing a random k'th degree polynomial
class PolynomialHash():
    def __init__(self, k, bucket_number, prime):
        random.seed()
        self._bucket_number = bucket_number
        self._k = k
        self._prime = prime
        self._table = random.sample(range(self._prime), k = self._k-1)
        self._table.append(random.randint(1, self._prime))

    def hash(self, value):
        result = 0
        for degree in range(self._k):
            coefficent = self._table[degree]
            result += (coefficent * modulo_power(value, degree, self._prime)) % self._prime
        result = result % self._prime
        result = result % self._bucket_number
        return result


class Hash(PolynomialHash):
    pass
