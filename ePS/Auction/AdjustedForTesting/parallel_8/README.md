# ePS Auction Algorithm Implementation with 8 cores adjusted for testing

## Configuration

### 1. Problem Size
In `_emx_s_auction.c`, the problem size has to be set. It is also necessary to manually define the block size N_18, N_28, ..., N_78. (Only integer block sizes are supported!)
Example:

```c
# define N 80 
# define N18 10
# define N28 20
...
# define N78 70
```

### 2. Number of Runs
To configure how many times the test runs, modify the constant R:
```c
#define R <num_runs>
```

### 3. Large Problem Sizes (> 1000)
When running with large values of N (greater than 1000), you may need to increase the stack size:
```bash
ulimit -s <new_stack_size>
```
### 4. Compile Code
Execute Makefile:
```bash
make
```

### 5. Run Code
Run the compiled code. The results will be stored in the generated file `auc_emmtrix_8.txt`.
```bash
./auction
```
