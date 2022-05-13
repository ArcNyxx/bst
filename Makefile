# bst - binary search tree
# Copyright (C) 2022 ArcNyxx
# see LICENCE file for licensing information

SRC = bst.c test.c
OBJ = $(SRC:.c=.o)

all: bst

$(OBJ): bst.h

.c.o:
	$(CC) $(CFLAGS) -c $<

bst: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f bst $(OBJ)
