from s_sparse_recovery import SSparseRecovery
from one_sparse_recovery import OneSparseRecovery
from l0_sampling import l0_sample
from hash import Hash
import math
import fire
import logging
import matplotlib.pyplot as plt
import numpy as np

VECTOR_LENGTH_ESTIMATION = 10
logger = logging.getLogger('count')

def count(k=4, s=4, r=4, logging_level=20, runs=1000000):
    fig = plt.figure(figsize=(10,5))
    ax = fig.add_subplot(111)
    ax.set_xlabel('Results')
    ax.set_xlabel('Count')
    results = np.linspace(0, 10, 11)

    count = [0] * (VECTOR_LENGTH_ESTIMATION + 1)
    for run in range(runs):
        count[l0_sample(k, s, r, logging_level)] += 1
    ax.bar(results, count)
    plt.show()

if __name__ == "__main__":
    fire.Fire(count)
