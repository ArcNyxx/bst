# bst - binary search tree
# Copyright (C) 2022 ArcNyxx
# see LICENCE file for licensing information

.POSIX:

SRC = bst.c test.c
OBJ = $(SRC:.c=.o)
HEAD = bst.h

all: bst.o

$(OBJ): $(HEAD)

.c.o:
	$(CC) $(CFLAGS) -c $<

test: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f test $(OBJ) bst.tar.gz

dist: clean
	mkdir -p bst
	cp LICENCE Makefile $(SRC) $(HEAD) bst
	tar -cf - bst | gzip -c > bst.tar.gz
	rm -rf bst
