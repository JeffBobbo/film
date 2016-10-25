EXEC:=memtest

MAIN = main.o alloc.o llist.o csv.o film.o moviedatabase.o

# general compiler settings
CFLAGS=-std=gnu11 -Wall -Wextra -ggdb
LDFLAGS=

#default target is debug Linux
all: linux

win: CC=x86_64-w64-mingw32-c++
win: LDFLAGS+=-static-libgcc -static-libstdc++ -static
win: EXEC:=$(EXEC).exe
win: comp

linux: EXEC:=$(EXEC).out
linux: comp

comp: $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $(EXEC) $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN)

.PHONY: all clean

