change problem size in file hungarian.c (#define N ...)
=> it is necessary to specify the block sizes (N18, N28, ...) manually. Therefore divide problem size by 8. The first block has the size of this result. For each step this value is added to get the next bigger block size.
Attention only integer block sizes are working! 

E.g.
# define N 80 
# define N18 10
# define N28 20
...
# define N78 70

To set the number of runs just modify the constant R (#define R ...)

For tests with problem sizes larger than 1000, increase stack size with ulimit -s ...