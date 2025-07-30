change problem size in file hungarian.c (#define N ...)
=> it is necessary to specify the block sizes (N_50) manually. Therefore divide problem size by 2. The first block has the size of this result.
Attention only integer block sizes are working! 

E.g.
# define N 100 
# define N_50 50

To set the number of runs just modify the constant R (#define R ...)

For tests with problem sizes larger than 1000, increase stack size with ulimit -s ...