# l0sampling

An implementation of l_0sampling

An implementation of reservoir sampling

Testing all major parts of the l_0sampling

  * The Tests folder contains it's own README and tests the major functions of the l_0 sampler

## Running the code

To run either the l0_sampler or reservoir sampler do the folloing

Make the l0_sampler and resevoir sampler type

  ''' make '''

For l_0 sampler these are the general parameters:
$ ./l0sampling k s r prime n runs retry stream.txt

eg:

  '''./l0sampling 4 4 4 0 10 1 0 "FileSimple.txt" '''

For the reservoir sampler these are the general parameters:

  ''' ./resevoir_sampling n runs "FileSimple.txt"'''

eg:

  ''' ./resevoir_sampling 10 1 "FileSimple.txt"'''
