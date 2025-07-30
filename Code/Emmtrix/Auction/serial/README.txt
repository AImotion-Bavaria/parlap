change problem size in file auction.c (#define N ...)

To set the number of runs just modify the constant (#define R ...)

compiled with:
gcc ./auction.c -O3 -o hun

For tests with problem sizes larger than 1000, increase stack size with ulimit -s ...


