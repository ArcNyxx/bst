/* bst - binary search tree
 * Copyright (C) 2022 ArcNyxx
 * see LICENCE file for licensing information */

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <sys/types.h>

typedef ssize_t bst_find_t;
typedef struct { } bst_data_t;

typedef struct bsn {
	bst_find_t val;
	bst_data_t data;
	struct bsn *lft, *rgt;
} bsn_t;

typedef struct bst {
	bsn_t *root;
	size_t size;
} bst_t;

bsn_t *bsn_init(bst_find_t val);

bst_t *bst_init(bst_t *bst);
bst_t *bst_dest(bst_t *bst);

bool bst_addn(bst_t *bst, bsn_t *bsn);
bsn_t *bst_remn(bst_t *bst, bst_find_t val);

bsn_t *bst_find(bst_t *bst, bst_find_t val);

bst_find_t bst_minn(bst_t *bst);
bst_find_t bst_maxn(bst_t *bst);

#endif /* BST_H */
