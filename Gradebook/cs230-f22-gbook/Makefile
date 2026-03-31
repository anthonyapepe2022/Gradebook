CXXFLAGS = -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -std=c++17

OBJS = gbtest

all: ${OBJS}

Gradebook.o: Gradebook.h

gbtest: Gradebook.o

.PHONY: clean
clean:
	rm -f *.o ${OBJS} *~