#executable 
HUN_SERIAL = test_hungarian_serial
AUC_SERIAL = test_auction_serial
#compiler

CPPFLAGS += -O3 -std=c++17 

all: $(HUN_SERIAL) $(AUC_SERIAL)

$(HUN_SERIAL): $(HUN_SERIAL).cpp
	$(CXX) $(CPPFLAGS) $^ -o $(HUN_SERIAL)

$(AUC_SERIAL): $(AUC_SERIAL).cpp
	$(CXX) $(CPPFLAGS) $^ -o $(AUC_SERIAL)

clean:
	rm $(HUN_SERIAL) $(AUC_SERIAL)
