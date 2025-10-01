#executable 
HUN_PARALLEL = test_hungarian_parallel_openmp
AUC_PARALLEL = test_auction_parallel_openmp
#compiler

CPPFLAGS += -O3 -std=c++17 
CPPFLAGS_OPENMP += -O3 -fopenmp -lpthread -std=c++17

all: $(HUN_PARALLEL) $(AUC_PARALLEL)

$(HUN_PARALLEL): $(HUN_PARALLEL).cpp
	$(CXX) $(CPPFLAGS_OPENMP) $^ -o $(HUN_PARALLEL)

$(AUC_PARALLEL): $(AUC_PARALLEL).cpp
	$(CXX) $(CPPFLAGS_OPENMP) $^ -o $(AUC_PARALLEL)

clean:
	rm $(HUN_PARALLEL) $(AUC_PARALLEL)
