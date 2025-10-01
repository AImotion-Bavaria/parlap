# Hungarian Algorithm Pthreads Implementation

## Configuration

Edit `/src/hungarian.cpp` to adjust the following parameters:

### 1. Number of Threads
Set the number of threads via the `NUM_THREADS` constant:
```cpp
#define NUM_THREADS 8
```
### 2. Problem Sizes
Define the problem sizes to test in the test_cases vector:
```cpp
vector<int> test_cases = { ... };
```

## Compilation
Compile code with:
```bash
make
```

## Execution
Run the compiled binary with:
```bash
./bin/hungarian <num_test_runs> <output_filename>
```
- num_test_runs: number of times to repeat the tests
- output_filename: name of the file where results will be stored

## Output
All output files are stored in the data/ directory.
