change problem size in file hungarian.c (#define N ...)
=> it is necessary to specify the block sizes (N_25, N_50, ...) manually. Therefore divide problem size by 4. The first block has the size of this result. For each step this value is added to get the next bigger block size.
Attention only integer block sizes are working! 

E.g.
# define N 100 
# define N_25 25
# define N_50 50
...
# define N_75 75

To set the number of runs just modify the constant R (#define R ...)

For tests with problem sizes larger than 1000, increase stack size with ulimit -s ...