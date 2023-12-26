CC = clang
CFLAGS = -g -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm
#TESTS = tests
EXEC = tsp
HEADERS = graph.h path.h stack.h vertices.h

all: $(EXEC)

$(EXEC): $(EXEC).o graph.o path.o stack.o
	$(CC) $^ $(LFLAGS) -o $@

#$(TESTS): $(TESTS).o mathlib.o operators.o stack.o
#	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) $(TESTS) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
