# bst - binary search tree
# Copyright (C) 2022 ArcNyxx
# see LICENCE file for licensing information

SRC = bst.c test.c
OBJ = $(SRC:.c=.o)
HEAD = bst.h

all: bst

$(OBJ): $(HEAD)

.c.o:
	$(CC) $(CFLAGS) -c $<

bst: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f bst bst.tar.gz $(OBJ)

dist: clean
	mkdir -p bst
	cp LICENCE Makefile $(SRC) $(HEAD) bst
	tar -cf - bst | gzip -c > "bst.tar.gz"
	rm -rf bst
