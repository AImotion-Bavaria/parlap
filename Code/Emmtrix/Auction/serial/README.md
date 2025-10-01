# Serial Input Code for ePS Auction Algorithm Implementation

## Configuration

### 1. Problem Size
In `auction.c`, the problem size has to be set.
Example:

```c
#define N 100
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
gcc ./auction.c -O3 -o hun
```

### 5. Run Code
Run the compiled code. The results will be stored in the generated file `auc_emmtrix_50_ser.txt`.
```bash
./auction
```
