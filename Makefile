CFLAGS	+= -Wall
LIBS	+= -lpthread
INC	+= -Iinclude
CC	:= $(CROSS_COMPILE)g++


%.o: %.cpp
	@$(CC) -c -o $@ $(CFLAGS) $(INC) $<

server_test: test/server_test.o
	@$(CC) -o $@ $< $(LIBS)

client_test: test/client_test.o
	@$(CC) -o $@ $< $(LIBS)

all: server_test client_test

clean:
	@rm -f test/*.d test/*.o server_test client_test

test: all
	./server_test 8001 & sleep 1 && ./client_test 127.0.0.1:8001
