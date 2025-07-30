change problem size in file hungarian.c (#define N ...)

To set the number of runs just modify the constant (#define R ...)

compiled with:
gcc ./hungarian.c -O3 -o hun

For tests with problem sizes larger than 1000, increase stack size with ulimit -s ...


