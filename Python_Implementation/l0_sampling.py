from s_sparse_recovery import SSparseRecovery
from one_sparse_recovery import OneSparseRecovery
from hash import Hash
import math
import fire
import logging
import sympy


DIFFICULTY = 'simple'
VECTOR_LENGTH_ESTIMATION = 10
SAMPLING_RANGE = (VECTOR_LENGTH_ESTIMATION
                * VECTOR_LENGTH_ESTIMATION
                * VECTOR_LENGTH_ESTIMATION)

logger = logging.getLogger('l0_sampler')
#logging.basicConfig(filename='l0_sampler.log',level=logging.DEBUG)


def index_in_level(value, level = 0):
    if (value <= SAMPLING_RANGE>>level):
        return True
    return False

def l0_sample(k=4, s=4, r=4, logging_level=20):
    logging.basicConfig(level=logging_level)
    hash_map = Hash(k, SAMPLING_RANGE, sympy.randprime(SAMPLING_RANGE*3,SAMPLING_RANGE*6))
    number_of_levels = math.ceil(math.log2(SAMPLING_RANGE))
    logger.debug(f' the number of levels is {number_of_levels}')
    s_sparse_recovery_table = []
    for i in range(number_of_levels):
        s_sparse_recovery_table.append(SSparseRecovery(k,s,r))

    with open("{}stream.txt".format(DIFFICULTY), "r", newline='',encoding="utf8") as f:
        for line in f:
            pair = line.split(',')
            index = int(pair[0])
            frequency = int(pair[1])
            for level in range(number_of_levels):
                if index_in_level(index, level):
                    s_sparse_recovery_table[level].update(index, frequency)

        for s_sparse_structure in s_sparse_recovery_table:
            result = s_sparse_structure.recover()
            if result != 0:
                return result


if __name__ == "__main__":
    fire.Fire(l0_sample)
