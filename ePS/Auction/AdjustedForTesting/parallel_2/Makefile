CC = gcc
CXX = g++
NAME = auction

CFLAGS = -march=native -O3
CXXFLAGS = -march=native 
LDFLAGS = 
INC =
LIBS_PATH =

C_FILES = emxapi_comm_ringbuf_fixed.c emxapi_comm_ringbuf_fixed_impl.c timestamp.c _emx_s_auction.c emxapi_comm_ringbuf_fixed_fork.c _emx_t_main.c
CPP_FILES = 
H_FILES = emxapi_comm_ringbuf_config.h _emx_main.h emxapi_comm_ringbuf_fixed_fork.h timestamp.h emxapi_comm_ringbuf_fixed.h emxapi_defines.h

OBJECTS=$(patsubst %.c, %.o, $(C_FILES)) $(patsubst %.cpp, %.o, $(CPP_FILES))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBS_PATH) $(LDFLAGS)

run: $(NAME)
	ulimit -s unlimited; ./auction

emxapi%.o: emxapi%.c $(H_FILES)
	$(CC) $(INC) -c $< -o $@

%.o: %.c $(H_FILES)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

%.o: %.cpp $(H_FILES)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -f *.o auction
