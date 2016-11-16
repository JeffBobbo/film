EXEC:=omdb

MAIN = main.o alloc.o llist.o csv.o film.o moviedatabase.o
LIST = listTest.o llist.o alloc.o

# general compiler settings
CFLAGS:=-std=gnu11 -Wall -Wextra -Wpedantic -ggdb
LDFLAGS=


all: $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $(EXEC).out $(LDFLAGS)

list: $(LIST)
	$(CC) $(CFLAGS) $(LIST) -o list.out $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN) $(LIST)

.PHONY: all clean

